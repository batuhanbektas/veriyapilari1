#include "Shape.hpp"

Shape::Shape(int x, int y, int w, int h, char c, int z)
    : x(x), y(y), width(w), height(h), drawChar(c), z(z) {}

void Shape::move(int dx, int dy) {
    x += dx;
    y += dy;
}