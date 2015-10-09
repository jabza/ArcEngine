////////////////////////////////////////////////////////////
// CCollider.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreComponents/CCollider.hpp"


CCollider::CCollider(sf::FloatRect alignedBounds)
: mVertices(sf::Quads, 4)
{
    setBounds(alignedBounds);
}


CCollider::CCollider(sf::VertexArray vertices)
: mVertices(vertices)
{
}


void CCollider::setBounds(sf::FloatRect alignedBounds)
{
    mVertices[0].position = sf::Vector2f(alignedBounds.left, alignedBounds.top);
    mVertices[1].position = sf::Vector2f(alignedBounds.left+alignedBounds.width, alignedBounds.top);
    mVertices[2].position = sf::Vector2f(alignedBounds.left+alignedBounds.width, alignedBounds.top+alignedBounds.height);
    mVertices[3].position = sf::Vector2f(alignedBounds.left, alignedBounds.top+alignedBounds.height);
}


void CCollider::setBounds(sf::VertexArray vertices)
{
    mVertices = vertices;
}


sf::Vector2f CCollider::getSize()
{
    auto bb = getAlignedBounds();
    
    return sf::Vector2f(bb.width, bb.height);
}


sf::FloatRect CCollider::getAlignedBounds()
{
    return mVertices.getBounds();
}


sf::FloatRect CCollider::getAlignedBounds(sf::Transform transform)
{
    return getVerts(transform).getBounds();
}


sf::VertexArray CCollider::getVerts()
{
    return mVertices;
}


sf::VertexArray CCollider::getVerts(sf::Transform transform)
{
    sf::VertexArray tmpVerts = mVertices;
    
    tmpVerts[0].position = transform.transformPoint(tmpVerts[0].position);
    tmpVerts[1].position = transform.transformPoint(tmpVerts[1].position);
    tmpVerts[2].position = transform.transformPoint(tmpVerts[2].position);
    tmpVerts[3].position = transform.transformPoint(tmpVerts[3].position);
    
    return tmpVerts;
}
