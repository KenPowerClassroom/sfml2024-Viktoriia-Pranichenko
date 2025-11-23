#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int arkanoid()
{
    srand(time(0));

    RenderWindow window(VideoMode(520, 450), "Arkanoid!");
    window.setFramerateLimit(60);

    Texture blockTexture,backgroundTexture,ballTexture,paddleTexture;
    blockTexture.loadFromFile("images/arkanoid/block01.png");
    backgroundTexture.loadFromFile("images/arkanoid/background.jpg");
    ballTexture.loadFromFile("images/arkanoid/ball.png");
    paddleTexture.loadFromFile("images/arkanoid/paddle.png");

    Sprite backgroundSprite(backgroundTexture), ballSprite(ballTexture), paddleSprite(paddleTexture);
    paddleSprite.setPosition(300,440);

    Sprite block[1000];

    int blockCount=0;
    for (int column=1; column <=10; column++)
    for (int row=1;row<=10;row++)
      {
         block[blockCount].setTexture(blockTexture);
         block[blockCount].setPosition(column*43,row*20);
         blockCount++;
      }

    float ballVelocityX=6, ballVelocityY=5;
    float ballPositionX=300, ballPositionY=300;

    while (window.isOpen())
    {
       Event event;
       while (window.pollEvent(event))
       {
         if (event.type == Event::Closed)
             window.close();
       }

    ballPositionX+=ballVelocityX;
    for (int blockIndex =0; blockIndex <blockCount; blockIndex++)
        if ( FloatRect(ballPositionX+3,ballPositionY+3,6,6).intersects(block[blockIndex].getGlobalBounds()) )
             {block[blockIndex].setPosition(-100,0); ballVelocityX=-ballVelocityX;}

    ballPositionY+=ballVelocityY;
    for (int blockIndex=0; blockIndex <blockCount; blockIndex++)
        if ( FloatRect(ballPositionX+3,ballPositionY+3,6,6).intersects(block[blockIndex].getGlobalBounds()) )
             {block[blockIndex].setPosition(-100,0); ballVelocityY=-ballVelocityY;}

    if (ballPositionX<0 || ballPositionX>520)  ballVelocityX=-ballVelocityX;
    if (ballPositionY<0 || ballPositionY>450)  ballVelocityY=-ballVelocityY;

    if (Keyboard::isKeyPressed(Keyboard::Right)) paddleSprite.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) paddleSprite.move(-6,0);

    if ( FloatRect(ballPositionX,ballPositionY,12,12).intersects(paddleSprite.getGlobalBounds()) ) ballVelocityY=-(rand()%5+2);

    ballSprite.setPosition(ballPositionX,ballPositionY);

    window.clear();
    window.draw(backgroundSprite);
    window.draw(ballSprite);
    window.draw(paddleSprite);

    for (int blockIndex =0; blockIndex <blockCount; blockIndex++)
     window.draw(block[blockIndex]);

    window.display();
    }

  return 0;
}
