#include <SFML/Graphics.hpp>
#include <time.h>
#include "Ball.h"
using namespace sf;

const int WINDOW_WIDTH = 520;
const int WINDOW_HEIGHT = 450;

const int FRAMERATE_LIMIT = 60;

const float PADDLE_START_POSITION_X = 300.0f;
const float PADDLE_START_POSITION_Y = 420.0f;

const int TOTAL_BLOCKS = 1000;

const int MAX_BLOCK_COLUMNS = 10;
const int MAX_BLOCK_ROWS = 10;

const int BLOCK_WIDTH = 43;
const int BLOCK_HEIGHT = 20;

const float BALL_START_POSITION_X = 300.0f;
const float BALL_START_POSITION_Y = 300.0f;

const float BALL_VELOCITY_X = 6.0f;
const float BALL_VELOCITY_Y = 5.0f;

const float BLOCK_INACTIVATE_X = -100.0f;
const float BLOCK_INACTIVATE_Y = 0.0f;

const float BALL_SIZE = 12.0f;

const float BALL_COLLISION_PADDING = 3.0f;
const float BALL_COLLISION_SIZE = 6.0f;

const float PADDLE_SPEED = 6.0f;

const int BALL_PADDLE_BOUNCE_MIN = 2;
const int BALL_PADDLE_BOUNCE_MAX = 5;


void handleInput(RenderWindow& window, Sprite& paddleSprite);
void checkBallCollisions(Ball& ball, Sprite blocks[], int blockCount, Sprite& paddleSprite);
void drawGame(RenderWindow& window, Sprite& backgroundSprite, Sprite& ballSprite,
    Sprite& paddleSprite, Sprite block[], int blockCount);

int arkanoid()
{
    srand(time(0));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid!");
    window.setFramerateLimit(FRAMERATE_LIMIT);

    Texture blockTexture,backgroundTexture,ballTexture,paddleTexture;
    blockTexture.loadFromFile("images/arkanoid/block01.png");
    backgroundTexture.loadFromFile("images/arkanoid/background.jpg");
    ballTexture.loadFromFile("images/arkanoid/ball.png");
    paddleTexture.loadFromFile("images/arkanoid/paddle.png");

    Sprite backgroundSprite(backgroundTexture), ballSprite(ballTexture), paddleSprite(paddleTexture);
    paddleSprite.setPosition(PADDLE_START_POSITION_X, PADDLE_START_POSITION_Y);

    Sprite block[TOTAL_BLOCKS];

    int blockCount=0;
    for (int column=1; column <= MAX_BLOCK_COLUMNS; column++)
    for (int row=1;row<= MAX_BLOCK_ROWS;row++)
    {
         block[blockCount].setTexture(blockTexture);
         block[blockCount].setPosition(column* BLOCK_WIDTH,row* BLOCK_HEIGHT);
         blockCount++;
    }

    Ball ball(BALL_START_POSITION_X, BALL_START_POSITION_Y, BALL_VELOCITY_X, BALL_VELOCITY_Y);

    while (window.isOpen())
    {
        handleInput(window, paddleSprite);

        ball.updatePosition();

        checkBallCollisions( ball, block, blockCount, paddleSprite);

        ballSprite.setPosition(ball.getPositionX(), ball.getPositionY());
   
        drawGame(window, backgroundSprite, ballSprite, paddleSprite, block, blockCount);
    }

  return 0;
}

void handleInput(RenderWindow& window, Sprite& paddleSprite)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) paddleSprite.move(PADDLE_SPEED, 0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) paddleSprite.move(-PADDLE_SPEED, 0);
}


void checkBallCollisions(Ball& ball, Sprite blocks[], int blockCount, Sprite& paddleSprite)
{
    for (int blockIndex = 0; blockIndex < blockCount; blockIndex++)
    {
		FloatRect blockBounds = blocks[blockIndex].getGlobalBounds();
        FloatRect ballBoundsX(ball.getPositionX() + BALL_COLLISION_PADDING, ball.getPositionY(), BALL_COLLISION_SIZE, BALL_COLLISION_SIZE);
		FloatRect ballBoundsY(ball.getPositionX(), ball.getPositionY() + BALL_COLLISION_PADDING, BALL_COLLISION_SIZE, BALL_COLLISION_SIZE);

        if (ballBoundsX.intersects(blockBounds))
        {
            blocks[blockIndex].setPosition(BLOCK_INACTIVATE_X, BLOCK_INACTIVATE_Y);
            ball.bounceHorizontally();
        }
        if (ballBoundsY.intersects(blockBounds))
        {
                blocks[blockIndex].setPosition(BLOCK_INACTIVATE_X, BLOCK_INACTIVATE_Y);
                ball.bounceVertically();
        }
    }

    if (ball.getPositionX()<0 || ball.getPositionX() >WINDOW_WIDTH)  ball.bounceHorizontally();
    if (ball.getPositionY() <0 || ball.getPositionY() >WINDOW_HEIGHT)   ball.bounceVertically();

    if (FloatRect(ball.getPositionX(), ball.getPositionY(), BALL_SIZE, BALL_SIZE).intersects(paddleSprite.getGlobalBounds()))
    {
        ball.applyPaddleBounce(rand() % BALL_PADDLE_BOUNCE_MAX + BALL_PADDLE_BOUNCE_MIN);
    }
}

void drawGame(RenderWindow& window, Sprite& backgroundSprite, Sprite& ballSprite, Sprite& paddleSprite, Sprite block[], int blockCount)
{

    window.clear();
    window.draw(backgroundSprite);
    window.draw(ballSprite);
    window.draw(paddleSprite);

    for (int blockIndex = 0; blockIndex < blockCount; blockIndex++)
        window.draw(block[blockIndex]);

    window.display();
}
