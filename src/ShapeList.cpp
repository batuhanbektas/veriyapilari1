#include "../include/ShapeList.hpp"
#include <iostream>

ShapeList::ShapeList() : head(nullptr), size(0) {}

ShapeList::~ShapeList() {
    ShapeNode* temp = head;
    while (temp != nullptr) {
        ShapeNode* del = temp;
        temp = temp->next;
        delete del;
    }
}

void ShapeList::addShape(Shape* s) {
    ShapeNode* n = new ShapeNode(s);

    if (head == nullptr) {
        head = n;
    } 
    else {
        ShapeNode* iter = head;
        while (iter->next != nullptr){
            iter = iter->next;
        }  
        iter->next = n;
    }
    size++;
}

void ShapeList::removeIndex(int index) {
    if (index < 0 || index >= size) return;

    ShapeNode* del = head;

    if (index == 0) {
        head = head->next;
        delete del;
    }
    else {
        ShapeNode* prev = nullptr;
        for (int i = 0; i < index; i++) {
            prev = del;
            del = del->next;
        }
        prev->next = del->next;
        delete del;
    }

    size--;
}

Shape* ShapeList::getShape(int index) {
    if (index < 0 || index >= size) return nullptr;

    ShapeNode* iter = head;
    for (int i = 0; i < index; i++) {
        iter = iter->next;
    }
    return iter->data;
}

int ShapeList::getSize() const {
    return size;
}
