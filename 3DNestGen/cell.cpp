#include "stdafx.h"

void Cell::calculate_height() {
	int average = 0;
	int min = INT_MAX;
	int max = 0;
	int work1, work2;

	for (int i = 0; i < 6; i += 2) {
		work1 = _walls[i]->get_height();
		work2 = _walls[i + 1]->get_height();

		average += work1 + work2;

		if (work1 < work2) {
			if (work1 < min)
				min = work1;
			if (work2 > max) {
				max = work2;
			}
		}
		else{
			if (work2 < min)
				min = work2;
			if (work1 > max)
				max = work1;
		}
    }

    _min_height = min;
	_max_height = max;

	// Divide by 40 to scale 60 unit pulp loads back down to HCS scale (1 unit ~ 3.0 mm)
	// Average height also divided by 6 walls
	_average_height = average / 40.0 / 6.0;
}

int Cell::minimum_wall() {
    int minimum = _walls[0]->get_height();
    int test = 0;
    int location = 0;
    for (int i = 1; i < 6; ++i) {
        test = _walls[i]->get_height();
		if (test < minimum) {
			minimum = test;
			location = i;
		}
    }

    return location;
}

Cell::Cell(double max_height) {
	_index = 0;
	_x = 0;
	_y = 0;
	_z = 0;
	_birth = 0;
	_neighbors = 0;
	_threshold_height = max_height;

	_cartesian_x = 0.0;
	_cartesian_y = 0.0;
	
	for (int i = 0; i < 6; ++i) {
		_walls.emplace_back(nullptr);
	}

	_max_height = 0.0;
	_min_height = 0.0;
}

Cell::Cell(std::vector<std::shared_ptr<Wall>> walls, int index, int x, int y, int z, int step, int neighbors, double max_height) {
	_index = index;
	_x = x;
    _y = y;
    _z = z;
    _birth = step;
    _neighbors = neighbors;
    _threshold_height = max_height;

    _cartesian_x = (x + y) / 2.0;
    _cartesian_y = z / 2.0;
    _cartesian_y *= std::sqrt(3);

    for (int i = 0; i < 6; ++i) {
        _walls.push_back(walls[i]);
    }

	_max_height = 0.0;
    _min_height = 0.0;
}

void Cell::add_neighbors(int neighbors) {
    _neighbors += neighbors;
}

void Cell::add_wall(Wall wall, int position) {
    _walls[position] = std::make_shared<Wall>(wall);
	//Parent p1 = _walls[position]->get_parent1();
	//Parent p2 = _walls[position]->get_parent2();
	//std::cout << p1.getx() << p1.gety() << p1.getz() << p1.get_position() << std::endl;
	//std::cout << p2.getx() << p2.gety() << p2.getz() << p2.get_position() << std::endl;
}

bool Cell::build(int steps) {
	bool buildable = true;

	for (int i = 0; i < steps; ++i) {
        _walls[minimum_wall()]->increment();
    }

    calculate_height();

	// divide by 40.0 magic horseshit
    if ((_min_height / 40.0) >= _threshold_height) {
        buildable = false;
    }

	return buildable;
}

bool Cell::wall_exists(int position)
{
	if (_walls[position] == nullptr) { return false; }
	return true;
}

int Cell::sum_existing_walls()
{
	int sum = 0;
	for (int i = 0; i < 6; i++)	{
		if (_walls[i] != nullptr) {
			sum++;
		}
	}
	return sum;
}

int Cell::sum_wall_ages(int current_step)
{
	int sum = 0;
	for (int i = 0; i < 6; i++)	{
		if (_walls[i] != nullptr) {
			sum += (current_step - _walls[i]->get_birth());
		}
	}
	return sum;
}

int Cell::sum_wall_heights()
{
	int sum = 0;
	for (int i = 0; i < 6; i++) {
		if (_walls[i] != nullptr) {
			sum += _walls[i]->get_height();
		}
	}
	return sum;
}
