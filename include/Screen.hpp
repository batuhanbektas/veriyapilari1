#ifndef SCREEN_HPP
#define SCREEN_HPP

#define ROWS 25
#define COLS 80

class Screen {
private:
    char buffer[ROWS][COLS];

public:
    Screen();
    void clear();
    void setPixel(int x, int y, char c);
    void render();
};

#endif