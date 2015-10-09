////////////////////////////////////////////////////////////
// MainMenuState.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <CoreComponents/CNode.hpp>
#include <CoreComponents/CRenderText.hpp>
#include <CoreComponents/CCollider.hpp>
#include <CoreComponents/CAnimation.hpp>
#include <CoreComponents/CAudioSource.hpp>
#include "States/MainMenuState.hpp"

MainMenuState::MainMenuState(Arc::Context context)
: State(State::ID::MAIN_MENU, context)
{
}


void MainMenuState::onCreate()
{
    e = getEntityManager().create();
    auto node = e.assign<CNode>(mContext.window->getSize().x/2, mContext.window->getSize().y/2, Arc::Origin::CENTRE);

    sf::Text msg(mContext.resources->getString("WelcomeMsg"), mContext.resources->getFont("Default"));

    e.assign<CRenderText>(msg);
    e.assign<CCollider>(msg.getLocalBounds());
    e.assign<CAudioSource>(sf::Sound(mContext.resources->getSound("Click")));

    auto t = node->transform;
    t.setScale(2, 2);
    e.assign<CAnimation>(true)->addKeyframe(t, 1);
    t.setScale(1, 1);
    e.component<CAnimation>()->addKeyframe(t, 1);

    addToLayer(Layers::UI, e);

    mContext.input->mapKey(sf::Keyboard::Return, Arc::Controls::PlaySound);
    mContext.input->mapKey(sf::Keyboard::Space, Arc::Controls::PlaySound);
}


void MainMenuState::onUpdate(const sf::Time& delta)
{
    if(mContext.input->wasTriggered(Arc::Controls::PlaySound))
        e.component<CAudioSource>()->audioClip.play();
}

