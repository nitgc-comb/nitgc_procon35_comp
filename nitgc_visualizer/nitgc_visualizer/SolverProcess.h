#pragma once
#include "Problem.h"
#include "Solution.h"
#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;
#define pint pair<int,int>

class SolverProcess
{
public:
	// solve function (for demo)
	//static std::optional<Solution> solve_demo(Problem problem, std::atomic<bool>& stopFlag) {
	//	Solution solution;
	//	int result = 0;
	//	for (int i = 0; i < 5; i++) {
	//		std::this_thread::sleep_for(std::chrono::seconds(1));  // 1秒待機
	//		result += i;
	//		if (stopFlag) {
	//			Print << U"calculation canceled";
	//			return std::nullopt;
	//		}
	//		Print << U"Step " << i << U": result = " << result;
	//	}

	//	// store an information for return
	//	int n = 1;
	//	solution.n = n;
	//	Array<Op> operations;
	//	for (int i = 0; i < n; i++) {
	//		operations.emplace_back();
	//		operations[i].p = 4;
	//		operations[i].x = 0;
	//		operations[i].y = 0;
	//		operations[i].s = 2;
	//	}
	//	solution.ops = operations;


	//	return solution;  // 計算結果を返す
	//}
	
	// ---------------------------for performance----------------------------------------
	//任意の抜型で下方向に型抜き
	static void downshape(vector<vector<int> >* a, vector<int> b, int w, int x, int y) {
		int size = round(pow(2, (w + 2) / 3));
		int perX = ((w + 3) % 3) / 2 + 1, perY = ((w + 2) % 3) / 2 + 1;
		for (int i = max(x, (x + 1000) % perX); i < min(round(x + size), round(a->at(0).size())); i += perX) {
			vector<int> raw(a->size());
			int index = max(y, (y + 1000) % perY);
			for (int j = max(y, (y + 1000) % perY); j < a->size(); j += 1) {
				if (!((j - y) % perY == 0 && j - y < size)) {
					raw.at(index) = a->at(j).at((i + b.at(j)) % (a->at(0).size()));
					index += 1;
				}
			}
			for (int j = max(y, (y + 1000) % perY); j < a->size(); j += 1) {
				if (((j - y) % perY == 0 && j - y < size)) {
					raw.at(index) = a->at(j).at((i + b.at(j)) % (a->at(0).size()));
					index += 1;
				}
			}
			for (int j = max(y, (y + 1000) % perY); j < a->size(); j += 1) {
				a->at(j).at((i + b.at(j)) % (a->at(0).size())) = raw.at(j);
			}
		}
	}


	// solve function (for performance)
	static std::optional<Solution> solve(Problem problem, std::atomic<bool>& stopFlag) {
		Solution solution;

		int tate, yoko;//ボートの縦と横
		tate = problem.board.height;
		yoko = problem.board.width;
		//cout << min(tate, yoko) << endl;
		int tesuu = 0;
		vector<vector<int> > allgenjou(tate, vector<int>(yoko));//型抜きに応じて変更する配列
		vector<vector<int> > allrisou(tate, vector<int>(yoko));//目指す配列
		vector<int> side(tate);//各行が初期状態と比べて右にどれだけ型抜きされているか
		map<int, int> move;//各行で余っている数字と足りない数字


		//初期状態と完成形の入力
		for (int i = 0; i < tate; i += 1) {
			for (int j = 0; j < yoko; j += 1) {
				allgenjou.at(i).at(j) = problem.board.start[i][j] - '0';
			}
		}
		for (int i = 0; i < tate; i += 1) {
			for (int j = 0; j < yoko; j += 1) {
				allrisou.at(i).at(j) = problem.board.goal[i][j] - '0';
			}
		}
		vector<vector<int> > genjou(tate, vector<int>(yoko));//型抜きに応じて変更する配列
		vector<vector<int> > risou(tate, vector<int>(yoko));//目指す配列
		for (int i = 0; i < tate; i += 1) {
			for (int j = 0; j < yoko; j += 1) {
				genjou.at(i).at(j) = allgenjou.at(i).at(j);
			}
			side.at(i) = 0;
		}
		for (int i = 0; i < tate; i += 1) {
			for (int j = 0; j < yoko; j += 1) {
				risou.at(i).at(j) = allrisou.at(i).at(j);
			}
		}

		
		Print << U"genjou.at(0).at(0) = " << genjou.at(0).at(0);

		// tentative program
		int result = 0;
		for (int i = 0; i < 5; i++) {
			std::this_thread::sleep_for(std::chrono::seconds(1));  // 1秒待機
			result += i;
			if (stopFlag) {
				Print << U"calculation canceled";
				return std::nullopt;
			}
			Print << U"Step " << i << U": result = " << result;
		}

		// store an information for return
		int n = 1;
		solution.n = n;
		Array<Op> operations;
		for (int i = 0; i < n; i++) {
			operations.emplace_back();
			operations[i].p = 4;
			operations[i].x = 0;
			operations[i].y = 0;
			operations[i].s = 2;
		}
		solution.ops = operations;

		return solution;  // 計算結果を返す
	}

};
