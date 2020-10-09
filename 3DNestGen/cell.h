#ifndef CELL_H
#define CELL_H

#include "stdafx.h"

class Cell {
private:
	std::vector<std::shared_ptr<Wall>> _walls{ };
	double _average_height;
	double _cartesian_x;
    double _cartesian_y;
    double _threshold_height;
	int _index;
	int _max_height;
	int _min_height;
    int _x;
    int _y;
    int _z;
    int _birth;
    int _neighbors;

    void calculate_height();
    int minimum_wall();

public:
	explicit Cell(double max_height);
    Cell(std::vector<std::shared_ptr<Wall>> walls, int index, int x, int y, int z, int step, int neighbors, double max_height);

	std::shared_ptr<Wall> get_wall_pointer(int position) { return _walls[position]; }
	double get_average_height() { return _average_height; }
    double get_cartesian_x() { return _cartesian_x; }
    double get_cartesian_y() { return _cartesian_y; }
	double get_min_height_scaled() { return _min_height / 40.0; }
	int get_index() { return _index; }
	int get_max_height() { return _max_height; }
    int get_min_height() { return _min_height; }
    int getx() { return _x; }
    int gety() { return _y; }
    int getz() { return _z; }
    int get_birth() { return _birth; }
    int get_neighbors() { return _neighbors; }

	void set_birthday(int step) { _birth = step; }

    void add_neighbors(int neighbors);
    void add_wall(Wall wall, int position);
    bool build(int steps = 60);
	bool wall_exists(int position);

	int sum_existing_walls();
	int sum_wall_ages(int current_step);
	int sum_wall_heights();

};

#endif //CELL_H
