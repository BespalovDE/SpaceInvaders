#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "consts.h"
#include "alians.h"
#include "drawFunctions.h"
#include "bulletsFunctions.h"
#include "shipFunctions.h"
#include "menuFunctions.h"
#include "pointFunctions.h"
#include "bonusShip.h"

struct gameOptionsStruct
{
    int lives;
    float bottomPosition;
    int level;
    float speedBoost;
    float shipFireBoost;
    int buttonPress;
    float dt;
    int bulletCount;
    int alienBulletCount;
    bool shipFireState;
    float shipFireStateTimer;
};

struct shapeAndSpriteStruct
{
    sf::Sprite sprite;
    sf::RectangleShape shapeBottom;
    sf::RectangleShape shapeTop;
};

void setShapeAndSprite(shapeAndSpriteStruct &shapeAndSprite)
{
    drawShape(shapeAndSprite.shapeBottom);
    shapeAndSprite.shapeTop = shapeAndSprite.shapeBottom;
    shapeAndSprite.shapeTop.setPosition({0, topShapePositonY});
}

void setStartGameOptions(gameOptionsStruct &gameOptions, bool stateStartGame)
{
    if (stateStartGame) // start game
    {
        gameOptions.lives = startLives;
        gameOptions.bottomPosition = 0.0f;
        gameOptions.level = 1;
        gameOptions.speedBoost = 0.0f;
        gameOptions.shipFireBoost = 0.0f;
    }
    else // start level
    {
        gameOptions.buttonPress = 0;
        gameOptions.dt = 0.0f;
        gameOptions.bulletCount = 0;
        gameOptions.alienBulletCount = 0;
        gameOptions.shipFireState = true;
        gameOptions.shipFireStateTimer = 0.0f;
    }
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

void pollEvents(sf::RenderWindow &window, int &buttonPress)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            onKeyPress(event.key.code, buttonPress);
            break;
        default:
            break;
        }
    }
}

void startGameTimerShow(sf::RenderWindow &window, gameOptionsStruct &gameOptions, shapeAndSpriteStruct &shapeAndSprite, sf::Texture *&allTexture, aliansStruct &aliensInfo, bullet *&alienBulletList, recordsStruct &records, sf::Clock &clock)
{
    float startTimer = startTimeSet;
    while (startTimer > 0)
    {
        window.clear();
        window.draw(shapeAndSprite.sprite);
        drawLives(window, gameOptions.lives, allTexture[0]);
        drawLevel(window, gameOptions.level);
        drawInvanders(window, aliensInfo, alienBulletList, gameOptions.alienBulletCount, gameOptions.bottomPosition, allTexture);
        window.draw(shapeAndSprite.shapeTop);
        window.draw(shapeAndSprite.shapeBottom);
        drawPoints(window, records.iPoints, records.maxRecord);
        drawTimer(window, startTimer);
        window.display();
        gameOptions.dt = clock.restart().asSeconds();
        startTimer -= gameOptions.dt;
    }
}

void setSideAlienMoveX(gameOptionsStruct &gameOptions, aliansStruct &aliansInfo, aliansOptionsStruct &aliansOptions)
{
    if (aliansInfo.lPos <= leftLimit)
    {
        aliansOptions.alienVectorX = (alienMoveToX + gameOptions.speedBoost);
        aliansOptions.alienStateY = 1;
    }
    if (aliansInfo.rPos >= rightLimit)
    {
        aliansOptions.alienVectorX = -(alienMoveToX + gameOptions.speedBoost);
        aliansOptions.alienStateY = 1;
    }
}

void changeAlianOptions(gameOptionsStruct &gameOptions, aliansStruct &aliansInfo, aliansOptionsStruct &aliansOptions)
{
    aliansInfo.aliensVector.x += aliansOptions.alienVectorX * gameOptions.dt;
    if (aliansOptions.alienStateY > 0)
    {
        aliansInfo.aliensVector.y += alienMoveToY;
        aliansOptions.alienStateY = 0;
    }
    aliansInfo.alienFireTime += gameOptions.dt;
}

