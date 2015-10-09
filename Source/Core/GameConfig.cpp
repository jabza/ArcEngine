////////////////////////////////////////////////////////////
// GameConfig.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Core/GameConfig.hpp"

using namespace Arc;

GameConfig::GameConfig()
: mVidMode(sf::VideoMode(800, 600, 32)), mWinTitle("untitled"), mWinStyle(sf::Style::Close), mWinFPS(60), mWinVSync(false), mLanguage(Language::English)
{
}


GameConfig::GameConfig(sf::VideoMode vMode, sf::String wTitle, int wStyle, int wFPS, bool wVSync, Language lang)
: mVidMode(vMode), mWinTitle(wTitle), mWinStyle(wStyle), mWinFPS(wFPS), mWinVSync(wVSync), mLanguage(lang)
{
}

GameConfig::~GameConfig()
{
}

void GameConfig::setLanguage(const Language& language)
{
    mLanguage = language;
}


void GameConfig::setWinFPS(int winFPS)
{
    mWinFPS = winFPS;
}


void GameConfig::setVidMode(const sf::VideoMode& vidMode)
{
    mVidMode = vidMode;
}


void GameConfig::setWinStyle(int winStyle)
{
    mWinStyle = winStyle;
}


void GameConfig::setWinTitle(const sf::String& winTitle)
{
        mWinTitle = winTitle;
}


void GameConfig::setWinVSync(bool winVSync)
{
    mWinVSync = winVSync;
}


const GameConfig::Language& GameConfig::getLanguage() const
{
    return mLanguage;
}


int GameConfig::getWinFPS() const
{
    return mWinFPS;
}


const sf::VideoMode& GameConfig::getVidMode() const
{
    return mVidMode;
}


int GameConfig::getWinStyle() const
{
    return mWinStyle;
}


const sf::String& GameConfig::getWinTitle() const
{
    return mWinTitle;
}


bool GameConfig::isWinVSync() const
{
    return mWinVSync;
}


sf::Vector2f GameConfig::getWinSize() const
{
    return sf::Vector2f((float)mVidMode.width, (float)mVidMode.height);
}


