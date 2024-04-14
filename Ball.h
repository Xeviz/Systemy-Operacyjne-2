#ifndef BALL_H
#define BALL_H

#include <string>
#include <random>

class Ball {
private:
    float pos_x;
    float pos_y;
    float velocity{};
    float direction{};
    float radius;
    int number;
    float rgb[3]{};
    int timeToLive;
    std::mt19937 gen;
public:
    [[nodiscard]] int getTimeToLive() const;

public:
    Ball(float x, float y, int num, float rad, std::mt19937 gen);
    ~Ball();

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getVelocity() const;
    [[nodiscard]] float getDirection() const;
    [[nodiscard]] float getRadius() const;
    [[nodiscard]] float getR() const;
    [[nodiscard]] float getG() const;
    [[nodiscard]] float getB() const;
    [[nodiscard]] int getNumber() const;
    void changePosition(float updatedX, float updatedY);
    void changeDirection(float updatedDirection);
    void reduceTTL();
    void moveBall();
    void drawBall() const;

private:
    void initializeRandomDirectionAndVelocity();
};

#endif // BALL_H
