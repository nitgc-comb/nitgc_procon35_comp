#pragma once
class SolverProcess
{
	SolverProcess() {
		solver = ChildProcess{ U"nitgc_solver.exe" };
		if (not solver) {
			Print << U"Failed to create a process";
		}
	}
public:
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
	}
private:
	static ChildProcess solver;
};

