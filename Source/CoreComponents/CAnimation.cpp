////////////////////////////////////////////////////////////
// CAnimation.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#include "CoreComponents/CAnimation.hpp"


CAnimation::CAnimation(bool loop)
: loop(loop)
, onFinish([](entityx::Entity e, Arc::Context c){})
, mFrameCount(0)
{
}


void CAnimation::addKeyframe(sf::Transformable transform, float duration)
{
    mKeyframes.emplace_back(transform, duration);
}
