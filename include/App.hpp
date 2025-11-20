#ifndef APP_HPP
#define APP_HPP

#include "MainList.hpp"
#include "MainNode.hpp"
#include "ShapeNode.hpp"
#include "Screen.hpp"

class App {
private:
    enum Mode {
        MODE_LIST,   // Sadece node listesi arasında gezinme
        MODE_SHAPE   // Seçili node'un şekilleri arasında gezinme
    };

    MainList  mainList;
    MainNode* currentMain;
    ShapeNode* currentShape;
    Mode      mode;          // aktif mod

    void renderAll(Screen& screen);
    void handleInput(char key);
    void drawNodeList(Screen& screen); // soldaki numara listesi

public:
    App();
    void run();
};

#endif
