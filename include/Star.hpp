#ifndef STAR_HPP
#define STAR_HPP

#include "Shape.hpp"

class Star : public Shape {
public:
    Star(int x, int y, int w, int h, char c, int z);
    void draw(Screen& s) override;
};

#endif