#ifndef MAINNODE_HPP
#define MAINNODE_HPP

#include "ShapeList.hpp"

class MainNode{
    public:
        ShapeList shapes;
        MainNode* prev;
        MainNode* next;

        MainNode();
};

#endif