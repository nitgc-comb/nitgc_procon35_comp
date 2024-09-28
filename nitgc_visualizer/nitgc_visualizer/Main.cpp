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
	bool isProcessing = false;

	//minimum operations
	int minOps = 1000000000;
	

	while (System::Update())
	{
		// START button
		if (SimpleGUI::Button(U"START", Vec2{ 520, 370 }, 150)) {
			if (!isProcessing) {
				bool isGetOK = JsonManager::sendGetMatches();
				if (isGetOK) {
					if (auto problem = JsonManager::jsonParse()) {
						Print << U"JsonParse OK";
						Problem pro = problem.value();
						futureResult = std::async(std::launch::async, SolverProcess::solve, pro);
						isProcessing = true;
					}
					else {
						Print << U"JsonParse NG";
					}
				}
			}
			else {
				// if is processing
				Print << U"processing...";
			}
		}

		// STOP button
		if (SimpleGUI::Button(U"STOP", Vec2{ 520, 420 }, 150)) {
			if (isProcessing) {

			}
		}

		// async (when calculation complete)
		if (isProcessing) {
			if (futureResult.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
				// 計算が完了した場合
				if (auto result = futureResult.get()) { // retrieve result
					// if result is commonly retrieved
					Solution res = result.value();
					Print << U"result: " << res.n;
					for (int i = 0; i < res.n; i++) {
						Print << res.ops[i].p << U" " << res.ops[i].x << U" " << res.ops[i].y << U" " << res.ops[i].s;
					}

					if (minOps > res.n) {
						// write json file & POST request
						if (JsonManager::jsonWrite(res)) {
							Print << U"Json file write OK";

							if (JsonManager::sendPostAction()) {

							}
						}
						else {
							Print << U"Cannot write json file";
						}
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
