/**
* @file MainList.cpp
* @description MainList sınıfının üye fonksiyonlarının tanımlandığı dosya
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 17.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/


#include <cstdlib>
#include <ctime>
#include "../include/MainList.hpp"
#include <iostream>

MainList::MainList() : head(nullptr), tail(nullptr), current(nullptr), size(0) {}

MainList::~MainList() {
    MainNode* temp = head;
    while (temp != nullptr) {
        MainNode* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
}

void MainList::addNode() {
    MainNode* n = new MainNode();

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
            // Rastgele bir shape tipi seç
            int t =rand() % 3;
            Shape* sh = nullptr;

            int x = rand() % (COLS - 5);
            int y = rand() % (ROWS - 5);
            int w = 2 + rand() % 10;
            int h = 2 + rand() % 10;
            char c = 'A' + rand() % 26;
            int z = rand() % 100;

            if(t == 0)
                sh = new Rectangle(x, y, w, h, c, z);
            else if(t == 1)
                sh = new Triangle(x, y, w, h, c, z);
            else
                sh = new Star(x, y, w, h, c, z);

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
