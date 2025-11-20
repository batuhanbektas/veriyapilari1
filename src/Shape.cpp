/**
* @file Shape.cpp
* @description Shape soyut sınıfının üye fonksiyonlarının tanımlandığı dosya
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 17.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/

#include "Shape.hpp"

Shape::Shape(int x, int y, int width, int height, int z, char drawChar)
    : x(x), y(y), width(width), height(height), z(z), drawChar(drawChar) {}

Shape::~Shape() {}

int Shape::getX() const { return x; }
int Shape::getY() const { return y; }
int Shape::getWidth() const { return width; }
int Shape::getHeight() const { return height; }
int Shape::getZ() const { return z; }
char Shape::getDrawChar() const { return drawChar; }

void Shape::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Shape::setZ(int newZ) {
    z = newZ;
}

void Shape::move(int dx, int dy) {
    x += dx;
    y += dy;
}
