////////////////////////////////////////////////////////////
// CRenderRect.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
/// \brief Holds a renderable sf::RectangleShape.
////////////////////////////////////////////////////////////
struct CRenderRect 
: entityx::Component<CRenderRect>
{
    CRenderRect(sf::RectangleShape rectangleShape = sf::RectangleShape())
    : rectangleShape(rectangleShape){}

    sf::RectangleShape rectangleShape;
};

