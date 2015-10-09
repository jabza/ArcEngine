////////////////////////////////////////////////////////////
// Context.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

namespace sf
{
	class RenderWindow;
}

////////////////////////////////////////////////////////////
/// \brief Immutable struct for allowing shared access to engine.
////////////////////////////////////////////////////////////
namespace Arc
{
    class Engine;
	class ResourceManager;
	class InputManager;

    struct Context
    {
        Context(Engine *pArc, sf::RenderWindow *pWindow, ResourceManager *pResources, InputManager *pInput)
        : engine(pArc), window(pWindow), resources(pResources), input(pInput){}

        Engine * const          engine;
        sf::RenderWindow* const window;
        ResourceManager* const  resources;
        InputManager* const     input;
    };
}