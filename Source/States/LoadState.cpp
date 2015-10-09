////////////////////////////////////////////////////////////
// LoadState.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "States/LoadState.hpp"
#include "States/MainMenuState.hpp"
#include "Core/Engine.hpp"

LoadState::LoadState(Arc::Context context)
: State(State::ID::LOAD, context)
{
}


void LoadState::onCreate()
{
    mContext.resources->parse("fonts/fonts.xml");
    mContext.resources->parse("textures/textures.xml");
    mContext.resources->parse("sounds/sounds.xml");
    mContext.resources->parse("music/music.xml");

    switch(mContext.engine->getActiveConfig().getLanguage())
    {
		case Arc::GameConfig::Language::English : mContext.resources->parse("strings/en.xml"); break;
        default                            : mContext.resources->parse("strings/en.xml"); break;
    }
}


void LoadState::onUpdate(const sf::Time& delta)
{
    mContext.engine->pushState(new MainMenuState(mContext), true);
}
