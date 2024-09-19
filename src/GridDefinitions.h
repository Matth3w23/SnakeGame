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

bool operator==(const GridCoord& lhs, const GridCoord& rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}