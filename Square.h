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
    float height;
    float width;
    std::mt19937 gen;
    public:

    float direction;
    int sleepTime;
    bool unstickBalls;
    [[nodiscard]] float getPosX() const;
    [[nodiscard]] float getPosY() const;
    [[nodiscard]] float getVelocity() const;
    [[nodiscard]] float getDirection() const;
    [[nodiscard]] float getHeight() const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] int getSleepTime() const;
    void moveSquare();
    void drawSquare() const;
    void bounceAndReroll();

    Square(float posX, float posY, float height, float width, const std::mt19937 &gen);
    ~Square();

};


#endif //SYSPROJEKT_SQUARE_H
