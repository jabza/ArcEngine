////////////////////////////////////////////////////////////
// State.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Core Engine Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <entityx/deps/Dependencies.h>
#include "Core/ResourceManager.hpp"
#include "Core/InputManager.hpp"
#include "Core/Context.hpp"

using namespace entityx;

////////////////////////////////////////////////////////////
/// \brief The base State class, provides interfaces for
/// dervied States to implement custom updating and
/// rendering. Holds the game's Context.
////////////////////////////////////////////////////////////
class State : public sf::NonCopyable
{
public:
	typedef std::unique_ptr<State> Ptr;

    ////////////////////////////////////////////////////////////
    /// \brief Entity node layers.
    ////////////////////////////////////////////////////////////
    enum Layers
    {
        BACKGROUND = 0,
        MIDDLEGROUND,
        FOREGROUND,
        UI,
        TOTAL
    };

    
    ////////////////////////////////////////////////////////////
    /// \brief Default Constructor.
    /// \param context The game's Context.
    ////////////////////////////////////////////////////////////
                        State(Arc::Context context);
						virtual ~State() {};
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the State's sf::View camera.
    /// \return The State's camera.
    ////////////////////////////////////////////////////////////
    sf::View&           getCamera();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the State's EventManager.
    /// \return The State's EventManager.
    ////////////////////////////////////////////////////////////
    EventManager&       getEventManager();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the State's EntityManager.
    /// \return The State's EntityManager.
    ////////////////////////////////////////////////////////////
    EntityManager&      getEntityManager();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the State's SystemManager.
    /// \return The State's SystemManager.
    ////////////////////////////////////////////////////////////
    SystemManager&      getSystemManager();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets a layer entity.
    /// \param The layer to get.
    /// \return The layer root entity.
    ////////////////////////////////////////////////////////////
    entityx::Entity     getLayer(int layer);
    
    ////////////////////////////////////////////////////////////
    /// \brief Adds an entity to a layer node.
    /// \param layer The layer to add to.
    /// \param entity The entity to be added.
    ////////////////////////////////////////////////////////////
    void                addToLayer(int layer, entityx::Entity entity);
    
    ////////////////////////////////////////////////////////////
    /// \brief Performs any necessary operations before the State
    /// pauses.
    ////////////////////////////////////////////////////////////
    void                pause();
    
    ////////////////////////////////////////////////////////////
    /// \brief Performs any necessary operations before the State
    /// enters the main loop again.
    ////////////////////////////////////////////////////////////
    void                resume();

    ////////////////////////////////////////////////////////////
    /// \brief Handles a sf::RenderWindow sf::Event.
    /// \param delta The delta time since last frame.
    ////////////////////////////////////////////////////////////
    void                handleEvent(const sf::Event& event);
    
    ////////////////////////////////////////////////////////////
    /// \brief Updates the State.
    /// \param delta The delta time since last frame.
    ////////////////////////////////////////////////////////////
    void                update(const sf::Time& delta);
    
    ////////////////////////////////////////////////////////////
    /// \brief Renders the State's NodeGraph.
    /// \param pWindow Reference to the render window.
    ////////////////////////////////////////////////////////////
    void                draw(sf::RenderWindow& window);

protected:
    ////////////////////////////////////////////////////////////
    // Member data.
    ////////////////////////////////////////////////////////////
    Arc::Context        mContext;
    sf::View            mCamera;

    entityx::EntityX    mEntityx;

    std::vector<
    entityx::Entity>    mLayers;

	Arc::Logger         mLog;

private:
    ////////////////////////////////////////////////////////////
    /// \brief Optional event function implemented by
    /// dervived States.
    /// \param event The window event.
    ////////////////////////////////////////////////////////////
    virtual void        onHandleEvent(const sf::Event& event){};
    
    ////////////////////////////////////////////////////////////
    /// \brief Optional update function implemented by
    /// dervived States.
    /// \param delta The delta time.
    ////////////////////////////////////////////////////////////
    virtual void        onUpdate(const sf::Time& delta){};

    ////////////////////////////////////////////////////////////
    /// \brief Optional draw function implemented by
    /// dervived States.
    /// \param pWindow Reference to the render window.
    ////////////////////////////////////////////////////////////
    virtual void        onDraw(sf::RenderWindow& window){};

	////////////////////////////////////////////////////////////
	/// \brief Optional pause function implemented by
	/// dervived States.
	////////////////////////////////////////////////////////////
	virtual void        onPause(){};

    ////////////////////////////////////////////////////////////
    /// \brief Optional resume function implemented by
    /// dervived States.
    ////////////////////////////////////////////////////////////
	virtual void        onResume(){};
};
