#pragma once

enum GridState {
	EMPTY,
	CHERRY,
	SNAKE
};

struct GridCoord {
	unsigned int x = 0;
	unsigned int y = 0;
};