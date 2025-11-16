#ifndef MAINLIST_HPP
#define MAINLIST_HPP

#include "MainNode.hpp"

class MainList {
private:
    MainNode* head;
    MainNode* current;

public:
    MainList();
    ~MainList();

    void addNode();
    void removeNode();
    void nextNode();
    void prevNode();

    MainNode* getCurrent();
};

#endif