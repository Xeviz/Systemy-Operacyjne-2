//
// Created by linuxarc on 05.04.24.
//

#include "Ball.h"
#include <cmath>
#include <GLFW/glfw3.h>
#include <random>
#include <functional>
#include <iostream>

Ball::Ball(float x, float y, int num, float rad, std::mt19937 gen) : pos_x(x), pos_y(y), number(num), radius(rad), gen(gen) {
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    rgb[0] = distribution(gen);
    rgb[1] = distribution(gen);
    rgb[2] = distribution(gen);
    timeToLive = 5;
    sleepTime = 2000;
    isSticky = false;
    initializeRandomDirectionAndVelocity();
}

Ball::~Ball() = default;

float Ball::getX() const {
    return pos_x;
}

float Ball::getY() const {
    return pos_y;
}

float Ball::getVelocity() const {
    return velocity;
}

float Ball::getDirection() const {
    return direction;
}


int Ball::getNumber() const {
    return number;
}

float Ball::getRadius() const {
    return radius;
}

float Ball::getR() const {
    return rgb[0];
}

float Ball::getG() const {
    return rgb[1];
}

float Ball::getB() const {
    return rgb[2];
}

void Ball::changePosition(float updatedX, float updatedY) {
    pos_x = updatedX;
    pos_y = updatedY;
}

void Ball::changeDirection(float updatedDirection) {
    direction = updatedDirection;
    reduceTTL();
}

void Ball::moveBall() {
    float move_x = getVelocity() * cos(getDirection() * M_PI / 180.0);
    float move_y = getVelocity() * sin(getDirection() * M_PI / 180.0);


    float new_x = getX() + move_x;
    float new_y = getY() + move_y;

    if (new_x - getRadius() < -1.0 || new_x + getRadius() > 1.0) {
        changeDirection(180.0 - getDirection());
    }

    if (new_y - getRadius() < -1.0 || new_y + getRadius() > 1.0) {
        changeDirection(-getDirection());
    }
    changePosition(new_x, new_y);
}

void Ball::moveStickyBall(Square square) {
    float move_y = getVelocity() * square.getDirection();
    float new_y = getY() + move_y;
    pos_y = new_y;



};

void Ball::checkIfCollide(Square square) {
    float closestX = std::clamp(pos_x, square.getPosX(), square.getPosX() + square.getWidth());
    float closestY = std::clamp(pos_y, square.getPosY(), square.getPosY() + square.getHeight());

    float distanceX = pos_x - closestX;
    float distanceY = pos_y - closestY;

    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    if (distanceSquared < (radius * radius) && !square.unstickBalls) {
        isSticky = true;
    }
}

void Ball::initializeRandomDirectionAndVelocity() {
    velocity = 0.001f;
    std::uniform_real_distribution<float> direction_distribution(1.0f, 180.0f);
    std::uniform_int_distribution<int> sleep_distribution(400, 1200);
    sleepTime = sleep_distribution(gen);
    direction = direction_distribution(gen);
}

int Ball::getTimeToLive() const {
    return timeToLive;
}

int Ball::getSleepTime() const {
    return sleepTime;
}

void Ball::reduceTTL() {
    timeToLive--;
}


void Ball::bounceFromSquare(Square square) {
    std::cout << number << "wydupcam x/y " << pos_x << ", " << pos_y << " direction " << getDirection() << std::endl;
    if (pos_x - getRadius() < square.getPosX() || pos_x + getRadius() > square.getPosX()+square.getWidth()) {
        changeDirection(180.0 - getDirection());
    }

    if (pos_y - getRadius() < square.getPosY() || pos_y + getRadius() > square.getPosY()+square.getHeight()) {
        changeDirection(-getDirection());
    }
    isSticky = false;
};

void Ball::drawBall() const {
    glColor3f(getR(), getG(), getB());
    glPointSize(1.0);
    int triangleAmount = 22;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(this->pos_x,this->pos_y);
    for(int i = 0; i<= triangleAmount; i++){
        glVertex2f(
                this->pos_x + (this->radius * cos(i*1.0 * M_PIf*2.0 / triangleAmount*1.0)),
                this->pos_y + (this->radius * sin(i*1.0 * M_PIf*2.0 / triangleAmount*1.0))
        );
    }
    glEnd();

    glFlush();
}



