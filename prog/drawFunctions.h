#ifndef _DRAW_FUNCTIONS_H
#define _DRAW_FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <time.h>
#include "bulletsFunctions.h"

std::default_random_engine randomEngine(time(NULL));

void drawShape(sf::RectangleShape &shape)
{
    shape.setSize({WINDOW_WIDTH, shapeHeight});
    shape.setPosition({0, bottomShapePositonY});
    shape.setFillColor(shapeColor);
}

void getTextureFromFile(sf::Texture &texture, int textureState)
{
    switch (textureState)
    {
    case 0:
        texture.loadFromFile("pictures/Ship.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
        break;
    case 1:
        texture.loadFromFile("pictures/alien1.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
        break;
    case 2:
        texture.loadFromFile("pictures/alien2.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
        break;
    case 3:
        texture.loadFromFile("pictures/alien3.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
        break;
    case 4:
        texture.loadFromFile("pictures/alien4.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
        break;
    case 5:
        texture.loadFromFile("pictures/alien5.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
        break;
    case 6:
        texture.loadFromFile("pictures/shipBullet.png", sf::IntRect(0, 0, bulletSize, bulletSize));
        break;
    case 7:
        texture.loadFromFile("pictures/alienBullet.png", sf::IntRect(0, 0, bulletSize, bulletSize));
        break;
    case 8:
        texture.loadFromFile("pictures/play1.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
        break;
    case 9:
        texture.loadFromFile("pictures/play2.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
        break;
    case 10:
        texture.loadFromFile("pictures/records1.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
        break;
    case 11:
        texture.loadFromFile("pictures/records2.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
        break;
    case 12:
        texture.loadFromFile("pictures/exit1.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
        break;
    case 13:
        texture.loadFromFile("pictures/exit2.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
        break;
    case 14:
        texture.loadFromFile("pictures/bonusShip.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
        break;
    }
}

void drawLives(sf::RenderWindow &window, int lives)
{
    sf::Texture texture;
    getTextureFromFile(texture, 0);
    for (int i = 0; i < lives; i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(livesLeftPosition + i * livesWidthPosition, livesTopPosition));
        window.draw(sprite);
    }
}

void drawLevel(sf::RenderWindow &window, int level)
{
    sf::Font font;
    font.loadFromFile("CyrilicOld.ttf");
    sf::Text txt;
    txt.setFont(font);
    txt.setPosition(550, 568);
    txt.setString("Level: " + std::to_string(level));
    txt.setCharacterSize(fontSizeOfPoints);
    txt.setFillColor(sf::Color::Red);
    txt.setStyle(sf::Text::Bold);
    window.draw(txt);
}

int getRandomDirection(std::default_random_engine &randomEngine)
{
    std::uniform_int_distribution<int> randomNum(1, 100);
    return randomNum(randomEngine);
}

void drawInvanders(sf::RenderWindow &window, bool arrayAliens[aliensLines][alienColumns], sf::Vector2f aliensVector,
                   int &lPos, int &rPos, float &alienFireTime, bullet *&alienBulletsList, int &alienBuletCount, float &bottomPosition)
{
    sf::Texture aliensTexture;
    aliensTexture.setSmooth(true);
    lPos = windowEnd;
    rPos = windowStart;
    //std::default_random_engine randomEngine(time(NULL));
    for (int y = 0; y < aliensLines; y++)
    {
        getTextureFromFile(aliensTexture, y + 1);
        for (int x = 0; x < alienColumns; x++)
        {
            if (arrayAliens[y][x] == true)
            {
                sf::Sprite sprite;
                sprite.setTexture(aliensTexture);
                int scalY = alienWidthAndBetween + alienWidthAndBetween * y + aliensVector.y;
                sprite.setPosition(startLeftPositionAliens + x * alienWidthAndBetween + aliensVector.x, scalY);
                window.draw(sprite);
                if (scalY > bottomPosition)
                    bottomPosition = scalY;
                if (startLeftPositionAliens + x * alienWidthAndBetween + aliensVector.x < lPos)
                    lPos = startLeftPositionAliens + x * alienWidthAndBetween + aliensVector.x;
                if (startLeftPositionAliens + x * alienWidthAndBetween + aliensVector.x > rPos)
                    rPos = startLeftPositionAliens + x * alienWidthAndBetween + aliensVector.x;
                if (alienFireTime > alienTimeToFire) // per second
                {
                    int x = getRandomDirection(randomEngine);
                    if (x > 99)
                    {
                        bullet newBullet = alienFire(sprite);
                        funcInsertBullet(alienBulletsList, newBullet, alienBuletCount);
                    }
                }
            }
        }
    }
    if (alienFireTime > alienTimeToFire)
        alienFireTime = 0.0f;
}

int getBonusShipAlienNumber()
{
    //std::default_random_engine randomEngine(time(NULL));
    int x = 5 + getRandomDirection(randomEngine) / 2;
    return x;
}

void drawBullets(sf::RenderWindow &window, bullet *&bulletsList, int &size, int Membership)
{
    if (size > 0)
    {
        sf::Texture bulletTexture;
        bulletTexture.setSmooth(true);
        getTextureFromFile(bulletTexture, 6 + Membership);
        for (int i = 0; i < size; i++)
        {
            if (bulletsList[i].bulletState)
            {
                sf::Sprite sprite;
                sprite.setTexture(bulletTexture);
                sprite.setPosition(bulletsList[i].BulletVector.x, bulletsList[i].BulletVector.y);
                window.draw(sprite);
                //std::cout << "button number: " << bulletsList[i].BulletVector.x << std::endl;
            }
        }
    }
}

void drawMenuLine(sf::RenderWindow &window, int selectedMenuPicture, sf::Vector2f &positionVector)
{
    sf::Texture texture;
    sf::Sprite sprite;
    getTextureFromFile(texture, selectedMenuPicture);
    sprite.setPosition(positionVector);
    sprite.setTexture(texture);
    window.draw(sprite);
}

void drawMenu(sf::RenderWindow &window, int &selectedState)
{
    sf::Vector2f tempVector = menuStartPositionVector;
    for (int i = 0; i < 3; i++)
    {
        if (selectedState == i + 1)
            drawMenuLine(window, 9 + i * 2, tempVector);
        else
            drawMenuLine(window, 8 + i * 2, tempVector);
        tempVector.y = tempVector.y + sizeOfMenuLineY + sizeOfMenuBetweenLines;
    }
}

void drawTimer(sf::RenderWindow &window, float &startTimer)
{
    sf::Font font;
    font.loadFromFile("CyrilicOld.ttf");
    sf::Text txt;
    txt.setFont(font);
    txt.setPosition(timerPositionX, timerPositionY);
    txt.setString(std::to_string((int)ceil(startTimer)));
    txt.setCharacterSize(timerFontSize);
    txt.setFillColor(sf::Color::Red);
    txt.setStyle(sf::Text::Bold);
    window.draw(txt);
}

#endif