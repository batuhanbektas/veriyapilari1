/**
* @file MainList.cpp
* @description MainList sınıfının üye fonksiyonlarının tanımlandığı dosya
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 18.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "../include/MainList.hpp"
#include "../include/Rectangle.hpp"
#include "../include/Triangle.hpp"
#include "../include/Star.hpp"
#include "../include/Screen.hpp"
#include "../include/ShapeNode.hpp"
#include "MainNode.hpp"
#include "../include/ShapeList.hpp"
#include "../include/Shape.hpp"

using namespace std;

MainList::MainList() : head(nullptr), tail(nullptr), current(nullptr), size(0) {}

void MainList::clear() {
    MainNode* temp = head;
    while (temp != nullptr) {
        MainNode* toDelete = temp;
        temp = temp->next;
        delete toDelete;   
    }
    head    = nullptr;
    tail    = nullptr;
    current = nullptr;
    size    = 0;
}

MainList::~MainList() {
    clear();
}

void MainList::addNode(MainNode* n) {
    if (head == nullptr) {
        head = tail = current = n;
    } 
    else {
        tail->next = n;
        n->prev    = tail;
        tail       = n;
    }

    size++;
}

MainNode* MainList::getHead() const {
    return head;
}

void MainList::generateRandom(int count) {
    srand((unsigned)time(nullptr));

    for (int i = 0; i < count; i++) {
        MainNode* n = new MainNode();
        
        int shapeCount = 2 + (rand() % 6); 

        for (int s = 0; s < shapeCount; s++) {
            int t = rand() % 3;
            Shape* sh = nullptr;

            int w = 2 + rand() % 10; 
            int h = 2 + rand() % 10; 

            if (w >= COLS) w = COLS - 1;
            if (h >= ROWS) h = ROWS - 1;

            int maxX = COLS - w;
            int maxY = ROWS - h;

            if (maxX < 0) maxX = 0;
            if (maxY < 0) maxY = 0;

            int minX = 10;
            if (minX > maxX) minX = 0;

            int x = minX + (rand() % (maxX - minX + 1));
            int y = rand() % (maxY + 1);

            const char chars[] = { '#', '*', '&', '+', 'o' };
            char c = chars[rand() % 5];
            int z  = rand() % 100;

            if (t == 0)
                sh = new Rectangle(x, y, w, h, z, c);
            else if (t == 1)
                sh = new Triangle(x, y, w, h, z, c);
            else
                sh = new Star(x, y, w, h, z, c);

            n->shapes.addShape(sh);
        }

        addNode(n);
    }
}

void MainList::removeCurrent() {
    if (current == nullptr) return;

    MainNode* del = current;

    if (del->prev != nullptr) del->prev->next = del->next;
    if (del->next != nullptr) del->next->prev = del->prev;

    if (del == head) head = del->next;
    if (del == tail) tail = del->prev;

    if (del->next != nullptr)
        current = del->next;
    else
        current = del->prev;

    delete del;
    size--;
}

void MainList::drawAll(Screen& s) {
    if (current == nullptr)
        return;

    int count = current->shapes.getSize();
    if (count == 0)
        return;

    Shape** arr = new Shape*[count];

    ShapeNode* cur = current->shapes.getHead();
    for (int i = 0; i < count; ++i) {
        arr[i] = cur->data;
        cur    = cur->next;
    }

    for (int i = 0; i < count - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < count; ++j) {
            if (arr[j]->getZ() < arr[minIdx]->getZ()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Shape* tmp  = arr[i];
            arr[i]      = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }

    for (int i = 0; i < count; ++i) {
        arr[i]->draw(s);
    }

    delete[] arr;
}

void MainList::nextNode() {
    if (current && current->next != nullptr)
        current = current->next;
}

void MainList::prevNode() {
    if (current && current->prev != nullptr)
        current = current->prev;
}

MainNode* MainList::getCurrent() {
    return current;
}

int MainList::getSize() const {
    return size;
}

//-----------------------------------------------------
//  DOSYAYA KAYDETME
//-----------------------------------------------------
void MainList::saveToFile(const string& filename) const {
    ofstream out(filename.c_str());
    if (!out) {
        cerr << "Dosya acilamadi: " << filename << endl;
        return;
    }

    out << size << '\n';

    MainNode* node = head;
    while (node != nullptr) {
        int shapeCount = node->shapes.getSize();
        out << shapeCount << '\n';

        ShapeNode* sn = node->shapes.getHead();
        while (sn != nullptr) {
            Shape* sh = sn->data;

            char typeChar = 'R';
            if (dynamic_cast<Triangle*>(sh) != nullptr) {
                typeChar = 'T';
            }
            else if (dynamic_cast<Star*>(sh) != nullptr) {
                typeChar = 'S';
            }

            out << typeChar << ' '
                << sh->getX()      << ' '
                << sh->getY()      << ' '
                << sh->getWidth()  << ' '
                << sh->getHeight() << ' '
                << sh->getZ()      << ' '
                << sh->getDrawChar() << '\n';

            sn = sn->next;
        }

        node = node->next;
    }
}

//-----------------------------------------------------
//  DOSYADAN YÜKLEME
//-----------------------------------------------------
void MainList::loadFromFile(const string& filename) {
    ifstream in(filename.c_str());
    if (!in) {
        cerr << "Dosya acilamadi: " << filename << endl;
        return;
    }

    clear();    

    int nodeCount = 0;
    if (!(in >> nodeCount)) {
        cerr << "Dosya formati hatali (node sayisi okunamadi)." << endl;
        return;
    }

    for (int i = 0; i < nodeCount; ++i) {
        MainNode* node = new MainNode();

        int shapeCount = 0;
        if (!(in >> shapeCount)) {
            cerr << "Dosya formati hatali (shape sayisi okunamadi)." << endl;
            delete node;
            break;
        }

        for (int s = 0; s < shapeCount; ++s) {
            char typeChar;
            int x, y, w, h, z;
            char drawChar;

            if (!(in >> typeChar >> x >> y >> w >> h >> z >> drawChar)) {
                cerr << "Dosya formati hatali (shape bilgisi okunamadi)." << endl;
                break;
            }

            Shape* sh = nullptr;
            switch (typeChar) {
                case 'R':
                    sh = new Rectangle(x, y, w, h, z, drawChar);
                    break;
                case 'T':
                    sh = new Triangle(x, y, w, h, z, drawChar);
                    break;
                case 'S':
                    sh = new Star(x, y, w, h, z, drawChar);
                    break;
                default:
                    sh = new Rectangle(x, y, w, h, z, drawChar);
                    break;
            }

            node->shapes.addShape(sh);
        }

        addNode(node);
    }

    current = head;
}
