////////////////////////////////////////////////////////////
// SoundSystem.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include "Core/Logger.hpp"
#include "Core/Context.hpp"
#include "CoreComponents/CAudioSource.hpp"
#include "CoreComponents/CNode.hpp"

////////////////////////////////////////////////////////////
/// \brief System for playing all audio.
////////////////////////////////////////////////////////////
class SoundSystem
: public entityx::System<SoundSystem>
, public entityx::Receiver<SoundSystem>
{
public:
                    SoundSystem(Arc::Context context);
                    ~SoundSystem();

    ////////////////////////////////////////////////////////////
    /// \brief Configures any event handlers.
    /// \param events The EventManager.
    ////////////////////////////////////////////////////////////
    void            configure(entityx::EventManager& events) override;
    
    void            update(entityx::EntityManager& entities,
                    entityx::EventManager& events, float dt) override;

    ////////////////////////////////////////////////////////////
    /// \brief Event handler for CNode component removed event.
    /// \param events The EventManager.
    ////////////////////////////////////////////////////////////
    void            receive(const entityx::ComponentRemovedEvent<CAudioSource>& event);

    ////////////////////////////////////////////////////////////
    /// \brief Event handler for entity destroyed event.
    /// \param events The EventManager.
    ////////////////////////////////////////////////////////////
    void            receive(const entityx::EntityDestroyedEvent& event);

private:
    Arc::Logger     mLog;
    Arc::Context    mContext;
};
