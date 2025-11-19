/**
* @file ShapeNode.cpp
* @description ShapeNode sınıfının üye fonksiyonlarının tanımlandığı dosya
* @course Veri Yapıları 2-A
* @assignment 1.Ödev
* @date 17.11.2025
* @author Batuhan Bektaş batuhan.bektas1@ogr.sakarya.edu.tr G231210379
*/


#include "ShapeNode.hpp"

ShapeNode::ShapeNode(Shape* s) : data(s), next(nullptr) {}

ShapeNode::~ShapeNode() {
    delete data;
}
