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
