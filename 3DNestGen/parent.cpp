#include "stdafx.h"

Parent::Parent() {
	_x = 0;
	_y = 0;
	_z = 0;
	_position = 0;
}

Parent::Parent(int x, int y, int z, int position) {
    _x = x;
    _y = y;
    _z = z;
    _position = position;
}
