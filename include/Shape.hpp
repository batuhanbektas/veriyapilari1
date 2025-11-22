#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Screen.hpp"

class Shape {
protected:
    int x;
    int y;
    int width;
    int height;
    int z;
    char drawChar;

public:
    Shape(int x, int y, int width, int height, int z, char drawChar);
    virtual ~Shape();

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    int getZ() const;
    char getDrawChar() const;

    void setPosition(int newX, int newY);
    void setZ(int newZ);

    virtual void draw(Screen& screen) = 0;
    virtual void move(int dx, int dy);
};

#endif
