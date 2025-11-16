#ifndef SHAPELIST_HPP
#define SHAPELIST_HPP

#include "ShapeNode.hpp"

class ShapeList {
private:
    ShapeNode* head;

public:
    ShapeList();
    ~ShapeList();

    void addShape(Shape* s);
    void removeShape();
    Shape* getShape(int index);
};

#endif