#pragma once

struct Op {
	int p;
	int x;
	int y;
	int s;


};

struct Solution {
	int n;
	Array<Op> ops;

	Solution(int n_)
		: n(n_), ops(n_) {}

	Solution()
		: n(0), ops(0) {}
};
