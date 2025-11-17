#ifndef SHAPE_HPP
#define SHAPE_HPP

class Screen;

class Shape {
protected:
    int x, y;
    int width, height;
    char drawChar;
    int z;

public:
    Shape(int x, int y, int w, int h, char c, int z);
    virtual ~Shape();

    virtual void draw(Screen& s) = 0;
    virtual void move(int dx, int dy);

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    int getZ() const;
    char getChar() const;

    void setPosition(int newX, int newY);
    void setSize(int newW, int newH);
    void setChar(char c);
    void setZ(int newZ);
};

#endif
