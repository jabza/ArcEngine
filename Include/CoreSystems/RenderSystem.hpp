////////////////////////////////////////////////////////////
// RenderSystem.hpp
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
#include "Core/Logger.hpp"
#include "Core/Context.hpp"

////////////////////////////////////////////////////////////
/// \brief System for rendering any renderable component
/// to a render target.
////////////////////////////////////////////////////////////
class RenderSystem : public entityx::System<RenderSystem>
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    /// \param context The game's Context.
    ////////////////////////////////////////////////////////////
                    RenderSystem(Arc::Context context);

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ////////////////////////////////////////////////////////////
                    ~RenderSystem();    
    
    ////////////////////////////////////////////////////////////
    /// \brief Sets the root entity to render the scene graph
    /// from.
    ////////////////////////////////////////////////////////////
    void			setRenderRoot(entityx::Entity root);
    
    ////////////////////////////////////////////////////////////
    /// \brief Updates the System.
    ////////////////////////////////////////////////////////////
    void			update(entityx::EntityManager& entities,
					entityx::EventManager& events, float dt) override;

private:
    ////////////////////////////////////////////////////////////
    /// \brief Renders any renderable component the entity has.
    ////////////////////////////////////////////////////////////
    void			renderEntity(entityx::Entity entity, sf::RenderStates worldStates);

    ////////////////////////////////////////////////////////////
    // Member data.
    ////////////////////////////////////////////////////////////    
    Arc::Logger		mLog;
    Arc::Context	mContext;
    entityx::Entity	mRenderRoot;
};

