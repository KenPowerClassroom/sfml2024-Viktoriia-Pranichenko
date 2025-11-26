#include "pch.h"
#include"../16_SFML_Games/Ball.h"

TEST(Ball, InitialPositionAndVelocity) {
    Ball ball(100.0f, 100.0f, 5.0f, 5.0f);

    EXPECT_FLOAT_EQ(ball.getPositionX(), 100.0f);
    EXPECT_FLOAT_EQ(ball.getPositionY(), 100.0f);
    EXPECT_FLOAT_EQ(ball.getVelocityX(), 5.0f);
    EXPECT_FLOAT_EQ(ball.getVelocityY(), 5.0f);
}

TEST(Ball, UpdatePosition) {
    Ball ball(100.0f, 100.0f, 5.0f, 5.0f);

    ball.updatePosition();
    EXPECT_FLOAT_EQ(ball.getPositionX(), 105.0f);
    EXPECT_FLOAT_EQ(ball.getPositionY(), 105.0f);
}

TEST(Ball, BounceHorizontally) {
    Ball ball(100.0f, 100.0f, 5.0f, 5.0f);

    ball.bounceHorizontally();
    EXPECT_FLOAT_EQ(ball.getVelocityX(), -5.0f);

    ball.updatePosition();
    EXPECT_FLOAT_EQ(ball.getPositionX(), 95.0f);
}

TEST(Ball, BounceVertically) {
    Ball ball(100.0f, 100.0f, 5.0f, 5.0f);

    ball.bounceVertically();
    EXPECT_FLOAT_EQ(ball.getVelocityY(), -5.0f);

    ball.updatePosition();
    EXPECT_FLOAT_EQ(ball.getPositionY(), 95.0f);
}

TEST(Ball, ApplyPaddleBounce) {
    Ball ball(100.0f, 100.0f, 5.0f, 5.0f);

    ball.applyPaddleBounce(7);
    EXPECT_FLOAT_EQ(ball.getVelocityY(), -7.0f);

    ball.applyPaddleBounce(10);
    EXPECT_FLOAT_EQ(ball.getVelocityY(), -10.0f);
}
