#include "stdafx.h"

Wall::Wall(Parent parent1, Parent parent2, int birth) {
    _height = 0;
	_birth = birth;

    _parent1 = parent1;
    _parent2 = parent2;
}

bool Wall::find_parent(int x, int y, int z, int position) {
	if (_parent1.getx() == x && _parent1.gety() == y && _parent1.getz() == z && _parent1.get_position() == position) { return true; }
	if (_parent2.getx() == x && _parent2.gety() == y && _parent2.getz() == z && _parent2.get_position() == position) { return true; }
	return false;
}

void Wall::increment() { ++_height; }
