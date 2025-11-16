#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

class Rectangle : public Shape{

    public:
        Rectangle(int x, int y, int w, int h, char c, int z);
        void draw(Screen& s) override;
};


#endif