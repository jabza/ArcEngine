////////////////////////////////////////////////////////////
// Engine.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "States/State.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/InputManager.hpp"
#include "Core/Context.hpp"

////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////
#define VERSION 1.0
#define PI 3.1415926535

////////////////////////////////////////////////////////////
/// \brief Controls the engine and game state.
////////////////////////////////////////////////////////////
namespace Arc
{
    class Engine : public sf::NonCopyable
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ////////////////////////////////////////////////////////////
                                Engine();

        ////////////////////////////////////////////////////////////
        /// \brief Default destructor
        ////////////////////////////////////////////////////////////
                                ~Engine();

        ////////////////////////////////////////////////////////////
        /// \brief Starts the game loop.
        ////////////////////////////////////////////////////////////
        void                    run();

        ////////////////////////////////////////////////////////////
        /// \brief Quits the game loop.
        ////////////////////////////////////////////////////////////
        void                    quit();

        ////////////////////////////////////////////////////////////
        /// \brief Pushes new State onto the stack.
        /// \param state The new State to push.
        /// \param destroyCurrent Destroy the current State.
        ////////////////////////////////////////////////////////////
        void                    pushState(State* state, bool destroyCurrent = false);

        ////////////////////////////////////////////////////////////
        /// \brief Pops the top State.
        ////////////////////////////////////////////////////////////
        void                    popState();

        ////////////////////////////////////////////////////////////
        /// \brief Gets a reference the currently running State.
        /// \return Active State reference.
        ////////////////////////////////////////////////////////////
        State&                  getActiveState();

        ////////////////////////////////////////////////////////////
        /// \brief Gets the currently active GameConfig object.
        /// \return Active GameConfig reference.
        ////////////////////////////////////////////////////////////
        const GameConfig&       getActiveConfig();

        ////////////////////////////////////////////////////////////
        /// \brief Creates a Context object.
        ////////////////////////////////////////////////////////////
        Arc::Context            getContext();

    private:
        ////////////////////////////////////////////////////////////
        /// \brief Executes any State changes.
        ////////////////////////////////////////////////////////////
        void                    changeState();

        ////////////////////////////////////////////////////////////
        /// \brief Handles SFML input events.
        ////////////////////////////////////////////////////////////
        void                    handleEvents();

        ////////////////////////////////////////////////////////////
        /// \brief Updates the current State.
        ////////////////////////////////////////////////////////////
        void                    updateState();

        ////////////////////////////////////////////////////////////
        /// \brief Renders the current State.
        ////////////////////////////////////////////////////////////
        void                    renderState();

        ////////////////////////////////////////////////////////////
        // Member data.
        ////////////////////////////////////////////////////////////
        std::list<State::Ptr>   mStates;

        std::list<std::pair
        <State::Ptr, bool>>     mPushStates;

        unsigned int            mPopStates;

        sf::RenderWindow        mWindow;
        sf::Clock               mFrameClock;

        GameConfig              mActiveConfig;
        ResourceManager         mResourceManager;
        InputManager            mInputManager;

        Arc::Logger             mLog;
    };
}