# include <Siv3D.hpp> // Siv3D v0.6.15
# include "JsonManager.h"
# include "GeneralPattern.h"
//# include "SolverProcess.h"

void Main()
{

	// background
	Scene::SetBackground(ColorF{ 0.0, 0.0, 0.0 });

	//child process
	/*SolverProcess cProcess;
	cProcess.Create();*/
	//ChildProcess solver;
	

	while (System::Update())
	{
		if (SimpleGUI::Button(U"START", Vec2{ 520, 370 }, 150)) {
			bool isGetOK = JsonManager::sendGetMatches();
			if (isGetOK) {
				if (auto problem = JsonManager::jsonParse()) {
					Print << U"JsonParse OK";
					Print << problem->b.width;
				}
				else {
					Print << U"JsonParse NG";
				}
			}
			
		}

		//if (SimpleGUI::Button(U"POST request", Vec2{ 520, 420 }, 150)) {
		//	JsonManager::sendPostAction();
		//}

		//if (SimpleGUI::Button(U"child send", Vec2{ 320, 370 }, 150)) {
		//	//cProcess.Send();
		//	/*solver = ChildProcess{ U"nitgc_solver.exe",Pipe::StdInOut };
		//	if (not solver) {
		//		Print << U"Failed to create a process";
		//	}
		//	else {
		//		solver.ostream() << 10 << std::endl;
		//		solver.ostream() << 20 << std::endl;
		//		int result;
		//		solver.istream() >> result;
		//		Print << U"result: " << result;
		//	}*/
		//}

		//if (SimpleGUI::Button(U"child receive", Vec2{ 320, 420 }, 150)) {
		//	//cProcess.Receive();
		//	
		//}
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
