#ifndef SHAPE_HPP
#define SHAPE_HPP

class Screen;

class Shape{
    private:
        int x,y;
        int width,height;
        char drawChar;
        int z;
    public:

            Shape(int x, int y, int w, int h, char c, int z)
                : x(x),y(y), width(w), height(h), drawChar(c), z(z){}

            virtual ~Shape(){}

            
            virtual void draw(Screen& scr) = 0;
            virtual void move(int dx,int dy) = 0;

            int getX() const;
            int getY() const;
            int getWidth() const;
            int getHeight() const;
            int getZ() const;
            int getChar() const;

            void setPosition(int newX,int newY);
            void setSize(int newH, int newW);   
            void setChar(char c);
            void setZ(int newZ);

};

#endif