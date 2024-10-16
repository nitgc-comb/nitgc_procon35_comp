# include <Siv3D.hpp> // Siv3D v0.6.15
# include "JsonManager.h"
# include "Solution.h"
# include "Problem.h"
# include "SolverProcess.h"

void Main()
{

	// background
	Scene::SetBackground(ColorF{ 0.0, 0.0, 0.0 });

	//child process
	std::future<std::optional<Solution>> futureResult;
	// if during calculation
	bool isProcessing = false;
	// if start or not
	bool isActivating = false;
	// stop flag (to stop calculation)
	std::atomic<bool> stopFlag = false;

	// number of attempts
	int attempts = 0;
	//minimum operations
	int minOps = -1;
	// number of unmatch pieces
	int minUnmatch = -1;
	int unmatch = 0;

	//text font
	const Font font{ 30 };

	Problem pro;
	

	while (System::Update())
	{
		//texts
		font(U"attempts: ", attempts).draw(440,30);
		font(U"minOps: ", minOps).draw(440, 100);
		font(U"minUnmatch: ", minUnmatch).draw(440, 170);


		// START button (setup)
		if (SimpleGUI::Button(U"START", Vec2{ 520, 370 }, 150)) {
			stopFlag = false;
			if (!isActivating) { // setup
				if (JsonManager::sendGetMatches()) {
					if (auto problem = JsonManager::jsonParse()) {
						pro = problem.value();
						Print << U"Setup OK";
						isActivating = true;
					}
					else {
						Print << U"Json Parse failed";
					}
				}
				else {
					Print << U"Get Request failed";
				}
			}
		}

		// STOP button
		if (SimpleGUI::Button(U"STOP", Vec2{ 520, 420 }, 150)) {
			isProcessing = false;
			isActivating = false;
			stopFlag = true;
		}

		// start calculation
		if (isActivating && !isProcessing) {
			futureResult = std::async(std::launch::async, SolverProcess::solve, pro, std::ref(stopFlag), &unmatch);
			isProcessing = true;
		}

		// async (when calculation complete)
		if (isProcessing) {
			if (futureResult.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
				// 計算が完了した場合
				if (auto result = futureResult.get()) { // retrieve result
					// if result is commonly retrieved
					Solution res = result.value();
					Print << U"calculation completed";
					Print << U"ops = " << res.n;
					Print << U"unmatch = " << unmatch;
					attempts++;

					// judge if do post action
					if (minUnmatch == 0) {
						if (minOps == -1 || minOps > res.n) {
							// write json file & POST request
							minOps = res.n;
							JsonManager::sendActions(res);
						}
					}
					else if (minUnmatch == -1 || minUnmatch > unmatch){
						minUnmatch = unmatch;
						JsonManager::sendActions;
					}
					

					isProcessing = false;

				}
				else {
					// if not
					Print << U"could not solve";
				}
				
			}
			else {
				// 計算中
				//Print << U"calculating...";
			}
		}	
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
