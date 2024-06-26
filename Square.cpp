//
// Created by linuxarc on 14.04.24.
//

#include "Square.h"
#include <cmath>
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
    direction = 1;
    bounceAndReroll();
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
    pos_y = new_y;
}

void Square::bounceAndReroll(){
    std::uniform_real_distribution<float> velocity_distribution(0.005f, 0.025f);

    velocity = velocity_distribution(gen);

}
