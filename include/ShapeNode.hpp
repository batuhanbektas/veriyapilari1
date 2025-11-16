#ifndef SHAPENODE_HPP
#define SHAPENODE_HPP

#include "Shape.hpp"

class ShapeNode {
public:
    Shape* data;
    ShapeNode* next;

    ShapeNode(Shape* s);
};

#endif