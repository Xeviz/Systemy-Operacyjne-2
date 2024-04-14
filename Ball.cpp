//
// Created by linuxarc on 05.04.24.
//

#include "Ball.h"
#include <cmath>
#include <GLFW/glfw3.h>
#include <random>

Ball::Ball(float x, float y, int num, float rad, std::mt19937 gen) : pos_x(x), pos_y(y), number(num), radius(rad), gen(gen) {
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    rgb[0] = distribution(gen);
    rgb[1] = distribution(gen);
    rgb[2] = distribution(gen);
    timeToLive = 5;
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

void Ball::initializeRandomDirectionAndVelocity() {
    std::uniform_real_distribution<float> velocity_distribution(0.005f, 0.025f);
    velocity = velocity_distribution(gen);

    std::uniform_real_distribution<float> direction_distribution(1.0f, 180.0f);
    direction = direction_distribution(gen);
}

int Ball::getTimeToLive() const {
    return timeToLive;
}

void Ball::reduceTTL() {
    timeToLive--;
}

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
