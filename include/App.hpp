#ifndef APP_HPP
#define APP_HPP

#include "MainList.hpp"
#include "Screen.hpp"
#include "MainNode.hpp"
#include "ShapeNode.hpp"
#include <iostream>


class App {
private:
    MainList mainList;
    MainNode* currentMain;  
    ShapeNode* currentShape;

public:
    App();
    void run();
    void handleInput(char key);
    void renderAll(Screen& s);
};

#endif
