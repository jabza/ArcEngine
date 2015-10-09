////////////////////////////////////////////////////////////
// InputManager.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <list>
#include <SFML/Graphics.hpp>
#include "Core/Logger.hpp"
#include "Core/Controls.hpp"

class Entity;

namespace Arc
{
	////////////////////////////////////////////////////////////
	/// \brief Maps player controls and parses sf::Events.
	////////////////////////////////////////////////////////////
	class InputManager : public sf::NonCopyable
	{
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor.
		////////////////////////////////////////////////////////////
										InputManager();

		////////////////////////////////////////////////////////////
		/// \brief Default destructor
		////////////////////////////////////////////////////////////                                   
										~InputManager();

		////////////////////////////////////////////////////////////
		/// \brief Handles a sf::RenderWindow sf::Event.
		/// \param event Reference to window event.
		////////////////////////////////////////////////////////////
		void                            handleEvent(const sf::Event& event);

		void                            clearTriggered();

		////////////////////////////////////////////////////////////
		/// \brief Checks if the sf::RenderWindow is in focus.
		/// \return If in focus.
		//////////////////////////////////////////////////////////// 
		const bool                      hasFocus() const;

		////////////////////////////////////////////////////////////
		/// \brief Checks if the mouse is inside the sf::RenderWindow.
		/// \return If mouse inside.
		//////////////////////////////////////////////////////////// 
		const bool                      hasMouse() const;

		////////////////////////////////////////////////////////////
		/// \brief Maps a sf::Key to a Control.
		/// \param key The sf::Key.
		/// \param ctrl The Control.
		//////////////////////////////////////////////////////////// 
		void                            mapKey(sf::Keyboard::Key key, Arc::Controls ctrl);

		////////////////////////////////////////////////////////////
		/// \brief Maps a sf::Button to a Control.
		/// \param button The sf::Button.
		/// \param ctrl The Control.
		//////////////////////////////////////////////////////////// 
		void                            mapButton(sf::Mouse::Button button, Arc::Controls ctrl);

		////////////////////////////////////////////////////////////
		/// \brief Gets the keys associated with the given Control.
		/// \param ctrl The Control.
		/// \return The list of bound sf::Keys.
		//////////////////////////////////////////////////////////// 
		std::list<sf::Keyboard::Key>    getKeys(Arc::Controls ctrl);

		////////////////////////////////////////////////////////////
		/// \brief Gets the buttons associated with the given Control.
		/// \param ctrl The Control.
		/// \return The list of bound sf::Buttons.
		//////////////////////////////////////////////////////////// 
		std::list<sf::Mouse::Button>    getButtons(Arc::Controls ctrl);

		////////////////////////////////////////////////////////////
		/// \brief Gets the Control associated with the sf::Key.
		/// \param key The sf::Key.
		/// \return The bound Control.
		//////////////////////////////////////////////////////////// 
		Arc::Controls                   getControl(sf::Keyboard::Key key);

		////////////////////////////////////////////////////////////
		/// \brief Gets the Control associated with the sf::Button.
		/// \param key The sf::Button.
		/// \return The bound Control.
		////////////////////////////////////////////////////////////
		Arc::Controls                   getControl(sf::Mouse::Button btn);


		////////////////////////////////////////////////////////////
		/// \brief Checks if the Control is pressed.
		/// \param ctrl The Control.
		/// \return If the Control is pressed.
		//////////////////////////////////////////////////////////// 
		bool                            isPressed(Arc::Controls ctrl);

		////////////////////////////////////////////////////////////
		/// \brief Checks if the Control is triggered.
		/// \param ctrl The Control.
		/// \return If the Control is triggered.
		//////////////////////////////////////////////////////////// 
		bool                            wasTriggered(Arc::Controls ctrl);

		////////////////////////////////////////////////////////////
		/// \brief Gets the current mouse position relative to the 
		/// sf::RenderWindow.
		/// \return The mouse position.
		//////////////////////////////////////////////////////////// 
		sf::Vector2f                    getMousePos();

	private:
		////////////////////////////////////////////////////////////
		// Member data.
		////////////////////////////////////////////////////////////
		bool                                        mHasFocus;
		bool                                        mHasMouse;

		std::map<sf::Keyboard::Key, Arc::Controls>  mKeyBindings;
		std::map<sf::Mouse::Button, Arc::Controls>  mButtonBindings;

		sf::Vector2f                                mLocalMousePosition;

		std::map<Arc::Controls, bool>               mTriggered;
		Arc::Logger                                 mLog;
	};
}