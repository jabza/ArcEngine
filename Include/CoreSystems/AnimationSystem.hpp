////////////////////////////////////////////////////////////
// AnimationSystem.hpp
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

#include "CoreComponents/CAnimation.hpp"

////////////////////////////////////////////////////////////
/// \brief System for animating keyframes in CAnimation
/// components.
////////////////////////////////////////////////////////////
class AnimationSystem : public entityx::System<AnimationSystem>
{
public:
                    AnimationSystem(Arc::Context context);
                    ~AnimationSystem();
    
    void            update(entityx::EntityManager& entities,
                    entityx::EventManager& events, float dt) override;

private:
    bool            advanceFrame(entityx::Entity entity);
    void            resetAnimation(entityx::Entity entity);

    Arc::Logger     mLog;
    Arc::Context    mContext;
};
