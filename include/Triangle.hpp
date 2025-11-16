#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : public Shape {
    public:
        Triangle(int x, int y, int w, int h, char c, int z);
        void draw(Screen& s) override;
};

#endif