//
// Created by linuxarc on 14.04.24.
//

#ifndef SYSPROJEKT_SQUARE_H
#define SYSPROJEKT_SQUARE_H


#include <random>

class Square {

private:


    float pos_x;
    float pos_y;
    float velocity{};
    int direction;
    float height;
    float width;
    std::mt19937 gen;
public:
    float getPosX() const;
    float getPosY() const;
    float getVelocity() const;
    float getDirection() const;
    float getHeight() const;
    float getWidth() const;
    void moveSquare();
    void drawSquare() const;
    void bounceAndReroll();

    Square(float posX, float posY, float height, float width, const std::mt19937 &gen);
    ~Square();


};


#endif //SYSPROJEKT_SQUARE_H
