#ifndef ADJUSTMENTS_H
#define ADJUSTMENTS_H

namespace Adjustments {
	const int _positions[6][3] = {
		{ 0,  1,  1 },
		{ 1,  1,  0 },
		{ 1,  0,  -1 },
		{ 0,  -1, -1 },
		{ -1, -1, 0 },
		{ -1, 0,  1 }
	};

	std::vector<int> adjust_coordinates(int x, int y, int z, int position);
	int opposite_position(int position);
}

#endif // ADJUSTMENTS_H
