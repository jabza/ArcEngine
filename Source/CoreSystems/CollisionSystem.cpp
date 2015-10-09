////////////////////////////////////////////////////////////
// CollisionSystem.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreSystems/CollisionSystem.hpp"

#include "CoreComponents/CNode.hpp"
#include "CoreComponents/CCollider.hpp"


CollisionSystem::CollisionSystem(Arc::Context context)
: mLog("CollisionSystem")
, mContext(context)
{
    mLog.l("System Created!");
}


CollisionSystem::~CollisionSystem()
{
    mLog.l("System Destroyed!");
}


void CollisionSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, float dt)
{
    mTestedMap.clear();

    for(auto a : entities.entities_with_components<CNode, CCollider>())
    {
        auto nodeA = a.component<CNode>();
        auto colliderA = a.component<CCollider>();
        auto transformA = nodeA->getWorldTransform();

        if(nodeA->active)
        {
            for(auto b : entities.entities_with_components<CNode, CCollider>())
            {
                auto nodeB = b.component<CNode>();
                auto colliderB = b.component<CCollider>();
                auto transformB = nodeB->getWorldTransform();

                if(nodeB->active && a != b)
                {
                    //If this pair hasn't been tested.
                    if(mTestedMap[a].count(b) == 0)
                    {
                        if(colliderA->getAlignedBounds(transformA).intersects(colliderB->getAlignedBounds(transformB)))
                        {
                            if(intersects(colliderA->getVerts(transformA), colliderB->getVerts(transformB)))
                            {
                                if(colliderA->colliders.count(b) == 0 || colliderB->colliders.count(a) == 0)
                                {
                                    colliderA->colliders.emplace(b);
                                    colliderB->colliders.emplace(a);
                                };
                            }
                            else
                            {
                                colliderA->colliders.erase(b);
                                colliderB->colliders.erase(a);
                            }
                        }
                        else
                        {
                            colliderA->colliders.erase(b);
                            colliderB->colliders.erase(a);
                        }

                        mTestedMap[a].emplace(b);
                        mTestedMap[b].emplace(a);
                    }
                }
            }
        }
    }
}


bool CollisionSystem::contains(sf::VertexArray aBounds, sf::Vector2f point)
{
    sf::VertexArray pointVerts(sf::Quads, 4);
    pointVerts[0].position = sf::Vector2f(point.x, point.y);
    pointVerts[1].position = sf::Vector2f(point.x+2, point.y);
    pointVerts[2].position = sf::Vector2f(point.x+2, point.y+2);
    pointVerts[3].position = sf::Vector2f(point.x, point.y+2);
    
    return intersects(aBounds, pointVerts);
}


bool CollisionSystem::intersects(sf::VertexArray aBounds, sf::VertexArray bBounds)
{
    for(sf::Vector2f& axis : getAxes(aBounds))
    {
        sf::Vector2f proj1 = getProjection(aBounds, axis);
        sf::Vector2f proj2 = getProjection(bBounds, axis);
        
        //If they DON'T overlap, a separating axis was found! No collision!
        if(!(proj1.x < proj2.y && proj1.y > proj2.x))
            return false;
    }

    for(sf::Vector2f& axis : getAxes(bBounds))
    {
        sf::Vector2f proj1 = getProjection(aBounds, axis);
        sf::Vector2f proj2 = getProjection(bBounds, axis);
        
        //If they DON'T overlap, a separating axis was found! No collision!
        if(!(proj1.x < proj2.y && proj1.y > proj2.x))
            return false;
    }
    
    return true;
}


std::list<sf::Vector2f> CollisionSystem::getAxes(sf::VertexArray& verts)
{
    std::list<sf::Vector2f> axes;

    sf::Vector2f axis1 = verts[0].position - verts[1].position;
    sf::Vector2f axis2 = verts[1].position - verts[2].position;

    axes.emplace_back(-axis1.y, axis1.x);
    axes.emplace_back(-axis2.y, axis2.x);

    return axes;
}


sf::Vector2f CollisionSystem::getProjection(sf::VertexArray& verts, sf::Vector2f& axis)
{
    float dp = 0;
    dp += verts[0].position.x * axis.x;
    dp += verts[0].position.y * axis.y;

    sf::Vector2f projection(dp, dp);

    for(int v = 0; v < 4; v++)
    {
        dp = 0;
        dp += verts[v].position.x * axis.x;
        dp += verts[v].position.y * axis.y;
        
        if(dp < projection.x)
            projection.x = dp;
        else if(dp > projection.y)
            projection.y = dp;
    }
    
    return projection;
}

