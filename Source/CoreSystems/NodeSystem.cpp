////////////////////////////////////////////////////////////
// NodeSystem.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreSystems/NodeSystem.hpp"
#include "CoreComponents/CCollider.hpp"

using namespace Arc;


NodeSystem::NodeSystem()
: mLog("NodeSystem")
{
    mLog.l("System Created!");
}


NodeSystem::~NodeSystem()
{
    mLog.l("System Destroyed!");
}


void NodeSystem::configure(entityx::EventManager& events)
{
    events.subscribe<entityx::ComponentRemovedEvent<CNode>>(*this);
    events.subscribe<entityx::EntityDestroyedEvent>(*this);
}


void NodeSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, float dt)
{
    std::set<entityx::Entity> cullQueue;

    for(auto e : entities.entities_with_components<CNode>())
    {
        if(e.component<CNode>()->active)
        {
            assessNodeRemovals(e);
            assessNodeAdditions(e);

            updateOrigin(e);
            updateWorldTransform(e);
            updateWorldRotation(e);

            if(e.component<CNode>()->mCull)
                cullQueue.insert(e);
        }
    }

    for(entityx::Entity e : cullQueue)
    {
        e.destroy();
    }
}


void NodeSystem::receive(const entityx::ComponentRemovedEvent<CNode>& event)
{
    auto entity = event.entity;
    auto node = event.component;
    
    if(node)
    {
        if(node->mParent)
            node->mParent.component<CNode>()->removeChild(entity);
        
        node->removeChildren();
        assessNodeRemovals(entity);
    }
}


void NodeSystem::receive(const entityx::EntityDestroyedEvent& event)
{
    auto entity = event.entity;
    auto node = entity.component<CNode>();
    
    if(node)
    {
        if(node->mParent)
        {
            if(node->mParent.component<CNode>())
                node->mParent.component<CNode>()->removeChild(entity);
        }
        
        node->removeChildren();
        assessNodeRemovals(entity);
    }
}


void NodeSystem::assessNodeRemovals(entityx::Entity entity)
{
    if(entity.valid())
    {
        auto node = entity.component<CNode>();
        if(node)
        {
            if(node->mCull)
                node->removeChildren();

            for(entityx::Entity dc : node->mRemoveChildren)
            {
                if(node->hasChild(dc))
                {
                    node->mChildren.erase(dc);
                    if(dc)
                    {
                        dc.component<CNode>()->cull();
                        for(entityx::Entity gc : dc.component<CNode>()->getChildren())
                        {
                            if(gc)
                            {
                                gc.component<CNode>()->cull();
                                assessNodeRemovals(gc);
                            }
                        }
                    }
                }
            }
            node->mRemoveChildren.clear();
        }
    }
}


void NodeSystem::assessNodeAdditions(entityx::Entity entity)
{
    if(entity.valid())
    {
        auto node = entity.component<CNode>();
        if(node)
        {
            for(entityx::Entity ac : node->mAddChildren)
            {
                if(ac.valid())
                {
                    if(!node->hasChild(ac) && ac.component<CNode>() && entity != ac)
                    {
                        auto wp = ac.component<CNode>()->getWorldPosition();

                        //Replaces owner.
                        if(ac.component<CNode>()->mParent)
                            ac.component<CNode>()->mParent.component<CNode>()->mChildren.erase(ac);

                        ac.component<CNode>()->mParent = entity;
                        node->mChildren.insert(ac);
                    }
                }
            }
            node->mAddChildren.clear();
        }
    }
}


void NodeSystem::updateOrigin(entityx::Entity entity)
{
    auto node = entity.component<CNode>();
    auto collider = entity.component<CCollider>();

    if(node && collider)
    {
        auto size = collider->getSize();

        switch(node->origin)
        {
            case Origin::NORTH       : node->transform.setOrigin(size.x/2, 0); break;
            case Origin::NORTH_EAST  : node->transform.setOrigin(size.x, 0); break;
            case Origin::EAST        : node->transform.setOrigin(size.x, size.y/2); break;
            case Origin::SOUTH_EAST  : node->transform.setOrigin(size.x, size.y); break;
            case Origin::SOUTH       : node->transform.setOrigin(size.x/2, size.y); break;
            case Origin::SOUTH_WEST  : node->transform.setOrigin(0, size.y); break;
            case Origin::WEST        : node->transform.setOrigin(0, size.y/2); break;
            case Origin::NORTH_WEST  : node->transform.setOrigin(0, 0); break;
            case Origin::CENTRE      : node->transform.setOrigin(size.x/2, size.y/2); break;
        }
    }
}


void NodeSystem::updateWorldTransform(entityx::Entity entity)
{
    sf::Transform worldTransform = sf::Transform::Identity;
    
    for(entityx::Entity node = entity; node.valid(); node = node.component<CNode>()->mParent)
    {
        worldTransform = node.component<CNode>()->getTransform() * worldTransform;
    }
    
    entity.component<CNode>()->mWorldTransform = worldTransform;
}


void NodeSystem::updateWorldRotation(entityx::Entity entity)
{
    float worldRotation = 0;
    
    for(entityx::Entity node = entity; node.valid(); node = node.component<CNode>()->mParent)
    {
        worldRotation += node.component<CNode>()->getRotation();
    }
    
    if(worldRotation > 360)
        worldRotation -= floor(worldRotation/360)*360;
    
    entity.component<CNode>()->mWorldRotation = worldRotation;
}
