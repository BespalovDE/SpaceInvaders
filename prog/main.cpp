#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "consts.h"
#include "drawFunctions.h"
#include "bulletsFunctions.h"
#include "shipFunctions.h"
#include "menuFunctions.h"
#include "pointFunctions.h"
#include "bonusShip.h"

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void onKeyPress(const char event, int &buttonPress)
{
    /*if (event == sf::Keyboard::Escape)
    {
    }
    if ((int)event == 71) // left
    if ((int)event == 71) // right*/
    buttonPress = (int)event;
    //if (buttonPress != 0)
    //   std::cout << "button number: " << buttonPress << std::endl;
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, int &buttonPress)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        case sf::Event::KeyPressed:
            onKeyPress(event.key.code, buttonPress);
            break;
        default:
            break;
        }
    }
}

int game(sf::RenderWindow &window)
{
    sf::Texture texture;
    sf::Sprite sprite;
    //setStartPosition(sprite, texture);
    sf::Vector2f mousePosition;

    sf::RectangleShape shapeBottom;
    drawShape(shapeBottom);
    sf::RectangleShape shapeTop = shapeBottom;
    shapeTop.setPosition({0, topShapePositonY});

    int maxRecord = 0;
    int minRecord = 0;
    int recordsNumber = 0;
    GetRecords(maxRecord, minRecord, recordsNumber);

    int lives = startLives;
    float bottomPosition = 0.0f;
    int iPoints = 0;
    int level = 1;
    float speedBoost = 0.0f;
    float shipFireBoost = 0.0f;
    bool bonusShipWest = false;
    while (bottomPosition + sizeOfTexture < bottomShapePositonY && window.isOpen() && lives >= 0)
    {
        int bonusShipState = 0;
        int bonusShipStartAlienNumber = getBonusShipAlienNumber();
        sf::Vector2f bonusShipVector = bonusShipStartVector;
        if (bonusShipWest)
            bonusShipVector.x = 800;
        //std::cout << bonusShipStartAlienNumber << std::endl;
        float alienVectorX = -(alienMoveToX + speedBoost);
        int alienStateY = 0;
        bool arrayAliens[aliensLines][alienColumns];
        int aliensNumber = 0;
        for (int i = 0; i < aliensLines; i++)
            for (int j = 0; j < alienColumns; j++)
            {
                arrayAliens[i][j] = true;
                aliensNumber++;
            }
        int alienStartNumber = aliensNumber;
        sf::Vector2f aliensVector = sf::Vector2f(0, 0);
        int buttonPress = 0;
        int leftAliensPosition = WINDOW_WIDTH;
        int rightAliensPosition = 0;
        sf::Clock clock;
        float dt = 0.0f;
        int bulletCount = 0;
        int alienBulletCount = 0;
        bullet *shipBulletList = new bullet[bulletCount];
        bullet *alienBulletList = new bullet[alienBulletCount];
        float alienFireTime = 0.0f;
        bool shipFireState = true;
        float shipFireStateTimer = 0.0f;
        bottomPosition = 0.0f;
        if (lives < 3)
            lives++;
        setStartPosition(sprite, texture);
        float startTimer = startTimeSet;
        while (startTimer > 0)
        {
            window.clear();
            window.draw(sprite);
            drawLives(window, lives);
            drawLevel(window, level);
            drawInvanders(window, arrayAliens, aliensVector, leftAliensPosition, rightAliensPosition, alienFireTime,
                          alienBulletList, alienBulletCount, bottomPosition);
            window.draw(shapeTop);
            window.draw(shapeBottom);
            drawPoints(window, iPoints, maxRecord);
            drawTimer(window, startTimer);
            window.display();
            dt = clock.restart().asSeconds();
            startTimer -= dt;
        }
        while (window.isOpen() && lives >= 0 && aliensNumber > 0 && bottomPosition + sizeOfTexture < bottomShapePositonY) // раунд иры
        {
            if (leftAliensPosition <= leftLimit)
            {
                alienVectorX = (alienMoveToX + speedBoost);
                alienStateY = 1;
            }
            if (rightAliensPosition >= rightLimit)
            {
                alienVectorX = -(alienMoveToX + speedBoost);
                alienStateY = 1;
            }
            dt = clock.restart().asSeconds();
            aliensVector.x += alienVectorX * dt;
            if (alienStateY > 0)
            {
                aliensVector.y += alienMoveToY;
                alienStateY = 0;
            }
            alienFireTime += dt;
            pollEvents(window, mousePosition, buttonPress);
            shipMove(sprite, buttonPress);
            if (bonusShipState == 1)
                bonusShipMove(bonusShipVector, dt, bonusShipWest);
            BulletMove(shipBulletList, bulletCount, dt, false);
            BulletMove(alienBulletList, alienBulletCount, dt, true);
            if ((buttonPress == buttonSpace) && (shipFireState))
            {
                bullet newBullet = shipFire(sprite);
                funcInsertBullet(shipBulletList, newBullet, bulletCount);
                shipFireState = false;
                shipFireStateTimer = 0.0f;
            }
            if (!shipFireState)
            {
                shipFireStateTimer += dt;
                if (shipFireStateTimer >= timeBetweenShipFire - shipFireBoost)
                    shipFireState = true;
            }
            checkBulletsCross(shipBulletList, alienBulletList, bulletCount, alienBulletCount);
            checkAliensDestroy(arrayAliens, shipBulletList, bulletCount, aliensVector);
            checkShipDamage(sprite, lives, alienBulletList, alienBulletCount);
            checkShipsCross(sprite, lives, arrayAliens, aliensVector);
            if (bonusShipState == 1)
                checkBonusShipDestroy(shipBulletList, bulletCount, bonusShipVector, iPoints, bonusShipState);
            funcDeleteBullet(shipBulletList, bulletCount);
            funcDeleteBullet(alienBulletList, alienBulletCount);
            buttonPress = 0;
            window.clear();
            drawBullets(window, shipBulletList, bulletCount, 0);
            drawBullets(window, alienBulletList, alienBulletCount, 1);
            window.draw(sprite);
            drawLives(window, lives);
            drawLevel(window, level);
            drawInvanders(window, arrayAliens, aliensVector, leftAliensPosition, rightAliensPosition, alienFireTime,
                          alienBulletList, alienBulletCount, bottomPosition);
            if (bonusShipState == 1)
            {
                showBonusShip(window, bonusShipVector, bonusShipWest);
                if ((bonusShipVector.x > WINDOW_WIDTH && !bonusShipWest) || (bonusShipVector.x < -sizeOfTexture && bonusShipWest))
                    bonusShipState = 2;
            }
            window.draw(shapeTop);
            window.draw(shapeBottom);
            aliensNumber = 0;
            for (int i = 0; i < aliensLines; i++)
                for (int j = 0; j < alienColumns; j++)
                    if (arrayAliens[i][j])
                        aliensNumber++;
            if (aliensNumber <= bonusShipStartAlienNumber && bonusShipState == 0)
                bonusShipState = 1;
            updatePoints(alienStartNumber, aliensNumber, iPoints);
            drawPoints(window, iPoints, maxRecord);
            window.display();
        }
        level++;
        bonusShipWest = !bonusShipWest;
        speedBoost += alienSpeedBoost;
        shipFireBoost += shipFireBoostTime;
        if (lives < 0 || bottomPosition + sizeOfTexture >= bottomShapePositonY)
            if (iPoints > minRecord || recordsNumber < 10)
                SetRecord(window, iPoints);
    }
}

int main()
{
    sf::ContextSettings settings;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Space Invanders", sf::Style::Default, settings);
    int selectedState = 1;
    sf::Vector2f mousePosition;
    int buttonPress = 0;
    int gameState = 0;
    while (window.isOpen() && selectedState > 0)
    {
        pollEvents(window, mousePosition, buttonPress);
        if (buttonPress != 0)
            menuSelectStatus(window, buttonPress, selectedState, gameState);
        if (gameState == 1)
            game(window);
        else if (gameState == 2)
            showRecords(window);
        gameState = 0;
        buttonPress = 0;
        window.clear();
        drawMenu(window, selectedState);
        window.display();
    }
}