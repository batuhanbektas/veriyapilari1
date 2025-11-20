#ifndef MAINNODE_HPP   // HEADER GUARD BAŞI
#define MAINNODE_HPP

#include "ShapeList.hpp"   // SADECE ShapeList yeterli

class MainNode {
public:
    MainNode* prev;
    MainNode* next;
    ShapeList shapes;

    MainNode();
    ~MainNode() = default;
};

#endif // MAINNODE_HPP  // HEADER GUARD SONU
