#pragma once
#include "Problem.h"
class SolverProcess
{
public:
	// function solve will be the main function of solving problem in the future
	static int solve(Problem problem) {
		int result = 0;
		for (int i = 0; i < 5; i++) {
			std::this_thread::sleep_for(std::chrono::seconds(1));  // 1秒待機
			result += i;
			Print << U"Step " << i << U": result = " << result;
		}
		return result;  // 計算結果を返す
	}
	/*static void Create() {
		solver = ChildProcess{ U"nitgc_solver.exe" };
		if (not solver) {
			Print << U"Failed to create a process";
		}
	}

	static void Send() {
		if (not solver)
		{
			throw Error{ U"Failed to create a process" };
		}
		solver.ostream() << 10 << std::endl;
		solver.ostream() << 20 << std::endl;
	}
	static void Receive() {
		int result;
		solver.istream() >> result;
		Print << U"result: " << result;
	}*/
//private:
//	static ChildProcess solver;
};
