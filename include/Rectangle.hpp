#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int width, int height, int z, char drawChar);

    virtual void draw(Screen& screen) override;
};

#endif
