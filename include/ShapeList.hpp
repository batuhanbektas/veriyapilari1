#ifndef SHAPELIST_HPP
#define SHAPELIST_HPP

#include "ShapeNode.hpp"

class ShapeList {
private:
    ShapeNode* head;
    int size;

public:
    ShapeList();
    ~ShapeList();

    void addShape(Shape* s);
    void removeIndex(int index);
    Shape* getShape(int index);
    int getSize() const;
};

#endif
