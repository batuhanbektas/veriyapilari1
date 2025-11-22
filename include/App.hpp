#ifndef APP_HPP
#define APP_HPP

#include "MainList.hpp"
#include "MainNode.hpp"
#include "ShapeNode.hpp"
#include "Screen.hpp"

class App {
private:
    enum Mode {
        MODE_LIST,   
        MODE_SHAPE   
    };

    MainList  mainList;
    MainNode* currentMain;
    ShapeNode* currentShape;
    Mode      mode;         
    void renderAll(Screen& screen);
    void handleInput(char key);
    void drawNodeList(Screen& screen); 

public:
    App();
    void run();
};

#endif
