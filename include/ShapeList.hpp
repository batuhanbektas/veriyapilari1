#ifndef SHAPELIST_HPP
#define SHAPELIST_HPP

#include "ShapeNode.hpp"

class ShapeList {
private:
    
    int size;

public:
    ShapeNode* head;
    ShapeList();
    ~ShapeList();

    void addShape(Shape* s);
    void removeIndex(int index);
    Shape* getShape(int index);
    int getSize() const;

    ShapeNode* getHead() const;  
};


#endif
