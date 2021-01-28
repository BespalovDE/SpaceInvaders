#ifndef _SHIP_FUNCTIONS_H
#define _SHIP_FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include "bulletsFunctions.h"

bullet shipFire(sf::Sprite &sprite)
{
    bullet newBullet;
    newBullet.bulletState = true;
    newBullet.bulletMembership = true;
    newBullet.bulletVector = sf::Vector2f(sprite.getPosition().x + 12, sprite.getPosition().y);
    return newBullet;
}

void shipMove(sf::Sprite &sprite, int buttonPress)
{
    if (buttonPress == buttonLeft)
    {
        if (sprite.getPosition().x > leftLimit)
            sprite.move(-shipMoveX, 0.0f);
    }
    if (buttonPress == buttonRight)
    {
        if (sprite.getPosition().x < rightLimit)
            sprite.move(shipMoveX, 0.0f);
    }
}

void setStartPosition(sf::Sprite &sprite, sf::Texture &texture)
{
    sprite.setPosition(StartVector);
    sprite.setTexture(texture);
}

void checkShipDamage(sf::Sprite &sprite, int &lives, bullet *&alienBullets, int &alienBulletsCount)
{
    for (int j = 0; j < alienBulletsCount; j++)
    {
        if (abs((alienBullets[j].bulletVector.x + bulletSize / 2) - (sprite.getPosition().x + sizeOfTexture / 2)) < sizeOfTexture / 2 + bulletSize / 2)
        {
            if (abs((alienBullets[j].bulletVector.y + bulletSize / 2) - (sprite.getPosition().y + sizeOfTexture / 2)) < sizeOfTexture / 2 + bulletSize / 2)
            {
                alienBullets[j].bulletState = false;
                lives--;
            }
        }
    }
}

void checkShipsCross(sf::Sprite &sprite, int &lives, aliansStruct &aliansInfo)
{
    for (int i = 0; i < alienColumns; i++)
    {
        for (int j = 0; j < aliensLines; j++)
        {
            if (aliansInfo.arrayAliens[j][i] == true)
            {
                if (abs((startLeftPositionAliens + i * alienWidthAndBetween + aliansInfo.aliensVector.x + sizeOfTexture / 2) - (sprite.getPosition().x + sizeOfTexture / 2)) < sizeOfTexture)
                {
                    if (abs((alienWidthAndBetween + j * alienWidthAndBetween + aliansInfo.aliensVector.y + sizeOfTexture / 2) - (sprite.getPosition().y + sizeOfTexture / 2)) < sizeOfTexture)
                    {
                        aliansInfo.arrayAliens[j][i] = false;
                        lives--;
                    }
                }
            }
        }
    }
}

#endif