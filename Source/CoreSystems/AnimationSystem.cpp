////////////////////////////////////////////////////////////
// AnimationSystem.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreSystems/AnimationSystem.hpp"
#include "CoreComponents/CNode.hpp"


AnimationSystem::AnimationSystem(Arc::Context context)
: mLog("AnimationSystem")
, mContext(context)
{
    mLog.l("System Created!");
}


AnimationSystem::~AnimationSystem()
{
    mLog.l("System Destroyed!");
}


void AnimationSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, float dt)
{
    for(auto e : entities.entities_with_components<CNode, CAnimation>())
    {
        auto node = e.component<CNode>();
        auto anim = e.component<CAnimation>();

		if(!anim->mKeyframes.empty())
		{
			if(anim->mFrameCount == 0 && anim->mTimer.asSeconds() == 0)
				resetAnimation(e);

			if(anim->mTimer.asSeconds() >= anim->mKeyframes[anim->mFrameCount].second)
			{
				if(!advanceFrame(e))
				{
					if(!anim->loop)
					{
						anim->onFinish(e, mContext);
						e.remove<CAnimation>();
						continue;
					}
					else
						resetAnimation(e);
				}
			}
			else
			{
				node->transform.move(anim->mMoveVector*dt);
				node->transform.setScale(node->transform.getScale() + (anim->mScaleVector*dt));
				node->transform.rotate(anim->mRotateVector*dt);

				anim->mTimer += sf::seconds(dt);
			}
		}
    }
}


bool AnimationSystem::advanceFrame(entityx::Entity entity)
{
    auto node = entity.component<CNode>();
    auto anim = entity.component<CAnimation>();

	if(anim->mFrameCount + 1 < anim->mKeyframes.size())
	{
		anim->mFrameCount++;
		anim->mTimer = sf::seconds(0);

		auto currFrame = anim->mKeyframes[anim->mFrameCount];
		anim->mMoveVector = (currFrame.first.getPosition() - node->transform.getPosition()) / currFrame.second;
		anim->mScaleVector = (currFrame.first.getScale() - node->transform.getScale()) / currFrame.second;
		anim->mRotateVector = (currFrame.first.getRotation() - node->transform.getRotation()) / currFrame.second;

		return true;
	}

	return false;
}


void AnimationSystem::resetAnimation(entityx::Entity entity)
{
    entity.component<CAnimation>()->mFrameCount = -1;
    advanceFrame(entity);
}
