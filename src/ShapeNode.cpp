#include "ShapeNode.hpp"

ShapeNode::ShapeNode(Shape* s) : data(s), next(nullptr) {}

ShapeNode::~ShapeNode() {
    delete data;
}
