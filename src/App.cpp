/**
 * @file App.cpp
 * @description Program akışı, kullanıcı etkileşimi, liste ve şekil kontrolü
 * @course Veri Yapıları 2-A
 * @assignment 1.Ödev
 * @date 19.11.2025
 * @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
 */

#include <iostream>
#include <conio.h>
#include <string>
#include "App.hpp"
#include "MainList.hpp"
#include "Shape.hpp"
#include "ShapeNode.hpp"
#include "Screen.hpp"

using namespace std;

App::App() {
    char secim;
    cout << "Sahne nasil yüklensin?\n";
    cout << "1) Dosyadan yukle (data.txt)\n";
    cout << "2) Rastgele olustur\n";
    cout << "Secim (1/2): ";
    cin >> secim;

    if (secim == '1') {
        mainList.loadFromFile("data.txt");

        if (mainList.getSize() == 0) {
            cout << "Dosya okunamadi ya da sahne bos. "
                         "Rastgele sahne olusturuluyor...\n";
            mainList.generateRandom(20);  
        }
    }
    else {
        mainList.generateRandom(20);      
    }

    currentMain  = mainList.getCurrent();
    currentShape = nullptr;
    mode         = MODE_LIST;   
}

void App::drawNodeList(Screen& screen) {
    MainNode* node = mainList.getHead();
    int idx = 0;
    int y   = 0;

    while (node && y < ROWS) {
        int displayIndex = idx + 1; 
        int shapeCount   = node->shapes.getSize();

        string line = to_string(displayIndex) + " (" + to_string(shapeCount) + ")";
        if (node == currentMain)
            line += " <--";

        for (size_t i = 0; i < line.size() && (int)i < COLS; ++i) {
            screen.setPixel((int)i, y, line[i]);
        }

        node = node->next;
        y++;
        idx++;
    }
}

void App::renderAll(Screen& screen) {
    mainList.drawAll(screen);

    drawNodeList(screen);

    if (mode == MODE_SHAPE && currentShape) {
        Shape* s = currentShape->data;
        screen.setPixel(s->getX(), s->getY(), '@'); 
    }
}

void App::handleInput(char key) {
    //---------------------------------------
    // 1) LİSTE MODU – ana liste düğümleri  
    //---------------------------------------
    if (mode == MODE_LIST) {
        if (key == 'w' || key == 'W') {
            mainList.prevNode();
            currentMain  = mainList.getCurrent();
            currentShape = nullptr;
            return;
        }
        if (key == 's' || key == 'S') {
            mainList.nextNode();
            currentMain  = mainList.getCurrent();
            currentShape = nullptr;
            return;
        }
        if ((key == 'f' || key == 'F') && currentMain) {
            mode         = MODE_SHAPE;
            currentShape = currentMain->shapes.getHead();
            return;
        }
        if (key == 'c' || key == 'C') {
            mainList.removeCurrent();
            currentMain  = mainList.getCurrent();
            currentShape = nullptr;
            return;
        }

        return;
    }

    //---------------------------------------
    // 2) ŞEKİL MODU – seçili node'un şekilleri
    //---------------------------------------
    if (mode == MODE_SHAPE) {

        if (currentMain && currentMain->shapes.isEmpty()) {
            mainList.removeCurrent();
            currentMain  = mainList.getCurrent();
            currentShape = nullptr;
            mode         = MODE_LIST;
            return;
        }

        if (!currentMain) {
            mode         = MODE_LIST;
            currentShape = nullptr;
            return;
        }

        if (key == 'g' || key == 'G') {
            mode         = MODE_LIST;
            currentShape = nullptr;
            return;
        }

        if (key == 'q' || key == 'Q') {
            if (currentShape && currentShape != currentMain->shapes.getHead()) {
                ShapeNode* iter = currentMain->shapes.getHead();
                while (iter && iter->next != currentShape)
                    iter = iter->next;
                if (iter) currentShape = iter;
            }
            return;
        }

        if (key == 'e' || key == 'E') {
            if (currentShape && currentShape->next)
                currentShape = currentShape->next;
            return;
        }

        if (key == 'c' || key == 'C') {
            if (currentMain && currentShape) {

                int index = 0;
                ShapeNode* iter = currentMain->shapes.getHead();
                while (iter && iter != currentShape) {
                    iter = iter->next;
                    index++;
                }

                if (!iter) return;

                currentMain->shapes.removeIndex(index);

                if (currentMain->shapes.isEmpty()) {
                    mainList.removeCurrent();              
                    currentMain  = mainList.getCurrent();  
                    currentShape = nullptr;
                    mode         = MODE_LIST;               
                    return;                                           
                     }

                currentShape = currentMain->shapes.getHead();
            }
            return;
        }

        if (currentShape) {
            Shape* s = currentShape->data;
            int dx = 0, dy = 0;

            if (key == 'w' || key == 'W') dy = -1; 
            if (key == 's' || key == 'S') dy =  1; 
            if (key == 'a' || key == 'A') dx = -1; 
            if (key == 'd' || key == 'D') dx =  1; 
            
            if (dx != 0 || dy != 0) {
                s->move(dx, dy);

                int x = s->getX();
                int y = s->getY();
                int w = s->getWidth();
                int h = s->getHeight();

                if (x < 0) x = 0;
                if (y < 0) y = 0;
                if (x + w > COLS) x = COLS - w;
                if (y + h > ROWS) y = ROWS - h;

                if (x < 0) x = 0;
                if (y < 0) y = 0;

                s->setPosition(x, y);
            }
        }

        return;
    }
}

void App::run() {
    Screen screen;
    char key = ' ';

    while (true) {
        screen.clear();
        renderAll(screen);
        screen.render();

        cout << "\n-------------------------\n";
        cout << "Node sayisi : " << mainList.getSize() << "\n";

        if (currentMain) {
            int shapeCount = currentMain->shapes.getSize();
            cout << "Aktif Node Shape sayisi : " << shapeCount << "\n";
        } else {
           cout << "Listede hic Node kalmadi.\n";
        }

        if (mode == MODE_LIST) {
            cout << "\n[LİSTE MODU]\n";
            cout << "(w/s) listede yukari/asagi\n";
            cout << "(f)   secili node'un sekillerine git\n";
            cout << "(c)   node sil\n";
        } else {
            cout << "\n[SEKİL MODU]\n";
            cout << "(w/a/s/d) sekli hareket ettir\n";
            cout << "(q) onceki sekil   (e) sonraki sekil\n";
            cout << "(c) sekil sil      (g) liste moduna don\n";
        }

        cout << "\n(0) Cikis (ve kaydet)\n";

        key = _getch();

        if (key == '0') {
            mainList.saveToFile("data.txt");
            break;
        }

        handleInput(key);
    }
}
