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

MainList::~MainList() {
    MainNode* temp = head;
    while (temp != nullptr) {
        MainNode* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
}

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




void MainList::generateRandom(int count) {
    srand(time(nullptr));

    for(int i=0; i<count; i++) {
        MainNode* n = new MainNode();
        
        // 2 ile 7 arası shape
        int shapeCount = 2 + (rand() % 6);

        for(int s=0; s<shapeCount; s++) {

            int t =rand() % 3;
            Shape* sh = nullptr;

            int x = rand() % (COLS - 5);
            int y = rand() % (ROWS - 5);
            int w = 2 + rand() % 10;
            int h = 2 + rand() % 10;
            const char chars[] = { '#', '*', '&' };
            char c = chars[rand() % 3];
            int z = rand() % 100;

                        
            if(t == 0)
                sh = new Rectangle(x, y, w, h, z, c);
            else if(t == 1)
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
    std::vector<Shape*> allShapes;

    // Tüm node'ları gez
    MainNode* temp = head;
    while(temp) {
        // Bu node'un shapes listesini diziye at
        ShapeNode* cur = temp->shapes.getHead();
        while(cur) {
            allShapes.push_back(cur->data);
            cur = cur->next;
        }
        temp = temp->next;
    }

    // Z-değerine göre sırala
    sort(allShapes.begin(), allShapes.end(),
              [](Shape* a, Shape* b) { return a->getZ() < b->getZ(); });

    // Tüm şekilleri ekrana çiz
    for(Shape* sh : allShapes) 
        sh->draw(s);
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

