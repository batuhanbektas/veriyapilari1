#ifndef MAINLIST_HPP
#define MAINLIST_HPP

#include "MainNode.hpp"
#include <vector>

class MainList {
private:
    MainNode* head;
    MainNode* tail;
    MainNode* current;
    int size;

public:
    MainList();
    ~MainList();

 
    void addNode(MainNode* n);
      
    void removeCurrent();    

    void nextNode();         
    void prevNode();        
    

    void drawAll(Screen& s);


    MainNode* getCurrent();
    int getSize() const;

    void generateRandom(int count);

};

#endif
