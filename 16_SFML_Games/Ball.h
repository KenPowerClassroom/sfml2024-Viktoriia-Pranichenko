#pragma once

class Ball
{
private:
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;

public:
    Ball(float startX, float startY, float initialVelocityX, float initialVelocityY)
        : positionX(startX), positionY(startY), velocityX(initialVelocityX), velocityY(initialVelocityY)
    {}

    void updatePosition()
    {
        positionX += velocityX;
        positionY += velocityY;
    }

    void bounceHorizontally()
    {
        velocityX = -velocityX;
    }

    void bounceVertically()
    {
        velocityY = -velocityY;
    }

    void applyPaddleBounce(int verticalSpeed)
    {
        velocityY = -verticalSpeed;
    }

    float getPositionX() const { return positionX; }
    float getPositionY() const { return positionY; }
    float getVelocityX() const { return velocityX; }
    float getVelocityY() const { return velocityY; }

    void setPosition(float newX, float newY)
    {
        positionX = newX;
        positionY = newY;
    }

    void setVelocity(float newVelocityX, float newVelocityY)
    {
        velocityX = newVelocityX;
        velocityY = newVelocityY;
    }
};
