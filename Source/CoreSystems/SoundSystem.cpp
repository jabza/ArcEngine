////////////////////////////////////////////////////////////
// SoundSystem.cpp
//
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreSystems/SoundSystem.hpp"


SoundSystem::SoundSystem(Arc::Context context)
: mLog("SoundSystem")
, mContext(context)
{
    mLog.l("System Created!");
}


SoundSystem::~SoundSystem()
{
    mLog.l("System Destroyed!");
}


void SoundSystem::configure(entityx::EventManager& events)
{
    events.subscribe<entityx::ComponentRemovedEvent<CAudioSource>>(*this);
    events.subscribe<entityx::EntityDestroyedEvent>(*this);
}


void SoundSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, float dt)
{
    for(auto e : entities.entities_with_components<CNode, CAudioSource>())
    {
        auto audioSource = e.component<CAudioSource>();

        if(audioSource->mute)
            audioSource->audioClip.setVolume(0);
        else
            audioSource->audioClip.setVolume(audioSource->volume);
    }
}


void SoundSystem::receive(const entityx::ComponentRemovedEvent<CAudioSource>& event)
{
    auto entity = event.entity;

    if(entity.component<CAudioSource>())
        entity.component<CAudioSource>()->audioClip.stop();
}


void SoundSystem::receive(const entityx::EntityDestroyedEvent& event)
{
    auto entity = event.entity;

    if(entity.component<CAudioSource>())
        entity.component<CAudioSource>()->audioClip.stop();
}
