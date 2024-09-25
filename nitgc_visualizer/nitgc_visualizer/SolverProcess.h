#pragma once
class SolverProcess
{
public:
	// function solve will be the main function of solving problem in the future
	int solve() {

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

