#ifndef MAINLIST_HPP
#define MAINLIST_HPP

#include "MainNode.hpp"

class MainList {
private:
    MainNode* head;
    MainNode* tail;
    MainNode* current;
    int size;

public:
    MainList();
    ~MainList();

    void addNode();          
    void removeCurrent();    

    void nextNode();         
    void prevNode();         

    MainNode* getCurrent();
    int getSize() const;
};

#endif
