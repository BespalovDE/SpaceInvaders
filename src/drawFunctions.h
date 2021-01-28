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

void getAllTextureFromFile(sf::Texture *&allTextures)
{
    allTextures[0].loadFromFile("assets/pictures/Ship.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
    allTextures[1].loadFromFile("assets/pictures/alien1.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
    allTextures[2].loadFromFile("assets/pictures/alien2.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
    allTextures[3].loadFromFile("assets/pictures/alien3.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
    allTextures[4].loadFromFile("assets/pictures/alien4.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
    allTextures[5].loadFromFile("assets/pictures/alien5.png", sf::IntRect(0, 0, sizeOfTexture, sizeOfTexture));
    allTextures[6].loadFromFile("assets/pictures/shipBullet.png", sf::IntRect(0, 0, bulletSize, bulletSize));
    allTextures[7].loadFromFile("assets/pictures/alienBullet.png", sf::IntRect(0, 0, bulletSize, bulletSize));
    allTextures[8].loadFromFile("assets/pictures/play1.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
    allTextures[9].loadFromFile("assets/pictures/play2.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
    allTextures[10].loadFromFile("assets/pictures/records1.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
    allTextures[11].loadFromFile("assets/pictures/records2.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
    allTextures[12].loadFromFile("assets/pictures/exit1.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
    allTextures[13].loadFromFile("assets/pictures/exit2.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
    allTextures[14].loadFromFile("assets/pictures/bonusShip.png", sf::IntRect(0, 0, sizeOfMenuLineX, sizeOfMenuLineY));
    for (int i = 0; i < 15; i++)
        allTextures[i].setSmooth(true);
}

void drawLives(sf::RenderWindow &window, int lives, sf::Texture &texture)
{
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
    font.loadFromFile("assets/fonts/CyrilicOld.ttf");
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

void drawInvanders(sf::RenderWindow &window, aliansStruct &alienInfo, bullet *&alienBulletsList, int &alienBuletCount, float &bottomPosition, sf::Texture *&allTexture)
{
    alienInfo.lPos = windowEnd;
    alienInfo.rPos = windowStart;
    //std::default_random_engine randomEngine(time(NULL));
    for (int y = 0; y < aliensLines; y++)
    {
        for (int x = 0; x < alienColumns; x++)
        {
            if (alienInfo.arrayAliens[y][x] == true)
            {
                sf::Sprite sprite;
                sprite.setTexture(allTexture[y + 1]);
                int scalY = alienWidthAndBetween + alienWidthAndBetween * y + alienInfo.aliensVector.y;
                sprite.setPosition(startLeftPositionAliens + x * alienWidthAndBetween + alienInfo.aliensVector.x, scalY);
                window.draw(sprite);
                if (scalY > bottomPosition)
                    bottomPosition = scalY;
                if (startLeftPositionAliens + x * alienWidthAndBetween + alienInfo.aliensVector.x < alienInfo.lPos)
                    alienInfo.lPos = startLeftPositionAliens + x * alienWidthAndBetween + alienInfo.aliensVector.x;
                if (startLeftPositionAliens + x * alienWidthAndBetween + alienInfo.aliensVector.x > alienInfo.rPos)
                    alienInfo.rPos = startLeftPositionAliens + x * alienWidthAndBetween + alienInfo.aliensVector.x;
                if (alienInfo.alienFireTime > alienTimeToFire) // per second
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
    if (alienInfo.alienFireTime > alienTimeToFire)
        alienInfo.alienFireTime = 0.0f;
}

int getBonusShipAlienNumber()
{
    //std::default_random_engine randomEngine(time(NULL));
    int x = 5 + getRandomDirection(randomEngine) / 2;
    return x;
}

void drawBullets(sf::RenderWindow &window, bullet *&bulletsList, int &size, sf::Texture &bulletTexture)
{
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            if (bulletsList[i].bulletState)
            {
                sf::Sprite sprite;
                sprite.setTexture(bulletTexture);
                sprite.setPosition(bulletsList[i].bulletVector.x, bulletsList[i].bulletVector.y);
                window.draw(sprite);
            }
        }
    }
}

void drawMenuLine(sf::RenderWindow &window, sf::Texture &texture, sf::Vector2f &positionVector)
{
    sf::Sprite sprite;
    sprite.setPosition(positionVector);
    sprite.setTexture(texture);
    window.draw(sprite);
}

void drawMenu(sf::RenderWindow &window, int &selectedState, sf::Texture *&allTexture)
{
    sf::Vector2f tempVector = menuStartPositionVector;
    for (int i = 0; i < 3; i++)
    {
        if (selectedState == i + 1)
            drawMenuLine(window, allTexture[9 + i * 2], tempVector);
        else
            drawMenuLine(window, allTexture[8 + i * 2], tempVector);
        tempVector.y = tempVector.y + sizeOfMenuLineY + sizeOfMenuBetweenLines;
    }
}

void drawTimer(sf::RenderWindow &window, float &startTimer)
{
    sf::Font font;
    font.loadFromFile("assets/fonts/CyrilicOld.ttf");
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