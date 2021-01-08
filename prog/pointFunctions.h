#ifndef _POINT_FUNCTIONS_H
#define _POINT_FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "consts.h"
#include <list>

void drawPlayerPonts(sf::RenderWindow &window, std::string sPoints, int xPos)
{
    sf::Font font;
    font.loadFromFile("CyrilicOld.ttf");
    sf::Text txt;
    txt.setFont(font);
    txt.setPosition(xPos, 2);
    txt.setString(sPoints);
    txt.setCharacterSize(fontSizeOfPoints);
    txt.setFillColor(sf::Color::Red);
    txt.setStyle(sf::Text::Bold);
    window.draw(txt);
}

void updatePoints(int &alienStartNumber, int &aliensNumber, int &iPoints)
{
    iPoints += priceOfAlien * (alienStartNumber - aliensNumber);
    alienStartNumber = aliensNumber;
}

void pollEventsPoints(sf::RenderWindow &window, int &buttonPress, char &newChar)
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
            buttonPress = int(event.key.code);
            break;
        case sf::Event::TextEntered:
        {
            if (event.text.unicode < borderOfUncode)
            {
                newChar = static_cast<char>(event.text.unicode);
            }
            else
                newChar = 0;
            break;
        }
        default:
            break;
        }
    }
}

void showRecords(sf::RenderWindow &window)
{
    window.clear();
    sf::Font font;
    font.loadFromFile("CyrilicOld.ttf");
    sf::Text txt;
    txt.setFont(font);
    txt.setPosition(recordLeftPos, 10);
    txt.setString("Table of records:");
    txt.setCharacterSize(fontSizeOfPoints);
    txt.setFillColor(sf::Color::Red);
    txt.setStyle(sf::Text::Bold);
    window.draw(txt);
    std::string line;
    std::ifstream in("records.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        if (getline(in, line))
        {
            int i = 1;
            txt.setString(line);
            txt.setPosition(recordLeftPos, recordTopPos + recordTopPosInner * (i + 1));
            window.draw(txt);
            while (getline(in, line))
            {
                i++;
                txt.setString(line);
                txt.setPosition(recordLeftPos, recordTopPos + recordTopPosInner * (i + 1));
                window.draw(txt);
            }
        }
        else
        {
            txt.setPosition(recordLeftEmpty, recordTopEmpty);
            txt.setString("No records!");
            window.draw(txt);
        }
    }
    in.close(); // закрываем файл
    int iButton = 0;
    window.display();
    char newChar = 0;
    while (window.isOpen() && iButton == 0)
    {
        pollEventsPoints(window, iButton, newChar);
    }
}

int getScore(std::string &line)
{
    std::string::size_type sz;
    int iScore = 0;
    std::string stringLine = "";
    int i = line.length() - 1;
    while (line[i] >= minNumberChar && line[i] <= maxNumberChar)
    {
        stringLine = line[i] + stringLine;
        i--;
    }
    if (stringLine.length() > 0)
        iScore = std::stoi(stringLine, &sz);
    return iScore;
}

void GetRecords(int &recordScore, int &minRecordScore, int &recordsNumber)
{
    int iRecord = 0;
    int iTempRecord = 0;
    int iMinTempRecord = 0;
    std::string line;
    std::ifstream in("records.txt");
    if (in.is_open())
    {
        if (getline(in, line))
        {
            recordsNumber++;
            iTempRecord = getScore(line);
            iMinTempRecord = iTempRecord;
            if (iTempRecord > iRecord)
                iRecord = iTempRecord;
            while (getline(in, line))
            {
                recordsNumber++;
                iTempRecord = getScore(line);
                if (iTempRecord > iRecord)
                    iRecord = iTempRecord;
                if (iMinTempRecord > iTempRecord)
                    iMinTempRecord = iTempRecord;
            }
        }
    }
    in.close(); // закрываем файл
    recordScore = iRecord;
    minRecordScore = iMinTempRecord;
}

