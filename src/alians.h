#ifndef _ALIANS_H
#define _ALIANS_H
#include <SFML/Graphics.hpp>

struct aliansStruct
{
    bool arrayAliens[aliensLines][alienColumns];
    sf::Vector2f aliensVector;
    int lPos;
    int rPos;
    float alienFireTime;
};

struct aliansOptionsStruct
{
    float alienVectorX;
    int alienStateY;
    int aliensNumber;
    int alienStartNumber;
};

void aliensStartState(aliansStruct &aliansInfo, int &aliensNumber)
{
    for (int i = 0; i < aliensLines; i++)
    {
        for (int j = 0; j < alienColumns; j++)
        {
            aliansInfo.arrayAliens[i][j] = true;
            aliensNumber++;
        }
    }
    aliansInfo.aliensVector = sf::Vector2f(0, 0);
    aliansInfo.lPos = WINDOW_WIDTH;
    aliansInfo.rPos = 0;
    aliansInfo.alienFireTime = 0.0f;
}

void setStartAliansOptions(aliansStruct &aliansInfo, aliansOptionsStruct &aliansOptions, float &speedBoost)
{
    aliansOptions.alienVectorX = -(alienMoveToX + speedBoost);
    aliansOptions.alienStateY = 0;
    aliansOptions.aliensNumber = 0;
    aliensStartState(aliansInfo, aliansOptions.aliensNumber);
    aliansOptions.alienStartNumber = aliansOptions.aliensNumber;
}

#endif