/**
* @file ShapeNode.cpp
* @description ShapeNode sınıfının üye fonksiyonlarının tanımlandığı dosya
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 17.11.2025
* @author Batuhan Bektaş
*/

#include "ShapeNode.hpp"

ShapeNode::ShapeNode(Shape* s)
    : data(s), next(nullptr)
{
}

// DİKKAT: Burada data silinmiyor.
// Shape nesnelerini silme işinden ShapeList sorumlu (removeIndex ve destructor).
ShapeNode::~ShapeNode()
{
}
