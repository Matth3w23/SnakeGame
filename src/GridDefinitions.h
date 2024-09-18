#pragma once

enum GridState {
	EMPTY,
	CHERRY,
	SNAKE
};

enum GridDirection {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

struct GridCoord {
	int x = 0;
	int y = 0;
};