void moveObjectsFunctions(sf::RenderWindow &window, gameOptionsStruct &gameOptions, aliansStruct &aliansInfo, aliansOptionsStruct &aliansOptions, shapeAndSpriteStruct &shapeAndSprite, bonusShipStruct &bonusShip, bullet *&shipBulletList, bullet *&alienBulletList, sf::Clock &clock)
{
    setSideAlienMoveX(gameOptions, aliansInfo, aliansOptions);
    gameOptions.dt = clock.restart().asSeconds();
    changeAlianOptions(gameOptions, aliansInfo, aliansOptions);
    pollEvents(window, gameOptions.buttonPress);
    shipMove(shapeAndSprite.sprite, gameOptions.buttonPress);
    if (bonusShip.bonusShipState == 1)
        bonusShipMove(bonusShip, gameOptions.dt);
    BulletMove(shipBulletList, gameOptions.bulletCount, gameOptions.dt, false);
    BulletMove(alienBulletList, gameOptions.alienBulletCount, gameOptions.dt, true);
}

void checkFunctions(gameOptionsStruct &gameOptions, aliansStruct &aliansInfo, bullet *&shipBulletList, bullet *&alienBulletList, shapeAndSpriteStruct &shapeAndSprite, bonusShipStruct &bonusShip, recordsStruct &records)
{
    checkBulletsCross(shipBulletList, alienBulletList, gameOptions.bulletCount, gameOptions.alienBulletCount);
    checkAliensDestroy(aliansInfo, shipBulletList, gameOptions.bulletCount);
    checkShipDamage(shapeAndSprite.sprite, gameOptions.lives, alienBulletList, gameOptions.alienBulletCount);
    checkShipsCross(shapeAndSprite.sprite, gameOptions.lives, aliansInfo);
    if (bonusShip.bonusShipState == 1)
        checkBonusShipDestroy(shipBulletList, gameOptions.bulletCount, records.iPoints, bonusShip);
}

void checkShipFire(gameOptionsStruct &gameOptions, shapeAndSpriteStruct &shapeAndSprite, bullet *&shipBulletList)
{
    if ((gameOptions.buttonPress == buttonSpace) && (gameOptions.shipFireState))
    {
        bullet newBullet = shipFire(shapeAndSprite.sprite);
        funcInsertBullet(shipBulletList, newBullet, gameOptions.bulletCount);
        gameOptions.shipFireState = false;
        gameOptions.shipFireStateTimer = 0.0f;
    }
    if (!gameOptions.shipFireState)
    {
        gameOptions.shipFireStateTimer += gameOptions.dt;
        if (gameOptions.shipFireStateTimer >= timeBetweenShipFire - gameOptions.shipFireBoost)
            gameOptions.shipFireState = true;
    }
}

void drawGameFunctions(sf::RenderWindow &window, gameOptionsStruct &gameOptions, bullet *&shipBulletList, bullet *&alienBulletList, sf::Texture *&allTexture, shapeAndSpriteStruct &shapeAndSprite, aliansStruct &aliansInfo, bonusShipStruct &bonusShip)
{
    window.clear();
    drawBullets(window, shipBulletList, gameOptions.bulletCount, allTexture[6]);
    drawBullets(window, alienBulletList, gameOptions.alienBulletCount, allTexture[7]);
    window.draw(shapeAndSprite.sprite);
    drawLives(window, gameOptions.lives, allTexture[0]);
    drawLevel(window, gameOptions.level);
    drawInvanders(window, aliansInfo, alienBulletList, gameOptions.alienBulletCount, gameOptions.bottomPosition, allTexture);
    if (bonusShip.bonusShipState == 1)
    {
        showBonusShip(window, bonusShip, allTexture[14]);
        if ((bonusShip.bonusShipVector.x > WINDOW_WIDTH && !bonusShip.bonusShipWest) || (bonusShip.bonusShipVector.x < -sizeOfTexture && bonusShip.bonusShipWest))
            bonusShip.bonusShipState = 2;
    }
    window.draw(shapeAndSprite.shapeTop);
    window.draw(shapeAndSprite.shapeBottom);
}

