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
	static void storeSolution(Solution* sln, int p, int x, int y, int s) {
		Op op(p,x,y,s);

		sln->ops.push_back(op);

		sln->n = sln->ops.size();

		return;
		
	}

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
	static std::optional<Solution> solve(Problem problem, std::atomic<bool>& stopFlag, int* ummatchCount) {
		Solution solution;
		/*Array<Op> operations;
		Op op;*/

		*ummatchCount = 0;

		int tate, yoko;//ボートの縦と横
		tate = problem.board.height;
		yoko = problem.board.width;
		//cout << min(tate, yoko) << endl;
		//int tesuu = 0;
		vector<vector<int> > allgenjou(tate, vector<int>(yoko));//型抜きに応じて変更する配列
		vector<vector<int> > allrisou(tate, vector<int>(yoko));//目指す配列
		//vector<int> side(tate);//各行が初期状態と比べて右にどれだけ型抜きされているか
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


		for (int swapping = 0; swapping < 1; swapping += 1) {
			vector<int> side(tate);//各行が初期状態と比べて右にどれだけ型抜きされているか
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
			//型抜きを行う場所の候補を示す。一定の範囲内に抜くべきでない数字が1つ以下である場所をリストアップ
			//以下の基準で順位付けする。
			//1.範囲をnとしたときにfloor(log(2,n))のあたいが大きい(1-1,2~3-2.4~7-3...)
			//2,1の基準が等しい場合は範囲が狭いもの
			//3,盤上でより左にあるもの
			set<pint> addedway;
			set<pair<pint, pint>> freeway2;
			set<pair<pint, pint>> limitway2;
			pint way;
			int sorted = -1000;
			int waywidth;
			int score = 0;
			int score2 = 0;
			int raw = -1;
			set<pair<pint, pint>> deleteway;
			pint research = make_pair(0, yoko);
			for (int count = 0; count < tate - 1; count += 1) {
				Print << count;
				
				for (int i = 0; i < 4; i += 1) {
					move[i] = 0;
				}
				for (int i = 0; i < yoko; i += 1) {
					move[risou.at(tate - 1 - count).at(i)] += 1;
					move[genjou.at(tate - 1).at((i + side.at(tate - 1)) % yoko)] -= 1;
				}
				int timer = 0;
				do {
					for (int i = research.first, j = research.first, j2 = research.first; i != research.second;) {
						while (j < research.second) {
							j += 1;
							move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] += 1;
							if (move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] > 0) {
								move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] -= 1;
								j -= 1;
								break;
							}
						}
						if (j2 != j) {
							int wid = floor(pow(2, floor(0.0005 + log((j - i) * 1.0) / log(2))));
							freeway2.insert(make_pair(make_pair(-wid, j - 1 - i), make_pair(i, j - 1)));
							addedway.insert(make_pair(i, j - 1));
						}
						i += 1;
						move[genjou.at(tate - 1).at((i - 1 + side.at(tate - 1)) % yoko)] -= 1;
						if (i > j) {
							j += 1;
							move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] += 1;
						}
						j2 = j;
					}
					if (addedway.size() == 0) {
						//Print << move[0] << move[1] << move[2] << move[3];
						break;
					}
					int i = addedway.begin()->first, j = addedway.begin()->first;
					while (j != addedway.begin()->second + 1) {
						j += 1;
						move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] += 1;
					}
					for (auto p : addedway) {
						while (i != p.first) {
							i += 1;
							move[genjou.at(tate - 1).at((i - 1 + side.at(tate - 1)) % yoko)] -= 1;
						}
						while (j < p.second + 1) {
							j += 1;
							move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] += 1;
						}
						if (j < yoko - 1) {
							int j2 = j;
							j += 1;
							move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] += 1;
							while (j < yoko) {
								j += 1;
								move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] += 1;
								if (move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] > 0) {
									move[genjou.at(tate - 1).at((j - 1 + side.at(tate - 1)) % yoko)] -= 1;
									j -= 1;
									break;
								}
							}
							if (j2 + 1 < j) {
								int wid = floor(pow(2, floor(0.0005 + log((j - i) * 1.0) / log(2))));
								limitway2.insert(make_pair(make_pair(-wid, j - 1 - i), make_pair(i, j - 1)));

							}
						}
					}
					while (i != j) {
						i += 1;
						move[genjou.at(tate - 1).at((i - 1 + side.at(tate - 1)) % yoko)] -= 1;
					}

					addedway.clear();
					//型抜きを行う場所がない=その行に数字がすべてそろっているという事なので、その行はそろっている
					if (freeway2.size() == 0 && limitway2.size() == 0) {
						//Print << U"-------------------------------------";
						break;
					}
					//型抜き範囲の真上において何行目から型抜きをしてくるのが一番効率がいいかを判断する。
					//本来この時点で、条件のいい型抜き方法がない場合、型抜きの範囲の真上以外からも探す。
					way = freeway2.begin()->second;
					waywidth = -freeway2.begin()->first.first - 1;
					score = 0;
					score2 = 0;
					raw = -1;
					if (limitway2.size() != 0 && -limitway2.begin()->first.first - 1 > -freeway2.begin()->first.first) {
						way = limitway2.begin()->second;
						waywidth = -limitway2.begin()->first.first - 1;
					}
					way.second = way.first + waywidth;
					for (int i = 0; i < 4; i += 1) {
						score += (move[i] + abs(move[i])) / 2;
					}
					for (int i = way.first; i <= way.second; i += 1) {
						move[genjou.at(tate - 1).at((i + side.at(tate - 1)) % yoko)] += 1;
					}


					for (int i2 = 0; i2 < yoko; i2 += 1) {
						int rotate = (i2 + 1) / 2 * round(pow(-1, i2));
						//Print << U"rotate:" << rotate;
						rotate = (rotate + yoko) % yoko;
						score2 = score;
						int sc2 = score;
						for (int i = max(sorted + 1, 0); i < tate - 1; i += 1) {
							int sc = 0;
							for (int j = way.first; j <= way.second; j += 1) {
								move[genjou.at(i).at((j + side.at(i) + rotate) % yoko)] -= 1;
							}
							for (int i3 = 0; i3 < 4; i3 += 1) {
								sc += (move[i3] + abs(move[i3])) / 2;
							}
							if (sc < score) {
								sc2 = sc;
								score = sc;
								raw = i;
								if (sc == score2 - (way.second + 1 - way.first)) {
									for (int j = way.first; j <= way.second; j += 1) {
										move[genjou.at(i).at((j + side.at(i) + rotate) % yoko)] += 1;
									}
									break;
								}
							}
							for (int j = way.first; j <= way.second; j += 1) {
								move[genjou.at(i).at((j + side.at(i) + rotate) % yoko)] += 1;
							}
						}
						if (score2 != sc2 && raw != -1) {
							if (i2 != 0) {
								int rotate2 = ((rotate + yoko/2) % yoko) - yoko/2;
								side.at(raw) = (side.at(raw) + rotate) % yoko;
								cout << rotate << endl;
								if (rotate2 < 0) {
									rotate2 *= -1;
									if (rotate2 <= 2 || raw >= tate - 2) {
										cout << max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)) << " " << yoko - rotate2 << " " << raw << " " << 3 << endl;
										storeSolution(&solution, max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)), yoko - rotate2, raw, 3);
										//tesuu += 1;
									}
									else {
										cout << max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)) << " " << yoko - rotate2 << " " << raw << " " << 3 << endl;
										cout << max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)) << " " << 0 << " " << raw + 2 << " " << 2 << endl;
										storeSolution(&solution, max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)), yoko - rotate2, raw, 3);
										storeSolution(&solution, max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)), 0, raw + 2, 2);
										//tesuu += 2;
									}

								}
								else {
									if (rotate2 <= 2 || raw >= tate - 2) {
										cout << max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)) << " " << rotate2 << " " << raw << " " << 2 << endl;
										storeSolution(&solution, max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)), rotate2, raw, 2);
										//tesuu += 1;
									}
									else {
										cout << max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)) << " " << rotate2 << " " << raw << " " << 2 << endl;
										cout << max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)) << " " << yoko - rotate2 << " " << raw + 2 << " " << 3 << endl;
										storeSolution(&solution, max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)), rotate2, raw, 2);
										storeSolution(&solution, max(round(ceil(log(rotate2 * 1.0) / log(2) - 0.001) * 3 - 1), round(0)), yoko - rotate2, raw + 2, 3);
										//tesuu += 2;
									}
								}
							}
							break;
						}
					}
					for (int i = way.first; i <= way.second; i += 1) {
						move[genjou.at(raw).at((i + side.at(raw)) % yoko)] -= 1;
					}
					if (timer < 30 && count >= 29) {
						timer += 1;
						//cout<<timer<<"*"<<raw<<" "<<way.first<<" "<<way.second<<" "<<sorted<<endl;
						//cout<<move[0]<<" "<<move[1]<<" "<<move[2]<<" "<<move[3]<<endl;
					}
					//型抜きを行う
					while (raw != tate - 1) {
						//tesuu += 1;
						if (raw - sorted >= waywidth) {
							cout << max(round(floor(log(waywidth + 1.0001) / log(2)) * 3 - 1), round(0)) << " " << way.first << " " << raw - max(0, waywidth - 1) << " " << 0 << endl;
							storeSolution(&solution, max(round(floor(log(waywidth + 1.0001) / log(2)) * 3 - 1), round(0)), way.first, raw - max(0, waywidth - 1), 0);
							downshape(&genjou, side, floor(log(waywidth + 1.0001) / log(2)) * 3, way.first, raw - max(0, waywidth - 1));
							raw = tate - 1;
						}
						else {
							cout << max(round(floor(log(waywidth + 1.0001) / log(2)) * 3 - 1), round(0)) << " " << way.first << " " << sorted + 1 + ((raw - sorted + 1) % 2) << " " << 0 << endl;
							storeSolution(&solution, max(round(floor(log(waywidth + 1.0001) / log(2)) * 3 - 1), round(0)), way.first, sorted + 1 + ((raw - sorted + 1) % 2), 0);
							downshape(&genjou, side, floor(log(waywidth + 1.0001) / log(2)) * 3, way.first, sorted + 1 + ((raw - sorted + 1) % 2));
							raw = tate - 1 - min((tate - 1 - raw) / 2, (waywidth / 2 - (raw - sorted - 1) / 2));
						}
					}
					freeway2.clear();
					limitway2.clear();
				} while (true);

				//一番下のラインを一番上にあげる
				cout << 22 << " " << 0 << " " << tate - 257 << " " << 0 << endl;
				storeSolution(&solution, 22, 0, tate - 257, 0);
				//tesuu += 1;
				downshape(&genjou, side, 22, 0, tate - 257);
				sorted = count;
			}
			cout << 22 << " " << 0 << " " << tate - 257 << " " << 0 << endl;
			storeSolution(&solution, 22, 0, tate - 257, 0);
			//tesuu += 1;
			downshape(&genjou, side, 22, 0, tate - 257);
			for (int i = 0; i < tate; i += 1) {
				//int kazu[4] = { 0,0,0,0 };
				for (int j = 0; j < yoko; j += 1) {
					allgenjou.at(i).at(j) = genjou.at(i).at((j + side.at(i)) % yoko);
				}
				//Print << kazu[0] << kazu[1] << kazu[2] << kazu[3];
			}
		}














		swap(tate, yoko);
		for (int swapping = 1; swapping < 2; swapping += 1) {
			vector<int> side(tate);//各行が初期状態と比べて右にどれだけ型抜きされているか
			vector<vector<int> > genjou(tate, vector<int>(yoko));//型抜きに応じて変更する配列
			vector<vector<int> > risou(tate, vector<int>(yoko));//目指す配列
			for (int i = 0; i < tate; i += 1) {
				for (int j = 0; j < yoko; j += 1) {
					genjou.at(i).at(j) = allgenjou.at(j).at(i);
				}
				side.at(i) = 0;
			}
			for (int i = 0; i < tate; i += 1) {
				for (int j = 0; j < yoko; j += 1) {
					risou.at(i).at(j) = allrisou.at(j).at(i);
				}
			}
			/*for (int i = 0; i < tate; i += 1) {
				for (int j = 0; j < yoko; j += 1) {
					cout<<genjou.at(i).at(j)<<" ";
				}
				cout<<endl;
			}
			cout<<endl;*/
			//型抜きを行う場所の候補を示す。一定の範囲内に抜くべきでない数字が1つ以下である場所をリストアップ
			//以下の基準で順位付けする。
			//1.範囲をnとしたときにfloor(log(2,n))のあたいが大きい(1-1,2~3-2.4~7-3...)
			//2,1の基準が等しい場合は範囲が狭いもの
			//3,盤上でより左にあるもの
			set<pint> addedway;
			set<pair<pint, pint>> freeway2;
			set<pair<pint, pint>> limitway2;
			pint way;
			int sorted = -1000;
			int waywidth;
			int score = 0;
			int score2 = 0;
			int raw = -1;
			set<pair<pint, pint>> deleteway;
			pint research = make_pair(0, yoko);
			for (int count = 0; count < tate - 1; count += 1) {
				//Print << count;
				int timer = 0;
				do {
					for (int j = research.first, j2 = research.first; j2 < research.second;) {
						while (j < research.second && genjou.at(tate - 1).at(j) == risou.at(tate - 1 - count).at(j)) {
							j += 1;
						}
						j2 = j;
						if (j < research.second) {
							while (j < research.second && genjou.at(tate - 1).at(j) != risou.at(tate - 1 - count).at(j)) {
								j += 1;
							}
							int wid = floor(pow(2, floor(0.0005 + log((j - j2) * 1.0) / log(2))));
							freeway2.insert(make_pair(make_pair(-wid, j - 1 - j2), make_pair(j2, j - 1)));
							addedway.insert(make_pair(j2, j - 1));
						}
					}
					//cout<<"a"<<endl;
					addedway.clear();
					//型抜きを行う場所がない=その行に数字がすべてそろっているという事なので、その行はそろっている
					if (freeway2.size() == 0 && limitway2.size() == 0) {
						break;
					}
					//型抜き範囲の真上において何行目から型抜きをしてくるのが一番効率がいいかを判断する。
					//本来この時点で、条件のいい型抜き方法がない場合、型抜きの範囲の真上以外からも探す。
					way = freeway2.begin()->second;
					waywidth = -freeway2.begin()->first.first - 1;
					score = 0;
					score2 = 0;
					raw = -1;
					if (!limitway2.empty()) {
						if (-limitway2.begin()->first.first - 1 > -freeway2.begin()->first.first) {
							way = limitway2.begin()->second;
							waywidth = -limitway2.begin()->first.first - 1;
							score = 1;
						}
					}
					way.second = way.first + waywidth;
					score2 = score;
					for (int i = max(sorted + 1, 0); i < tate - 1; i += 1) {
						int sc = 0;
						for (int j = way.first; j <= way.second; j += 1) {
							if (genjou.at(i).at(j) == risou.at(tate - 1 - count).at(j)) {
								sc += 1;
							}
						}
						if (sc > score) {
							score = sc;
							raw = i;
							if (sc == (way.second + 1 - way.first)) {
								break;
							}
						}
					}
					//型抜きを行う
					while (raw != tate - 1) {
						//tesuu += 1;
						/*if (pow(2, floor(log(waywidth + 1.0001) / log(2))) - waywidth != 1) {
							Print << U"oh";
						}*/
						//Print << pow(2,floor(log(waywidth + 1.0001) / log(2)))-waywidth;
						if (raw - sorted >= waywidth) {
							cout << floor(log(waywidth + 1.0001) / log(2)) * 3 << " " << raw - max(0, waywidth - 1) << " " << way.first << " " << 2 << endl;
							storeSolution(&solution, floor(log(waywidth + 1.0001) / log(2)) * 3, raw - max(0, waywidth - 1), way.first, 2);
							downshape(&genjou, side, floor(log(waywidth + 1.0001) / log(2)) * 3, way.first, raw - max(0, waywidth - 1));
							raw = tate - 1;
						}
						else {
							cout << floor(log(waywidth + 1.0001) / log(2)) * 3 << " " << sorted + 1 + ((raw - sorted + 1) % 2) << " " << way.first << " " << 2 << endl;
							storeSolution(&solution, floor(log(waywidth + 1.0001) / log(2)) * 3, sorted + 1 + ((raw - sorted + 1) % 2), way.first, 2);
							downshape(&genjou, side, floor(log(waywidth + 1.0001) / log(2)) * 3, way.first, sorted + 1 + ((raw - sorted + 1) % 2));
							raw = tate - 1 - min((tate - 1 - raw) / 2, (waywidth / 2 - (raw - sorted - 1) / 2));
						}
					}
					freeway2.clear();
					limitway2.clear();
					timer += 1;
				} while (true);

				//一番下のラインを一番上にあげる
				cout << 22 << " " << tate - 257 << " " << 0 << " " << 2 << endl;
				storeSolution(&solution, 22, tate - 257, 0, 2);
				//tesuu += 1;
				downshape(&genjou, side, 22, 0, tate - 257);
				sorted = count;
			}
			cout << 22 << " " << tate - 257 << " " << 0 << " " << 2 << endl;
			storeSolution(&solution, 22, tate - 257, 0, 2);
			//tesuu += 1;
			downshape(&genjou, side, 22, 0, tate - 257);
			for (int i = 0; i < tate; i += 1) {
				for (int j = 0; j < yoko; j += 1) {
					allgenjou.at(j).at(i) = genjou.at(i).at(j);
				}
			}
			swap(tate, yoko);
			cout << solution.n << endl;
		}


		//count unmatched
		for (int i = 0; i < allgenjou.size(); i++) {
			for (int j = 0; j < allgenjou.at(0).size(); j++) {
				if (allgenjou.at(i).at(j) != allrisou.at(i).at(j)) {
					*ummatchCount++;
				}
			}
		}



		return solution;  // 計算結果を返す
	}

};
