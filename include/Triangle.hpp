#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : public Shape {
public:
    // height: üçgenin yüksekliği, width: taban genişliği gibi düşünebilirsin
    Triangle(int x, int y, int width, int height, int z, char drawChar);

    virtual void draw(Screen& screen) override;
};

#endif