void SetNewRecord(int &iPoints, std::string &userName)
{
    int insertState = 0;
    int recordsNumber = 0;
    int iTempRecord = 0;
    std::list<std::string> listOfRecords;
    std::string line;
    std::ifstream in("records.txt");
    if (in.is_open())
    {
        if (getline(in, line))
        {
            recordsNumber++;
            iTempRecord = getScore(line);
            if (iPoints > iTempRecord && insertState == 0)
            {
                listOfRecords.push_back(userName + " " + std::to_string(iPoints));
                recordsNumber++;
                insertState = 1;
            }
            listOfRecords.push_back(line);
            while (getline(in, line))
            {
                recordsNumber++;
                iTempRecord = getScore(line);
                if (iPoints > iTempRecord && insertState == 0)
                {
                    listOfRecords.push_back(userName + " " + std::to_string(iPoints));
                    recordsNumber++;
                    insertState = 1;
                }
                if (recordsNumber < recordNumberLimit)
                    listOfRecords.push_back(line);
            }
            if (insertState == 0)
                listOfRecords.push_back(userName + " " + std::to_string(iPoints));
        }
    }
    in.close();              // закрываем файл
    std::ofstream out;       // поток для записи
    out.open("records.txt"); // окрываем файл для записи
    if (out.is_open())
    {
        while (listOfRecords.size() > 0)
        {
            out << listOfRecords.front() << std::endl;
            listOfRecords.pop_front();
        }
    }
    out.close();
}

void SetRecord(sf::RenderWindow &window, int &iPoints)
{
    window.clear();
    std::string yourScore = "Your score is " + std::to_string(iPoints);
    std::string captionString = "Write your name and push 'Enter' or push 'Esc'";
    std::string nameString = "";
    sf::Font font;
    font.loadFromFile("CyrilicOld.ttf");
    sf::Text txt;
    txt.setFont(font);
    txt.setPosition(recordInfoX, recordInfoY);
    txt.setString(yourScore);
    txt.setCharacterSize(fontSizeOfPoints);
    txt.setFillColor(sf::Color::Red);
    txt.setStyle(sf::Text::Bold);
    window.draw(txt);
    txt.setPosition(recordTitleX, recordTitleY);
    txt.setString(captionString);
    window.draw(txt);
    window.display();
    int iButton = 0;
    char newChar = 0;
    int stateChange = 0;
    int iState = 0;
    while (window.isOpen() && iButton != buttonEnter && iButton != buttonEsc)
    {
        iButton = 0;
        newChar = 0;
        pollEventsPoints(window, iButton, newChar);
        if (iState == 1)
        {
            if (iButton != 0)
            {
                iState = 0;
                stateChange = 1;
            }
            iButton = 0;
            newChar = 0;
            continue;
        }
        if (newChar > 0 && newChar < 128 && iButton != buttonBackSpace && iButton != buttonEnter && iButton != buttonEsc)
        {
            if (nameString.length() <= lengthOfName)
            {
                nameString = nameString + newChar;
                stateChange = 1;
            }
        }
        if (iButton == buttonBackSpace)
            if (nameString.length() > 0)
            {
                nameString = nameString.substr(0, nameString.length() - 1);
                stateChange = 1;
            }
        if (stateChange == 1)
        {
            stateChange = 0;
            window.clear();
            txt.setPosition(recordInfoX, recordInfoY);
            txt.setString(yourScore);
            window.draw(txt);
            txt.setPosition(recordTitleX, recordTitleY);
            txt.setString(captionString);
            window.draw(txt);
            txt.setPosition(recordNameX, recordNameY);
            txt.setString(nameString);
            window.draw(txt);
            window.display();
        }
        if (iButton == buttonEnter && nameString.length() < 1)
        {
            iState = 1;
            iButton = 0;
            window.clear();
            txt.setPosition(emptyNameX, recordNameY);
            txt.setString("Empty name is not acceptable!");
            window.draw(txt);
            window.display();
        }
    }
    if (iButton == buttonEnter)
    {
        SetNewRecord(iPoints, nameString);
    }
}

void drawPoints(sf::RenderWindow &window, int iPoints, int &maxRecord)
{
    std::string sPoints;
    sPoints = "Number of points: " + std::to_string(iPoints);
    drawPlayerPonts(window, sPoints, nowPointsLeft);
    sPoints = "Record points: " + std::to_string(maxRecord);
    drawPlayerPonts(window, sPoints, recordPointsLeft);
}

#endif