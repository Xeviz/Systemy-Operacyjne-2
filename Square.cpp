//
// Created by linuxarc on 14.04.24.
//

#include "Square.h"
#include <GLFW/glfw3.h>
#include <random>

float Square::getPosX() const {
    return pos_x;
}

float Square::getPosY() const {
    return pos_y;
}

float Square::getVelocity() const {
    return velocity;
}

float Square::getDirection() const {
    return direction;
}

float Square::getHeight() const {
    return height;
}

float Square::getWidth() const {
    return width;
}

Square::Square(float posX, float posY, float height, float width, const std::mt19937 &gen)
        : pos_x(posX), pos_y(posY), height(height), width(width), gen(gen) {
    sleepTime = 400;
    direction = 1.0f;
    velocity = 0.001f;
    bounceAndReroll();
    unstickBalls = false;
}

Square::~Square() = default;

void Square::drawSquare() const {
    glColor3f(0.5, 0.5, 0.5);
    glPointSize(1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(getPosX(), getPosY());
    glVertex2f(getPosX(), getPosY()+getHeight());
    glVertex2f(getPosX()+getWidth(), getPosY());
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(getPosX()+getWidth(), getPosY()+getHeight());
    glVertex2f(getPosX(), getPosY()+getHeight());
    glVertex2f(getPosX()+getWidth(), getPosY());
    glEnd();

    glFlush();
}

void Square::moveSquare() {
    float move_y = getVelocity() * getDirection();
    float new_y = getPosY() + move_y;

    if(height + new_y >= 0.90 && getDirection()==1){
        bounceAndReroll();
        direction = -1;
    } else if(new_y <= -0.90 && getDirection()==-1){
        bounceAndReroll();
        direction = 1;
    }
    if (new_y > -0.20 && new_y+height < 0.20){
        unstickBalls = true;
    } else {
        unstickBalls = false;
    }
    pos_y = new_y;
}

void Square::bounceAndReroll(){
    std::uniform_int_distribution<int> sleep_distribution(400, 1200);
    sleepTime = sleep_distribution(gen);

}

int Square::getSleepTime() const {
    return sleepTime;
}
