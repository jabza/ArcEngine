////////////////////////////////////////////////////////////
// Engine.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Core/Engine.hpp"

using namespace Arc;

Engine::Engine()
: mPopStates(0)
, mRequestQuit(false)
, mLog("Engine")
{
    mLog.l("Initialising...");

    if(!mResourceManager.parse("config.xml"))
        throw std::runtime_error("Could not parse config.xml, aborting.");
        
    mActiveConfig = mResourceManager.getConfig("Default");
    mLog.l("Engine Created.");
}


Engine::~Engine()
{
    mLog.l("Destroying Engine...");
}


void Engine::run()
{
    mWindow.create(mActiveConfig.getVidMode(), mActiveConfig.getWinTitle()+" BUILD: "+std::to_string(VERSION), mActiveConfig.getWinStyle());
    mWindow.resetGLStates();

    changeState();

    while(!mStates.empty())
    {
        handleEvents();
        updateState();
        renderState();

		if(mRequestQuit)
			mStates.clear();
        else if(mPushStates.size() > 0 || mPopStates > 0)
            changeState();
    }

    mWindow.close();
}


void Engine::quit()
{
	mRequestQuit = true;
}


void Engine::popState()
{
    mPopStates++;
}


State& Engine::getActiveState()
{
    if(mStates.empty())
        throw std::runtime_error("No active State!");
    
    return *mStates.front();
}


const GameConfig& Engine::getActiveConfig()
{
    return mActiveConfig;
}


void Engine::changeState()
{
    // Pop States.
    for(unsigned int i = 0; i < mPopStates; i++)
    {
		if(!mStates.empty())
		{
			mStates.pop_front();

			if(!mStates.empty())
				getActiveState().resume();
		}
    }
    mPopStates = 0;

    // Push States.
    for(auto& stateIntent : mPushStates)
    {
        if(!mStates.empty())
            getActiveState().pause();

		mStates.push_front(stateIntent(getContext()));
    }
    mPushStates.clear();
}


void Engine::handleEvents()
{
    mInputManager.clearTriggered();

    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        mInputManager.handleEvent(event);
        getActiveState().handleEvent(event);
    }

    if(mInputManager.wasTriggered(Controls::Exit))
        quit();
}


void Engine::updateState()
{
    getActiveState().update(mFrameClock.restart());
}


void Engine::renderState()
{
    mWindow.clear(sf::Color::Black);

    getActiveState().draw(mWindow);

    mWindow.display();
}


Context Engine::getContext()
{
    return Context(this, &mWindow, &mResourceManager, &mInputManager);
}
