#ifndef MAINNODE_HPP   
#define MAINNODE_HPP

#include "ShapeList.hpp"   

class MainNode {
public:
    MainNode* prev;
    MainNode* next;
    ShapeList shapes;

    MainNode();
    ~MainNode() = default;
};

#endif
