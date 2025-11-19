#ifndef STAR_HPP
#define STAR_HPP

#include "Shape.hpp"

class Star : public Shape {
public:
    // width ve height yıldızın yatay/dikey boyutunu belirliyor
    Star(int x, int y, int width, int height, int z, char drawChar);

    virtual void draw(Screen& screen) override;
};

#endif
