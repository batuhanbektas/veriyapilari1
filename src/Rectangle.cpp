/**
* @file Rectangle.cpp
* @description Dikdörtgen şeklini ekrana çizen sınıfın kaynak dosyası
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 19.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/

#include "Rectangle.hpp"

Rectangle::Rectangle(int x, int y, int width, int height, int z, char drawChar)
    : Shape(x, y, width, height, z, drawChar) {}

void Rectangle::draw(Screen& screen) {
    // Basit dolu dikdörtgen
    for (int dy = 0; dy < height; ++dy) {
        for (int dx = 0; dx < width; ++dx) {
            screen.setPixel(x + dx, y + dy, drawChar);
        }
    }
}
