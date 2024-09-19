#pragma once
class SolverProcess
{
public:
	SolverProcess() {
		solver = ChildProcess{ U"solver.exe" };
		if (not solver) {
			Print << U"Failed to create a process";
		}
	}
private:
	static ChildProcess solver;
};

