#ifndef PARENT_H
#define PARENT_H

class Parent {
private:
    int _x;
    int _y;
    int _z;
    int _position;

public:
    int getx() { return _x; }
    int gety() { return _y; }
    int getz() { return _z; }
    int get_position() { return _position; }

	Parent();
    Parent(int x, int y, int z, int position);
};


#endif //PARENT_H
