#pragma once
struct GeneralPattern {
	int p;
	int width;
	int height;
	Array<String> cells;

	GeneralPattern(int p_, int width_, int height_)
		: p(p_), width(width_), height(height_), cells(height_) {}

	GeneralPattern()
		: width(0), height(0), cells(0) {}
};


struct General {
	int n;
	Array<GeneralPattern> patterns;

	General(int n_)
		: n(n_), patterns(n_) {}

	General()
		: n(0), patterns(0) {}
};

struct Board {
	int width;
	int height;
	Array<String> start;
	Array<String> goal;

	Board(int width_, int height_)
		:width(width_), height(height_), start(height_), goal(height_) {}

	Board()
		: width(0), height(0), start(0), goal(0) {}

};

struct Problem {
	Board board;
	General general;
};
