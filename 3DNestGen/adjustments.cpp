#include "stdafx.h"

std::vector<int> Adjustments::adjust_coordinates(int x, int y, int z, int position) {
	std::vector<int> coordinates = {x, y, z};

	for (int i = 0; i < 3; ++i) {
		coordinates[i] += _positions[position][i];
	}

	return coordinates;
}

int Adjustments::opposite_position(int position) {
	return (position > 2) ? position - 3 : position + 3;
}
