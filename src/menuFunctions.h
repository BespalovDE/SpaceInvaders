#ifndef _MENU_FUNCTIONS_H
#define _MENU_FUNCTIONS_H
#include "consts.h"

void menuSelectStatus(sf::RenderWindow &window, int &buttonPress, int &selectedState, int &gameState)
{
    switch (buttonPress)
    {
    case buttonEnter:
        switch (selectedState)
        {
        case 1:
            gameState = 1;
            break;
        case 2:
            gameState = 2;
            break;
        case 3:
            selectedState = 0;
            break;
        }
        break;
    case buttonUp:
        switch (selectedState)
        {
        case 1:
            selectedState = 3;
            break;
        case 2:
            selectedState = 1;
            break;
        case 3:
            selectedState = 2;
            break;
        }
        break;
    case buttonDown:
        switch (selectedState)
        {
        case 1:
            selectedState = 2;
            break;
        case 2:
            selectedState = 3;
            break;
        case 3:
            selectedState = 1;
            break;
        }
        break;
    case buttonEsc:
        selectedState = 0;
        break;
    default:
        break;
    }
}
#endif