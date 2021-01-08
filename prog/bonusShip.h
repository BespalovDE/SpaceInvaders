#ifndef _BONUSSHIP_H
#define _BONUSSHIP_H
#include <SFML/Graphics.hpp>
#include "consts.h"

void showBonusShip(sf::RenderWindow &window, sf::Vector2f bonusShipVector, bool bonusShipWest)
{
    sf::Texture bonusShipTexture;
    bonusShipTexture.setSmooth(true);
    getTextureFromFile(bonusShipTexture, 14);
    sf::Sprite sprite;
    sprite.setTexture(bonusShipTexture);
    sprite.setPosition(bonusShipVector.x, bonusShipVector.y + sizeOfTexture / 2);
    sprite.setOrigin(sizeOfTexture / 2, sizeOfTexture / 2);
    if (bonusShipWest)
        sprite.setRotation(180);
    window.draw(sprite);
}

void bonusShipMove(sf::Vector2f &bonusShipVector, float &dt, bool bonusShipWest)
{
    if (!bonusShipWest)
        bonusShipVector.x += dt * bonusShipSpeed;
    else
        bonusShipVector.x -= dt * bonusShipSpeed;
}

void checkBonusShipDestroy(bullet *&shipBullets, int &shipBulletsCount, sf::Vector2f &bonusShipVector, int &iPoints, int &bonusShipState)
{
    for (int k = 0; k < shipBulletsCount; k++)
        if (abs((bonusShipVector.x + sizeOfTexture / 2) - (shipBullets[k].BulletVector.x + bulletSize / 2)) < sizeOfTexture / 2 + bulletSize / 2)
            if (abs((bonusShipVector.y + sizeOfTexture / 2) - (shipBullets[k].BulletVector.y + bulletSize / 2)) < sizeOfTexture / 2 + bulletSize / 2)
            {
                iPoints += bonusShipCost;
                bonusShipState = 3;
                shipBullets[k].bulletState = false;
            }
}

#endif