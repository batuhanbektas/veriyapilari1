#include "../include/MainList.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ShapeList.hpp"

class MainNode {
public:
    MainNode* prev;
    MainNode* next;
    ShapeList shapes;

    MainNode();
};
