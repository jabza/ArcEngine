////////////////////////////////////////////////////////////
// CNode.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreComponents/CNode.hpp"


CNode::CNode(sf::Vector2f position, Arc::Origin origin)
: active(true)
, visible(true)
, origin(origin)
, mCull(false)
{
    transform.setPosition(position);
}


CNode::CNode(float x, float y, Arc::Origin origin)
: active(true)
, visible(true)
, origin(origin)
, mCull(false)
{
    transform.setPosition(sf::Vector2f(x, y));
}


CNode::~CNode()
{
}


entityx::ComponentHandle<CNode> CNode::getRootNode()
{
    if(!getParentNode()->mParent.valid())
        return getParentNode();

    return getParentNode()->getRootNode();
}


entityx::ComponentHandle<CNode> CNode::getParentNode()
{
    return mParent.component<CNode>();
}


entityx::Entity CNode::getParent()
{
    return mParent;
}


std::set<entityx::Entity> CNode::getChildren()
{
    return mChildren;
}


bool CNode::hasChild(entityx::Entity child)
{
    if(mChildren.count(child) > 0)
        return true;
    else
    {
        for(entityx::Entity c : mChildren)
        {
            if(c.component<CNode>()->hasChild(child))
                return true;
        }
    }

    return false;
}


void CNode::addChild(entityx::Entity child)
{
    mAddChildren.insert(child);
}


void CNode::removeChild(entityx::Entity child)
{
    mRemoveChildren.insert(child);
}


void CNode::removeChildren()
{
    for(auto c : mChildren)
    {
        removeChild(c);
    }
}


sf::Transform CNode::getTransform()
{
    return transform.getTransform();
}


sf::Transform CNode::getWorldTransform()
{
    return mWorldTransform;
}


sf::Vector2f CNode::getPosition()
{
    return transform.getPosition();
}


sf::Vector2f CNode::getWorldPosition()
{
    return mWorldTransform * sf::Vector2f();
}


float CNode::getRotation()
{
    return transform.getRotation();
}


float CNode::getWorldRotation()
{
    return mWorldRotation;
}


bool CNode::getWorldVisibility()
{
    if(!visible)
        return false;
    else if(mParent)
    {
        if(getParentNode()->visible)
            return getParentNode()->getWorldVisibility();
        else
            return false;
    }

    return visible;
}


void CNode::addTag(Tags tag)
{
    mTags.insert(tag);
}


void CNode::removeTag(Tags tag)
{
    mTags.erase(tag);
}


bool CNode::hasTag(Tags tag)
{
    if(mTags.count(tag) > 0)
        return true;

    return false;
}


void CNode::cull()
{
    mCull = true;
}