#ifndef _CONSTS_H
#define _CONSTS_H

// window
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
const float windowEnd = 800.0f;
const float windowStart = 0.0f;
// shapes
const int bottomShapePositonY = 565;
const int topShapePositonY = 35;
const sf::Color shapeColor = sf::Color(100, 100, 100);
const int shapeHeight = 3;
// all textures
const int sizeOfTexture = 32;
// start ship position
const sf::Vector2f StartVector = sf::Vector2f(385, 535);
// lives options
const int startLives = 3;
const int livesTopPosition = 570;
const int livesLeftPosition = 10;
const int livesWidthPosition = 30;
// aliens options
const int alienColumns = 11;
const int aliensLines = 5;
const float alienMoveToX = 100.0f;
const float alienMoveToY = 15.0f;
const float startLeftPositionAliens = 180.0f;
const float alienWidthAndBetween = sizeOfTexture + 5;
const float alienTimeToFire = 1.0f;
const int priceOfAlien = 10;
//const float alienTimeToMove = 0.1f;
// move limits
const float leftLimit = 10.0f;
const float rightLimit = 758.0f;
// ship speed
const float shipMoveX = 10.0f;
// buttons
const int buttonLeft = 71;
const int buttonRight = 72;
const int buttonUp = 73;
const int buttonDown = 74;
const int buttonSpace = 57;
const int buttonEnter = 58;
const int buttonEsc = 36;
const int buttonBackSpace = 59;
// bullets
const float bulletSpeed = 200.0f;
const float bulletSize = 8.0f;
// time between ship fire
const float timeBetweenShipFire = 0.32f;
// menu consts
const sf::Vector2f menuStartPositionVector = sf::Vector2f(180, 120);
const int sizeOfMenuLineX = 450;
const int sizeOfMenuLineY = 60;
const int sizeOfMenuBetweenLines = 20;
// pointLine
const int nowPointsLeft = 20;
const int recordPointsLeft = 450;
const int fontSizeOfPoints = 24;
// range numbers in char
const int minNumberChar = 48;
const int maxNumberChar = 57;
// records
const int recordLeftPos = 280;
const int recordTopPos = 120;
const int recordTopPosInner = 30;
const int recordLeftEmpty = 320;
const int recordTopEmpty = 280;
const int recordNumberLimit = 10;
// set new record
const int lengthOfName = 15;
const int recordInfoX = 250;
const int recordInfoY = 50;
const int recordTitleX = 120;
const int recordTitleY = 90;
const int recordNameX = 320;
const int recordNameY = 280;
const int emptyNameX = 200;
// speed boost
const float alienSpeedBoost = 50.0f;
const float shipFireBoostTime = 0.001f;
//start timer
const float startTimeSet = 3.0f;
const int timerPositionX = 390;
const int timerPositionY = 250;
const int timerFontSize = 75;
// bonus ship
const sf::Vector2f bonusShipStartVector = sf::Vector2f(-sizeOfTexture, topShapePositonY + shapeHeight);
const float bonusShipSpeed = 100.0f;
const int bonusShipCost = 120;
// other
const int borderOfUncode = 128;

#endif