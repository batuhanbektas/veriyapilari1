/**
* @file main.cpp
* @description Basit test: Ekrana birkaç şekil çizdirir
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 19.11.2025
* @author ...
*/

#include "Screen.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Star.hpp"

int main() {
    Screen screen;
    screen.clear();

    Rectangle rect(5, 3, 10, 4, 0, '#');
    Triangle tri(30, 5, 10, 6, 1, '*');
    Star star(50, 8, 7, 5, 2, '+');

    rect.draw(screen);
    tri.draw(screen);
    star.draw(screen);

    screen.render();

    return 0;
}
