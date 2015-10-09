////////////////////////////////////////////////////////////
// CAnimation.hpp
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
#include <vector>
#include "Core/Context.hpp"

////////////////////////////////////////////////////////////
/// \brief Animates an entitie's sf::Transformable.
////////////////////////////////////////////////////////////
class CAnimation : public entityx::Component<CAnimation>
{
friend class AnimationSystem;
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ////////////////////////////////////////////////////////////
                                                        CAnimation(bool loop = false);

    ////////////////////////////////////////////////////////////
    /// \brief Pushes a new keyframe to the animation queue.
    ////////////////////////////////////////////////////////////
    void                                                addKeyframe(sf::Transformable transform, float duration);

    bool                                                loop;

    std::function<void
    (entityx::Entity e, Arc::Context c)>                onFinish;
    
private:
    ////////////////////////////////////////////////////////////
    // Member data.
    ////////////////////////////////////////////////////////////
    unsigned int                                        mFrameCount;

    sf::Vector2f                                        mMoveVector, mScaleVector;
    float                                               mRotateVector;

    std::vector<std::pair<sf::Transformable, float>>    mKeyframes;
    sf::Time                                            mTimer;
};
