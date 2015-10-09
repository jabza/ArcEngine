////////////////////////////////////////////////////////////
// InputManager.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Core/InputManager.hpp"

using namespace Arc;

InputManager::InputManager()
: mHasFocus(true)
, mHasMouse(true)
, mLog("InputManager")
{
    mapButton(sf::Mouse::Button::Left, Controls::PrimarySelect);
    mapButton(sf::Mouse::Button::Right, Controls::SecondarySelect);
    
    mapKey(sf::Keyboard::Escape, Controls::Exit);
}


InputManager::~InputManager()
{
}


void InputManager::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::LostFocus)
        mHasFocus = false;
    else if(event.type == sf::Event::GainedFocus)
        mHasFocus = true;

    if(event.type == sf::Event::MouseEntered)
        mHasMouse = true;
    else if(event.type == sf::Event::MouseLeft)
        mHasMouse = false;

    if(event.type == sf::Event::Closed)
        mTriggered[Controls::Exit] = true;

    if(event.type == sf::Event::KeyReleased)
    {
        if(mKeyBindings.count(event.key.code) > 0)
            mTriggered[getControl(event.key.code)] = true;
    }

    if(event.type == sf::Event::MouseButtonReleased)
    {
        if(mButtonBindings.count(event.mouseButton.button) > 0)
            mTriggered[getControl(event.mouseButton.button)] = true;
    }

    if(event.type == sf::Event::MouseMoved)
    {
        mLocalMousePosition.x = (float)event.mouseMove.x;
        mLocalMousePosition.y = (float)event.mouseMove.y;
    }
}


void InputManager::clearTriggered()
{
    mTriggered.clear();
}


const bool InputManager::hasFocus() const
{
    return mHasFocus;
}


const bool InputManager::hasMouse() const
{
    return mHasMouse;
}


void InputManager::mapKey(sf::Keyboard::Key key, Controls ctrl)
{
    mKeyBindings[key] = ctrl;
}


void InputManager::mapButton(sf::Mouse::Button button, Controls ctrl)
{
    mButtonBindings[button] = ctrl;
}


std::list<sf::Keyboard::Key> InputManager::getKeys(Controls ctrl)
{
    std::list<sf::Keyboard::Key> keys;
    
    for(auto keyCtrl : mKeyBindings)
    {
        if(keyCtrl.second == ctrl)
            keys.push_back(keyCtrl.first);
    }
    
    return keys;
}


std::list<sf::Mouse::Button> InputManager::getButtons(Controls ctrl)
{
    std::list<sf::Mouse::Button> btns;
    
    for(auto btnCtrl : mButtonBindings)
    {
        if(btnCtrl.second == ctrl)
            btns.push_back(btnCtrl.first);
    }
    
    return btns;
}


Controls InputManager::getControl(sf::Keyboard::Key key)
{
    if(mKeyBindings.count(key) > 0)
        return mKeyBindings[key];
    
    return Controls::Unbound;
}


Controls InputManager::getControl(sf::Mouse::Button btn)
{
    if(mButtonBindings.count(btn) > 0)
        return mButtonBindings[btn];
    
    return Controls::Unbound;
}


bool InputManager::isPressed(Controls ctrl)
{
    auto keys = getKeys(ctrl);
    auto btns = getButtons(ctrl);
    
    for(auto key : keys)
    {
        if(sf::Keyboard::isKeyPressed(key))
            return true;
    }
    
    for(auto btn : btns)
    {
        if(sf::Mouse::isButtonPressed(btn))
            return true;
    }
    
    return false;
}


bool InputManager::wasTriggered(Controls ctrl)
{
    return mTriggered[ctrl];
}


sf::Vector2f InputManager::getMousePos()
{
    return mLocalMousePosition;
}
