/**
* @file MainList.cpp
* @description MainList sınıfının üye fonksiyonlarının tanımlandığı dosya
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 19.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/


#include <cstdlib>
#include <ctime>
#include "../include/MainList.hpp"
#include <iostream>
#include <algorithm>
#include <vector>              
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

void MainList::addNode(MainNode* n) {
    if (head == nullptr) {
        head = tail = current = n;
    } 
    else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }

    size++;
}


MainList::~MainList() {
    MainNode* temp = head;
    while (temp != nullptr) {
        MainNode* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
}

MainNode* MainList::getHead() const {
    return head;
}



void MainList::generateRandom(int count) {
    srand(time(nullptr)); // tek sefer çağrılacağı için sorun yok

    for (int i = 0; i < count; i++) {
        MainNode* n = new MainNode();
        
        // 3 ile 10 arası shape (max 10 olacak şekilde)
        int shapeCount = 3 + (rand() % 8); // 3..10

        // Her node kendi rastgele seed’ine göre farklı sahneye sahip olsun
        unsigned int nodeSeed = static_cast<unsigned int>(time(nullptr)) + i * 37;
        srand(nodeSeed);

        for (int s = 0; s < shapeCount; s++) {
            int t = rand() % 3;
            Shape* sh = nullptr;

            // Boyutları seç
            int w = 2 + rand() % 10; // 2..11
            int h = 2 + rand() % 10; // 2..11

            // Ekranı aşmaması için garanti
            if (w >= COLS) w = COLS - 1;
            if (h >= ROWS) h = ROWS - 1;

            int maxX = COLS - w;
            int maxY = ROWS - h;

            if (maxX < 0) maxX = 0;
            if (maxY < 0) maxY = 0;

            // Solda liste için boşluk bırak
            int minX = 10;
            if (minX > maxX) minX = 0;

            int x = minX + (rand() % (maxX - minX + 1));
            int y = rand() % (maxY + 1);

            const char chars[] = { '#', '*', '&', '+', 'o' };
            char c = chars[rand() % 5];
            int z = rand() % 100;

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

    // Liste oluşturulduktan sonra tekrar ana random’u karıştır
    srand(static_cast<unsigned int>(time(nullptr)));
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
    // Hiç node yoksa hiçbir şey çizme
    if (current == nullptr)
        return;

    std::vector<Shape*> allShapes;

    // SADECE current node'un içindeki şekilleri al
    ShapeNode* cur = current->shapes.getHead();
    while (cur) {
        allShapes.push_back(cur->data);
        cur = cur->next;
    }

    // Z-değerine göre sırala (önce arkadakiler, sonra öndekiler)
    std::sort(allShapes.begin(), allShapes.end(),
              [](Shape* a, Shape* b) { return a->getZ() < b->getZ(); });

    // Sadece bu node'un şekillerini ekrana çiz
    for (Shape* sh : allShapes) {
        sh->draw(s);
    }
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

