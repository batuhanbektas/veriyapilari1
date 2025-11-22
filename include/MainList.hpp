#ifndef MAINLIST_HPP
#define MAINLIST_HPP

#include "MainNode.hpp"
#include "Screen.hpp" 
#include <string>


class MainList {
public:
    MainList();
    ~MainList();

    void addNode(MainNode* n);
    void generateRandom(int count);
    void removeCurrent();
    void drawAll(Screen& s);
    void nextNode();
    void prevNode();
    MainNode* getCurrent();
    MainNode* getHead() const;
    int getSize() const;

   
    void clear();
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

private:
    MainNode* head;
    MainNode* tail;
    MainNode* current;
    int size;
};


#endif
