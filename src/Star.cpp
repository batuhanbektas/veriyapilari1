/**
* @file Star.cpp
* @description Yıldız (artı işareti şeklinde) çizen sınıfın kaynak dosyası
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 17.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/

#include "Star.hpp"

using namespace std;

Star::Star(int x, int y, int width, int height, int z, char drawChar)
    : Shape(x, y, width, height, z, drawChar) {}

void Star::draw(Screen& screen) {
    int centerX = x + width / 2;
    int centerY = y + height / 2;

    for (int dx = 0; dx < width; ++dx) {
        screen.setPixel(x + dx, centerY, drawChar);
    }

    for (int dy = 0; dy < height; ++dy) {
        screen.setPixel(centerX, y + dy, drawChar);
    }
}
