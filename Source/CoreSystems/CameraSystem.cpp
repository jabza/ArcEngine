////////////////////////////////////////////////////////////
// CameraSystem.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreSystems/CameraSystem.hpp"
#include "Core/Engine.hpp"

#include "CoreComponents/CNode.hpp"


CameraSystem::CameraSystem(Arc::Context context)
: mLog("CameraSystem")
, mContext(context)
{
    mLog.l("System Created!");
}


CameraSystem::~CameraSystem()
{
    mLog.l("System Destroyed!");
}


void CameraSystem::configure(entityx::EventManager& events)
{
    events.subscribe<entityx::ComponentAddedEvent<CCameraTarget>>(*this);
    events.subscribe<entityx::ComponentRemovedEvent<CCameraTarget>>(*this);
    events.subscribe<entityx::EntityDestroyedEvent>(*this);
}


void CameraSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, float dt)
{
    if(!mTargets.empty() && mTargets.front().valid())
    {
        auto node = mTargets.front().component<CNode>();
        
        mContext.engine->getActiveState().getCamera().setCenter((node->getWorldTransform()*(node->transform.getOrigin())));
        mContext.engine->getActiveState().getCamera().setRotation(node->getWorldRotation());
        
        sf::Listener::setPosition(mContext.engine->getActiveState().getCamera().getCenter().x, 0, mContext.engine->getActiveState().getCamera().getCenter().y);
    }
}


void CameraSystem::receive(const entityx::ComponentAddedEvent<CCameraTarget>& event)
{
    mTargets.push_front(event.entity);
}


void CameraSystem::receive(const entityx::ComponentRemovedEvent<CCameraTarget>& event)
{
    mTargets.remove(event.entity);
}


void CameraSystem::receive(const entityx::EntityDestroyedEvent& event)
{
    mTargets.remove(event.entity);
}
