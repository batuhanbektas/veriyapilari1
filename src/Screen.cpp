/**
* @file Screen.cpp
* @description 25x80 karakterlik ekranda çizim yapan sınıfın kaynak dosyası
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 19.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/

#include <iostream>
#include "Screen.hpp"

Screen::Screen() {
    clear();
}

void Screen::clear() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            buffer[r][c] = ' ';
        }
    }
}

void Screen::setPixel(int x, int y, char c) {
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS) {
        return;
    }
    buffer[y][x] = c;
}

void Screen::render() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            std::cout << buffer[r][c];
        }
        std::cout << std::endl;
    }
}
