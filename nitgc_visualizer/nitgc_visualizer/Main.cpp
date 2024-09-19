# include <Siv3D.hpp> // Siv3D v0.6.15
# include "JsonManager.h"
# include "SolverProcess.h"

void Main()
{

	//child process
	SolverProcess cProcess;

	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });


	while (System::Update())
	{
		if (SimpleGUI::Button(U"GET request", Vec2{ 520, 370 }, 150)) {
			JsonManager::sendGetMatches();
		}

		if (SimpleGUI::Button(U"POST request", Vec2{ 520, 420 }, 150)) {
			JsonManager::sendPostAction();
		}

		if (SimpleGUI::Button(U"child send", Vec2{ 320, 420 }, 150)) {
			cProcess.Send();
		}

		if (SimpleGUI::Button(U"child receive", Vec2{ 320, 420 }, 150)) {
			cProcess.Receive();
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
