#ifndef _BONUSSHIP_H
#define _BONUSSHIP_H
#include <SFML/Graphics.hpp>
#include "consts.h"

struct bonusShipStruct
{
    bool bonusShipWest;
    int bonusShipState;
    int bonusShipStartAlienNumber;
    sf::Vector2f bonusShipVector;
};

void bonusShipStartOptions(bonusShipStruct &bonusShip)
{
    bonusShip.bonusShipState = 0;
    bonusShip.bonusShipStartAlienNumber = getBonusShipAlienNumber();
    bonusShip.bonusShipVector = bonusShipStartVector;
    if (bonusShip.bonusShipWest)
        bonusShip.bonusShipVector.x = 800;
}

void showBonusShip(sf::RenderWindow &window, bonusShipStruct &bonusShip, sf::Texture &bonusShipTexture)
{
    sf::Sprite sprite;
    sprite.setTexture(bonusShipTexture);
    sprite.setPosition(bonusShip.bonusShipVector.x, bonusShip.bonusShipVector.y + sizeOfTexture / 2);
    sprite.setOrigin(sizeOfTexture / 2, sizeOfTexture / 2);
    if (bonusShip.bonusShipWest)
        sprite.setRotation(180);
    window.draw(sprite);
}

void bonusShipMove(bonusShipStruct &ShipVector, float &dt)
{
    if (!ShipVector.bonusShipWest)
        ShipVector.bonusShipVector.x += dt * bonusShipSpeed;
    else
        ShipVector.bonusShipVector.x -= dt * bonusShipSpeed;
}

void checkBonusShipDestroy(bullet *&shipBullets, int &shipBulletsCount, int &iPoints, bonusShipStruct &bonusShip)
{
    for (int k = 0; k < shipBulletsCount; k++)
    {
        if (abs((bonusShip.bonusShipVector.x + sizeOfTexture / 2) - (shipBullets[k].bulletVector.x + bulletSize / 2)) < sizeOfTexture / 2 + bulletSize / 2)
        {
            if (abs((bonusShip.bonusShipVector.y + sizeOfTexture / 2) - (shipBullets[k].bulletVector.y + bulletSize / 2)) < sizeOfTexture / 2 + bulletSize / 2)
            {
                iPoints += bonusShipCost;
                bonusShip.bonusShipState = 3;
                shipBullets[k].bulletState = false;
            }
        }
    }
}

#endif