void playGameLevel(sf::RenderWindow &window, sf::Texture *&allTexture, gameOptionsStruct &gameOptions, shapeAndSpriteStruct &shapeAndSprite, aliansStruct &aliansInfo, aliansOptionsStruct &aliansOptions, bonusShipStruct &bonusShip, recordsStruct &records, bullet *&shipBulletList, bullet *&alienBulletList, sf::Clock &clock)
{
    while (window.isOpen() && gameOptions.lives >= 0 && aliansOptions.aliensNumber > 0 && gameOptions.bottomPosition + sizeOfTexture < bottomShapePositonY) // раунд иры
    {
        moveObjectsFunctions(window, gameOptions, aliansInfo, aliansOptions, shapeAndSprite, bonusShip, shipBulletList, alienBulletList, clock);
        checkShipFire(gameOptions, shapeAndSprite, shipBulletList);
        checkFunctions(gameOptions, aliansInfo, shipBulletList, alienBulletList, shapeAndSprite, bonusShip, records);
        funcDeleteBullet(shipBulletList, gameOptions.bulletCount);
        funcDeleteBullet(alienBulletList, gameOptions.alienBulletCount);
        gameOptions.buttonPress = 0;
        drawGameFunctions(window, gameOptions, shipBulletList, alienBulletList, allTexture, shapeAndSprite, aliansInfo, bonusShip);
        aliansOptions.aliensNumber = 0;
        for (int i = 0; i < aliensLines; i++)
        {
            for (int j = 0; j < alienColumns; j++)
            {
                if (aliansInfo.arrayAliens[i][j])
                    aliansOptions.aliensNumber++;
            }
        }
        if (aliansOptions.aliensNumber <= bonusShip.bonusShipStartAlienNumber && bonusShip.bonusShipState == 0)
            bonusShip.bonusShipState = 1;
        updatePoints(aliansOptions, records.iPoints);
        drawPoints(window, records.iPoints, records.maxRecord);
        window.display();
    }
}

int game(sf::RenderWindow &window, sf::Texture *&allTexture)
{
    shapeAndSpriteStruct shapeAndSprite;
    setShapeAndSprite(shapeAndSprite);
    recordsStruct records;
    GetRecords(records);
    gameOptionsStruct gameOptions;
    setStartGameOptions(gameOptions, true);
    bonusShipStruct bonusShip;
    bonusShip.bonusShipWest = true;
    aliansStruct aliansInfo;
    while (gameOptions.bottomPosition + sizeOfTexture < bottomShapePositonY && window.isOpen() && gameOptions.lives >= 0)
    {
        sf::Clock clock;
        bonusShipStartOptions(bonusShip);
        aliansOptionsStruct aliansOptions;
        setStartAliansOptions(aliansInfo, aliansOptions, gameOptions.speedBoost);
        setStartGameOptions(gameOptions, false);
        bullet *shipBulletList = new bullet[gameOptions.bulletCount];
        bullet *alienBulletList = new bullet[gameOptions.alienBulletCount];
        gameOptions.bottomPosition = 0.0f;
        if (gameOptions.lives < 3)
            gameOptions.lives++;
        setStartPosition(shapeAndSprite.sprite, allTexture[0]);
        startGameTimerShow(window, gameOptions, shapeAndSprite, allTexture, aliansInfo, alienBulletList, records, clock);
        playGameLevel(window, allTexture, gameOptions, shapeAndSprite, aliansInfo, aliansOptions, bonusShip, records, shipBulletList, alienBulletList, clock);
        gameOptions.level++;
        bonusShip.bonusShipWest = !bonusShip.bonusShipWest;
        gameOptions.speedBoost += alienSpeedBoost;
        gameOptions.shipFireBoost += shipFireBoostTime;
        if (gameOptions.lives < 0 || gameOptions.bottomPosition + sizeOfTexture >= bottomShapePositonY)
        {
            if (records.iPoints > records.minRecord || records.recordsNumber < 10)
                SetRecord(window, records.iPoints);
        }
    }
}

int main()
{
    sf::Texture *allTexture = new sf::Texture[15];
    getAllTextureFromFile(allTexture);
    sf::ContextSettings settings;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Space Invanders", sf::Style::Default, settings);
    int selectedState = 1;
    int buttonPress = 0;
    int gameState = 0;
    while (window.isOpen() && selectedState > 0)
    {
        pollEvents(window, buttonPress);
        if (buttonPress != 0)
            menuSelectStatus(window, buttonPress, selectedState, gameState);
        if (gameState == 1)
            game(window, allTexture);
        else if (gameState == 2)
            showRecords(window);
        gameState = 0;
        buttonPress = 0;
        window.clear();
        drawMenu(window, selectedState, allTexture);
        window.display();
    }
}