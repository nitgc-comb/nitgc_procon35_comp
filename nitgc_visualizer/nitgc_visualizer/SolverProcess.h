#pragma once
#include "Problem.h"
#include "Solution.h"
class SolverProcess
{
public:
	// function solve will be the main function of solving problem in the future
	static std::optional<Solution> solve(Problem problem) {
		Solution solution;
		int result = 0;
		for (int i = 0; i < 5; i++) {
			std::this_thread::sleep_for(std::chrono::seconds(1));  // 1秒待機
			result += i;
			Print << U"Step " << i << U": result = " << result;
		}

		// store an information for return
		int n = 5;
		solution.n = n;
		Array<Op> operations;
		for (int i = 0; i < n; i++) {
			operations.emplace_back();
			operations[i].p = 4;
			operations[i].x = 5;
			operations[i].y = 6;
			operations[i].s = 2;
		}
		solution.ops = operations;


		return solution;  // 計算結果を返す
	}
};
