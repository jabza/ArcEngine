////////////////////////////////////////////////////////////
// State.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "States/State.hpp"

////////////////////////////////////////////////////////////
// System Headers
////////////////////////////////////////////////////////////
#include "CoreSystems/NodeSystem.hpp"
#include "CoreSystems/RenderSystem.hpp"
#include "CoreSystems/ShaderSystem.hpp"
#include "CoreSystems/SoundSystem.hpp"
#include "CoreSystems/CollisionSystem.hpp"
#include "CoreSystems/AnimationSystem.hpp"
#include "CoreSystems/CameraSystem.hpp"


State::State(State::ID state, Arc::Context context)
: mLog("State "+std::to_string(state))
, mStateID(state)
, mContext(context)
, mCamera(mContext.window->getDefaultView())
{
}


State::~State()
{
   onDestroy();
}


const State::ID State::getStateID() const
{
    return mStateID;
}


sf::View& State::getCamera()
{
    return mCamera;
}


EventManager& State::getEventManager()
{
    return mEntityx.events;
}


EntityManager& State::getEntityManager()
{
    return mEntityx.entities;
}


SystemManager& State::getSystemManager()
{
    return mEntityx.systems;
}


entityx::Entity State::getLayer(int layer)
{
    if(layer >= 0 && layer < State::Layers::TOTAL)
        return mLayers[layer];
    
    entityx::Entity empty;
    return empty;
}


void State::addToLayer(int layer, entityx::Entity entity)
{
    if(layer >= 0 && layer < State::Layers::TOTAL)
        mLayers[layer].component<CNode>()->addChild(entity);
}


void State::create()
{
    //Setup dependencies.

    //Setup core systems.
    getSystemManager().add<NodeSystem>();
    getSystemManager().add<RenderSystem>(mContext);
    getSystemManager().add<ShaderSystem>();
    getSystemManager().add<SoundSystem>(mContext);
    getSystemManager().add<CollisionSystem>(mContext);
    getSystemManager().add<AnimationSystem>(mContext);
    getSystemManager().add<CameraSystem>(mContext);

    //Configure.
    getSystemManager().configure();
    
    //Setup layers.
    for(int l = 0; l < State::Layers::TOTAL; l++)
    {
        entityx::Entity layer = getEntityManager().create();
        layer.assign<CNode>();
        mLayers.push_back(layer);
    }
    
    onCreate();
}


void State::destroy()
{
    onDestroy();
}


void State::pause()
{
    onPause();
}


void State::resume()
{
    onResume();
}


void State::handleEvent(const sf::Event &event)
{
    onHandleEvent(event);
}


void State::update(const sf::Time& delta)
{
    getSystemManager().update<NodeSystem>(delta.asSeconds());
    getSystemManager().update<CameraSystem>(delta.asSeconds());
    getSystemManager().update<SoundSystem>(delta.asSeconds());
    getSystemManager().update<CollisionSystem>(delta.asSeconds());
    getSystemManager().update<AnimationSystem>(delta.asSeconds());
    getSystemManager().update<ShaderSystem>(delta.asSeconds());
    
    onUpdate(delta);
}


void State::draw(sf::RenderWindow& window)
{
    //Render Scene entities with camera view.
    window.setView(mCamera);

    for(unsigned int l = 0; l < Layers::UI; l++)
    {
        getSystemManager().system<RenderSystem>()->setRenderRoot(mLayers[l]);
        getSystemManager().update<RenderSystem>(0);
    }

    //Render UI entities with default view.
    window.setView(window.getDefaultView());

    for(unsigned int l = Layers::UI; l < Layers::TOTAL; l++)
    {
        getSystemManager().system<RenderSystem>()->setRenderRoot(mLayers[l]);
        getSystemManager().update<RenderSystem>(0);
    }

    onDraw(window);
}
