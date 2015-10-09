////////////////////////////////////////////////////////////
// ResourceManager.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <map>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Core/tinyxml2.hpp>
#include "Core/GameConfig.hpp"
#include "Core/Logger.hpp"

using namespace tinyxml2;

namespace Arc
{
	////////////////////////////////////////////////////////////
	/// \brief Stores and controls access to the engine resources.
	////////////////////////////////////////////////////////////
	class ResourceManager : public sf::NonCopyable
	{
	public:
		ResourceManager();
		~ResourceManager();

		sf::String                              getRootDirectory();

		GameConfig&                             getConfig(const sf::String& key);
		sf::String&                             getString(const sf::String& key);
		sf::Font&                               getFont(const sf::String& key);
		sf::Texture&                            getTexture(const sf::String& key);
		sf::SoundBuffer&                        getSound(const sf::String& key);
		sf::String&                             getMusic(const sf::String& key);

		void                                    loadConfig(const sf::String& key, GameConfig config);
		sf::String                              loadConfig(GameConfig config);

		void                                    loadString(const sf::String& key, sf::String string);
		sf::String                              loadString(sf::String string);

		void                                    loadFont(const sf::String& key, sf::String filename);
		sf::String                              loadFont(sf::String filename);

		void                                    loadTexture(const sf::String& key, sf::String filename);
		sf::String                              loadTexture(sf::String filename);

		void                                    loadSound(const sf::String& key, sf::String filename);
		sf::String                              loadSound(sf::String filename);

		void                                    loadMusic(const sf::String& key, sf::String filename);
		sf::String                              loadMusic(sf::String filename);

		bool                                    parse(const sf::String directory);

		static int                              resourceID;

	private:
		bool                                    parseConfig(XMLElement *pElement);
		bool                                    parseString(XMLElement *pElement);
		bool                                    parseFont(XMLElement *pElement);
		bool                                    parseTexture(XMLElement *pElement);
		bool                                    parseSound(XMLElement *pElement);
		bool                                    parseMusic(XMLElement *pElement);

		sf::String                              mRootDirectory;
		sf::String                              mFontPath;
		sf::String                              mStringPath;
		sf::String                              mTexturePath;
		sf::String                              mSoundPath;
		sf::String                              mMusicPath;

		std::map<sf::String, sf::String>        mStringContainer;
		std::map<sf::String, sf::Texture>       mTextureContainer;
		std::map<sf::String, sf::SoundBuffer>   mSoundContainer;
		std::map<sf::String, sf::String>        mMusicContainer;
		std::map<sf::String, sf::Font>          mFontContainer;
		std::map<sf::String, GameConfig>        mConfigContainer;

		Arc::Logger                             mLog;
	};
}