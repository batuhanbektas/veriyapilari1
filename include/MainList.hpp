#ifndef MAINLIST_HPP
#define MAINLIST_HPP

#include "MainNode.hpp"
#include <vector>

class MainList {
private:
    int size;

public:
    MainNode* head;
    MainNode* tail;
    MainNode* current;

    MainList();
    ~MainList();

    int getSize() const;

    void addNode(MainNode* n);
    void removeCurrent();

    void nextNode();
    void prevNode();

    void drawAll(Screen& s);

    MainNode* getCurrent();

    void generateRandom(int count);
};

#endif
