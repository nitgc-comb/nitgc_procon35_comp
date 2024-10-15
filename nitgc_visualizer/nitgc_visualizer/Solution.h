#pragma once

struct Op {
	int p;
	int x;
	int y;
	int s;

	Op()
		: p(0), x(0), y(0), s(0) {}

	Op(int p_, int x_, int y_, int s_)
		: p(p_), x(x_), y(y_), s(s_) {}

};

struct Solution {
	int n;
	Array<Op> ops;

	Solution(int n_)
		: n(n_), ops() {}

	Solution()
		: n(0), ops() {}
};
