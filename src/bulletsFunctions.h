#ifndef _BULLET_FUNCTIONS_H
#define _BULLET_FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include "alians.h"

struct bullet
{
    bool bulletState;          //bullet exsts
    bool bulletMembership;     // ship or alien bullet
    sf::Vector2f bulletVector; // bullet position
};

void funcInsertBullet(bullet *&bulletsList, bullet val, int &size)
{ //Вставка элемента
    bullet *temp = new bullet[size + 1];
    if (size > 0)
        memmove((void *)temp, (const void *)bulletsList, sizeof(bullet) * size);
    temp[size] = val;
    size++;
    if (temp != nullptr)
    {
        bulletsList = new bullet[size];
        memmove((void *)&bulletsList[0], (const void *)temp, sizeof(bullet) * size);
    }
    delete[] temp;
    temp = nullptr;
}

void funcDeleteBullet(bullet *&bulletsList, int &size)
{ //Вставка элемента
    int newCount = 0;
    for (int i = 0; i < size; i++)
    {
        if (bulletsList[i].bulletState)
            newCount++;
    }
    if (size == newCount)
        return;
    if (newCount == 0)
    {
        bulletsList = new bullet[0];
        size = 0;
    }
    else
    {
        bullet *temp = new bullet[newCount];
        newCount = 0;
        for (int i = 0; i < size; i++)
        {
            if (bulletsList[i].bulletState)
            {
                temp[newCount] = bulletsList[i];
                newCount++;
            }
        }
        size = newCount;
        bulletsList = new bullet[size];
        memmove((void *)&bulletsList[0], (const void *)temp, sizeof(bullet) * size);
        delete[] temp;
        temp = nullptr;
    }
}

void BulletMove(bullet *&bulletsList, int &size, float &dt, bool alienState)
{
    if (size == 0)
        return;
    for (int i = 0; i < size; i++)
    {
        if (alienState)
        {
            bulletsList[i].bulletVector.y += bulletSpeed * dt;
            if (bulletsList[i].bulletVector.y >= bottomShapePositonY)
                bulletsList[i].bulletState = false;
        }
        else
        {
            bulletsList[i].bulletVector.y -= bulletSpeed * dt;
            if (bulletsList[i].bulletVector.y <= -bulletSize)
                bulletsList[i].bulletState = false;
        }
    }
}

bullet alienFire(sf::Sprite &sprite)
{
    bullet newBullet;
    newBullet.bulletState = true;
    newBullet.bulletMembership = false;
    newBullet.bulletVector = sf::Vector2f(sprite.getPosition().x + 12, sprite.getPosition().y + 32);
    return newBullet;
}

void checkBulletsCross(bullet *&shipBullets, bullet *&alienBullets, int &shipBulletsCount, int &alienBulletsCount)
{
    for (int i = 0; i < shipBulletsCount; i++)
    {
        for (int j = 0; j < alienBulletsCount; j++)
        {
            if ((abs(shipBullets[i].bulletVector.x - alienBullets[j].bulletVector.x) <= bulletSize) &&
                (abs(shipBullets[i].bulletVector.y - alienBullets[j].bulletVector.y) <= bulletSize))
            {
                shipBullets[i].bulletState = false;
                alienBullets[j].bulletState = false;
            }
        }
    }
}

void checkAliensDestroy(aliansStruct &aliansInfo, bullet *&shipBullets, int &shipBulletsCount)
{
    for (int i = 0; i < alienColumns; i++)
    {
        for (int j = 0; j < aliensLines; j++)
        {
            if (aliansInfo.arrayAliens[j][i] == true)
            {
                for (int k = 0; k < shipBulletsCount; k++)
                {
                    if (abs((startLeftPositionAliens + i * alienWidthAndBetween + aliansInfo.aliensVector.x + sizeOfTexture / 2) - (shipBullets[k].bulletVector.x + bulletSize / 2)) < sizeOfTexture / 2 + bulletSize / 2)
                    {
                        if (abs((alienWidthAndBetween + j * alienWidthAndBetween + aliansInfo.aliensVector.y + sizeOfTexture / 2) - (shipBullets[k].bulletVector.y + bulletSize / 2)) < sizeOfTexture / 2 + bulletSize / 2)
                        {
                            aliansInfo.arrayAliens[j][i] = false;
                            shipBullets[k].bulletState = false;
                        }
                    }
                }
            }
        }
    }
}

#endif