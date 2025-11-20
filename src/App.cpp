/**
 * @file App.cpp
 * @description Program akışı, kullanıcı etkileşimi, liste ve şekil kontrolü
 * @course Veri Yapıları 2-A
 * @assignment 1.Ödev
 * @date 19.11.2025
 */

#include <iostream>
#include <conio.h>
#include "../include/App.hpp"
#include "../include/MainList.hpp"
#include "../include/Shape.hpp"
#include "../include/ShapeNode.hpp"
#include "../include/Screen.hpp"

App::App() {
    currentMain = mainList.head;
    currentShape = (currentMain ? currentMain->shapes.getHead() : nullptr);
}

void App::renderAll(Screen& screen) {
    mainList.drawAll(screen);

    // Seçili shape'i işaretleme (isteğe bağlı)
    if (currentShape) {
        Shape* s = currentShape->data;
        screen.setPixel(s->getX(), s->getY(), '@');  // seçili shape gösterge
    }
}

void App::handleInput(char key) {
    //---------------------------------------
    // NODE GEÇİŞİ
    //---------------------------------------
    if (key == 'd' || key == 'D') {
        mainList.nextNode();
        currentMain = mainList.getCurrent();
        currentShape = (currentMain ? currentMain->shapes.getHead() : nullptr);
        return;
    }
    else if (key == 'a' || key == 'A') {
        mainList.prevNode();
        currentMain = mainList.getCurrent();
        currentShape = (currentMain ? currentMain->shapes.getHead() : nullptr);
        return;
    }

    //---------------------------------------
    // SHAPE GEÇİŞİ
    //---------------------------------------
    if (!currentMain) return;

    if (key == 's' || key == 'S') {
        if (currentShape && currentShape->next)
            currentShape = currentShape->next;
        return;
    }
    else if (key == 'w' || key == 'W') {
        if (currentShape != currentMain->shapes.getHead()) {
            ShapeNode* iter = currentMain->shapes.getHead();
            while (iter->next != currentShape)
                iter = iter->next;
            currentShape = iter;
        }
        return;
    }

    //---------------------------------------
    // SHAPE HAREKETİ
    //---------------------------------------
    if (currentShape) {
        Shape* s = currentShape->data;

        if (key == 'i' || key == 'I') s->move(0, -1);  // yukarı
        if (key == 'k' || key == 'K') s->move(0, 1);   // aşağı
        if (key == 'j' || key == 'J') s->move(-1, 0);  // sol
        if (key == 'l' || key == 'L') s->move(1, 0);   // sağ
    }

    //---------------------------------------
    // SHAPE SİL
    //---------------------------------------
    if (key == 'x' || key == 'X') {
        if (currentMain && currentShape) {
            int index = 0;
            ShapeNode* iter = currentMain->shapes.getHead();

            while (iter && iter != currentShape) {
                iter = iter->next;
                index++;
            }

            currentMain->shapes.removeIndex(index);
            currentShape = currentMain->shapes.getHead();
        }
    }

    //---------------------------------------
    // NODE SİL
    //---------------------------------------
    if (key == 'z' || key == 'Z') {
        mainList.removeCurrent();
        currentMain = mainList.getCurrent();
        currentShape = (currentMain ? currentMain->shapes.getHead() : nullptr);
    }
}

void App::run() {
    Screen screen;
    char key = ' ';

    while (true) {
        screen.clear();
        renderAll(screen);
        screen.render();

        std::cout << "\n[ A ] <-- Node   |   Node --> [ D ]\n";
        std::cout << "[ W ] <-- Shape  |  Shape --> [ S ]\n";
        std::cout << "[ I J K L ] Move Shape\n";
        std::cout << "[ X ] Shape Sil   |   [ Z ] Node Sil\n";
        std::cout << "[ Q ] Çıkış\n";

        key = _getch();
        if (key == 'q' || key == 'Q') break;

        handleInput(key);
    }
}
