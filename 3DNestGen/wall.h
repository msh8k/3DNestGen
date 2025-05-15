#ifndef WALL_H
#define WALL_H

#include <unordered_set>
#include <string>

class Wall {
private:
    // TODO: refactor design to have walls "dumb", i.e., not know which Cells are parents of particular Walls
    Parent _parent1;
    Parent _parent2;
	int _birth;
	int _height;	

public:
    Wall(Parent parent1, Parent parent2, int birth);

	int get_birth() { return _birth; }
    int get_height() { return _height; }
	Parent get_parent1() { return _parent1; }
	Parent get_parent2() { return _parent2; }

    bool find_parent(int x, int y, int z, int position);
    void increment();
};

#endif //WALL_H
