////////////////////////////////////////////////////////////
// ResourceManager.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Core/ResourceManager.hpp"

#ifdef OSX
#import <Foundation/Foundation.h>
#endif

using namespace Arc;

int ResourceManager::resourceID = 0;

ResourceManager::ResourceManager()
: mRootDirectory("assets/")
, mFontPath("fonts/")
, mStringPath("strings/")
, mTexturePath("textures/")
, mSoundPath("sounds/")
, mMusicPath("music/")
, mLog("ResourceManager")
{
#ifdef OSX
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    sf::String packagePath;
    NSBundle* bundle = [NSBundle mainBundle];
    
    if(bundle != nil)
    {
        NSString* path = [bundle resourcePath];
        packagePath = [path UTF8String] + sf::String("/");
    }
    [pool drain];
    
    mRootDirectory = packagePath + mRootDirectory;
#endif
}


ResourceManager::~ResourceManager()
{
}


sf::String ResourceManager::getRootDirectory()
{
    return mRootDirectory;
}


/**
 * @brief Gets a GameConfig.
 * @param key The key of the GameConfig.
 * @return The GameConfig.
 */
GameConfig& ResourceManager::getConfig(const sf::String& key)
{
    try
    {
        return mConfigContainer.at(key);
    } 
    catch(std::exception& e)
    {
        throw std::runtime_error("Could not get GameConfig: " + key + ", " + e.what());
    }
}


/**
 * @brief Gets a String.
 * @param key The key of the String.
 * @return The String.
 */
sf::String& ResourceManager::getString(const sf::String& key)
{
    try
    {
        return mStringContainer.at(key);
    } 
    catch(std::exception& e)
    {
        throw std::runtime_error("Could not get String: " + key + " - " + e.what());
    }
}


/**
 * @brief Gets a Font.
 * @param key The key of the Font.
 * @return The Font.
 */
sf::Font& ResourceManager::getFont(const sf::String& key)
{
    try
    {
        return mFontContainer.at(key);
    } 
    catch(std::exception& e)
    {
        throw std::runtime_error("Could not get Font: " + key + " - " + e.what());
    }
}


/**
 * @brief Gets a Texture.
 * @param key The key of the Texture.
 * @return The Texture.
 */
sf::Texture& ResourceManager::getTexture(const sf::String& key)
{
    try
    {
        return mTextureContainer.at(key);
    } 
    catch(std::exception& e)
    {
        mLog.l("Could not get Texture: " + key + " - " + e.what());
        return mTextureContainer.at("Default");
    }
}


/**
* @brief Gets the path to a music file.
* @param key The key of the Music.
* @return The full path to music.
*/
sf::String& ResourceManager::getMusic(const sf::String& key)
{
    try
    {
        return mMusicContainer.at(key);
    }
    catch(std::exception& e)
    {
        throw std::runtime_error("Could not get Music: " + key + " - " + e.what());
    }
}


/**
 * @brief Gets a SoundBuffer.
 * @param key The key of the SoundBuffer.
 * @return The SoundBuffer.
 */
sf::SoundBuffer& ResourceManager::getSound(const sf::String& key)
{
    try
    {
        return mSoundContainer.at(key);
    } 
    catch(std::exception& e)
    {
        throw std::runtime_error("Could not get Sound: " + key + " - " + e.what());
    }
}


void ResourceManager::loadConfig(const sf::String& key, GameConfig config)
{
    mConfigContainer.emplace(key, config);
    mLog.l("Loaded Config", key);
}


sf::String ResourceManager::loadConfig(GameConfig config)
{
    resourceID++;
    
    mConfigContainer.emplace(std::to_string(resourceID), config);
    mLog.l("Loaded Config with auto key", std::to_string(resourceID));
    
    return std::to_string(resourceID);
}


/**
 * @brief Loads a String.
 * @param key The key of the String.
 * @param string The String value to be loaded.
 */
void ResourceManager::loadString(const sf::String& key, sf::String string)
{
    mStringContainer.emplace(key, string);
    mStringContainer[key] = string;
    mLog.l("Loaded String", key);
}

/**
 * @brief Loads a String, auto generating a key.
 * @param string The String value to be loaded.
 * @return The key.
 */
sf::String ResourceManager::loadString(sf::String string)
{
    resourceID++;
    
    mStringContainer.emplace(std::to_string(resourceID), string);
    mLog.l("Loaded String with auto key", std::to_string(resourceID));
    
    return std::to_string(resourceID);
}


/**
 * @brief Loads a Font.
 * @param key The key of the Font.
 * @param filename The Font filename to be loaded.
 */
void ResourceManager::loadFont(const sf::String& key, sf::String filename)
{
    auto font = mFontContainer.insert(std::pair<sf::String, sf::Font>(key, sf::Font()));
    if(font.second)
    {
        if(font.first->second.loadFromFile(filename))
            mLog.l("Loaded Font", key);
        else
            throw std::runtime_error("Could not load Font: " + filename);
    }
    else
        mLog.l("Font already loaded", key);
}


/**
 * @brief Loads a Font.
 * @param filename The Font filename to be loaded.
 * @return The key.
 */
sf::String ResourceManager::loadFont(sf::String filename)
{
    resourceID++;
    
    auto font = mFontContainer.insert(std::pair<sf::String, sf::Font>(std::to_string(resourceID), sf::Font()));
    if(font.second)
    {
        if(font.first->second.loadFromFile(filename))
            mLog.l("Loaded Font with auto key", std::to_string(resourceID));
        else
            throw std::runtime_error("Could not load Font: " + filename);
    }
    else
        mLog.l("Font already loaded", std::to_string(resourceID));
        
    return std::to_string(resourceID);
}



/**
 * @brief Loads a Texture.
 * @param key The key of the Texture
 * @param filename The Texture filename to be loaded.
 */
void ResourceManager::loadTexture(const sf::String& key, sf::String filename)
{
    auto texture = mTextureContainer.insert(std::pair<sf::String, sf::Texture>(key, sf::Texture()));
    if(texture.second)
    {
        if(texture.first->second.loadFromFile(filename))
            mLog.l("Loaded Texture", key);
        else
        {
            mTextureContainer.erase(texture.first);
            mLog.l("Could not load Texture: " + filename);
        }
    }
    else
        mLog.l("Texture already loaded", key);
}


/**
 * @brief Loads a Texture.
 * @param filename The Texture filename to be loaded.
 * @return The key.
 */
sf::String ResourceManager::loadTexture(sf::String filename)
{
    resourceID++;
    
    auto texture = mTextureContainer.insert(std::pair<sf::String, sf::Texture>(std::to_string(resourceID), sf::Texture()));
    if(texture.second)
    {
        if(texture.first->second.loadFromFile(filename))
            mLog.l("Loaded Texture with auto key", std::to_string(resourceID));
        else
        {
            mTextureContainer.erase(texture.first);
            mLog.l("Could not load Texture: " + filename);
        }
    }
    else
        mLog.l("Texture already loaded", std::to_string(resourceID));
        
    return std::to_string(resourceID);
}


/**
 * @brief Loads a SoundBuffer.
 * @param key The key of the SoundBuffer.
 * @param filename The SoundBuffer filename to be loaded.
 */
void ResourceManager::loadSound(const sf::String& key, sf::String filename)
{
    auto sound = mSoundContainer.insert(std::pair<sf::String, sf::SoundBuffer>(key, sf::SoundBuffer()));
    if(sound.second)
    {
        if(sound.first->second.loadFromFile(filename))
            mLog.l("Loaded Sound", key);
        else
            throw std::runtime_error("Could not load Sound: " + filename);
    }
    else
        mLog.l("Sound already loaded", key);
}

/**
 * @brief Loads a SoundBuffer.
 * @param filename The SoundBuffer filename to be loaded.
 * @return The key.
 */
sf::String ResourceManager::loadSound(sf::String filename)
{
    resourceID++;
    
    auto sound = mSoundContainer.insert(std::pair<sf::String, sf::SoundBuffer>(std::to_string(resourceID), sf::SoundBuffer()));
    if(sound.second)
    {
        if(sound.first->second.loadFromFile(filename))
            mLog.l("Loaded Sound with auto key", std::to_string(resourceID));
        else
            throw std::runtime_error("Could not load Sound: " + filename);
    }
    else
        mLog.l("Sound already loaded", std::to_string(resourceID));
        
    return std::to_string(resourceID);
}


void ResourceManager::loadMusic(const sf::String& key, sf::String filename)
{
    auto music = mMusicContainer.insert(std::pair<sf::String, sf::String>(key, filename));
    if(music.second)
        mLog.l("Loaded Music", key);
    else
        mLog.l("Music already loaded", key);
}


bool ResourceManager::parse(const sf::String directory)
{
    sf::String path = mRootDirectory+directory;
    
    XMLDocument resourceDocument;
    
    if(resourceDocument.LoadFile(path.toAnsiString().data()) == 0)
    {
        XMLElement *pElement = resourceDocument.FirstChildElement();

        while(pElement)
        {
            if(pElement->Name() != NULL && pElement->Attribute("id") != NULL)
            {
                sf::String tag = pElement->Name();
                
                if(tag == "CONFIG")
                    parseConfig(pElement);
                else if(tag == "STRING")
                    parseString(pElement);
                else if(tag == "FONT")
                    parseFont(pElement);
                else if(tag == "TEXTURE")
                    parseTexture(pElement);
                else if(tag == "SOUND")
                    parseSound(pElement);
                else if(tag == "MUSIC")
                    parseMusic(pElement);
            }
            pElement = pElement->NextSiblingElement();
        }
    }
    else
        return false;
    
    return true;
}


bool ResourceManager::parseConfig(XMLElement *pElement)
{
    sf::String alias = pElement->Attribute("id");
    
    if(sf::String(pElement->Name()) == "CONFIG")
    {
        GameConfig config;
        
        if(pElement->Attribute("title") != NULL)
            config.setWinTitle(pElement->Attribute("title"));
        else
            mLog.l("XML Error parsing Config 'title'.");
            
        if(pElement->Attribute("lang") != NULL)
        {
            sf::String lang = pElement->Attribute("lang");
            if(lang == "en")
                config.setLanguage(GameConfig::Language::English);
            else
                config.setLanguage(GameConfig::Language::English);
        }
        else
            mLog.l("XML Error parsing Config 'language'.");
            
        if(pElement->IntAttribute("width") && pElement->IntAttribute("height"))
            config.setVidMode(sf::VideoMode(pElement->IntAttribute("width"), pElement->IntAttribute("height"), 32));
        else
            mLog.l("XML Error parsing Config 'window dimensions'.");

        int style = config.getWinStyle();

        if(pElement->BoolAttribute("fullscreen"))
            style |= sf::Style::Fullscreen;
        if(pElement->BoolAttribute("resize"))
            style |= sf::Style::Resize;

        config.setWinStyle(style);
        
        loadConfig(alias, config);

        return true;
    }
    
    mLog.l("Failed to load Config", alias);
    return false;
}


bool ResourceManager::parseString(XMLElement *pElement)
{
    sf::String alias = pElement->Attribute("id");
    
    if(sf::String(pElement->Name()) == "STRING" && pElement->GetText() != NULL)
    {
        sf::String text(pElement->GetText());
        loadString(alias, text);
        return true;
    }
    
    mLog.l("Failed to load String", alias);
    return false;
}


bool ResourceManager::parseFont(XMLElement *pElement)
{
    sf::String alias = pElement->Attribute("id");
    
    if(sf::String(pElement->Name()) == "FONT" && pElement->GetText() != NULL)
    {
        sf::String fontDir = pElement->GetText();
        
        loadFont(alias, mRootDirectory+mFontPath+fontDir);
        return true;
    }
    
    mLog.l("Failed to load Font", alias);
    return false;
}


bool ResourceManager::parseTexture(XMLElement *pElement)
{
    sf::String alias = pElement->Attribute("id");
    
    if(sf::String(pElement->Name()) == "TEXTURE" && pElement->GetText() != NULL)
    {
        sf::String textureDir = pElement->GetText();
        loadTexture(alias, mRootDirectory+mTexturePath+textureDir);
        
        bool tiled = false;
        pElement->QueryBoolAttribute("isTile", &tiled);
        getTexture(alias).setRepeated(tiled);
        
        return true;
    }
    
    mLog.l("Failed to load Texture", alias);
    return false;
}


bool ResourceManager::parseSound(XMLElement *pElement)
{
    sf::String alias = pElement->Attribute("id");
    
    if(sf::String(pElement->Name()) == "SOUND" && pElement->GetText() != NULL)
    {
        sf::String soundDir = pElement->GetText();
        loadSound(alias, mRootDirectory+mSoundPath+soundDir);
        return true;
    } 

    mLog.l("Failed to load Sound", alias);
    return false;
}


bool ResourceManager::parseMusic(XMLElement *pElement)
{
    sf::String alias = pElement->Attribute("id");

    if(sf::String(pElement->Name()) == "MUSIC" && pElement->GetText() != NULL)
    {
        sf::String soundDir = pElement->GetText();
        loadMusic(alias, mRootDirectory+mMusicPath+soundDir);
        return true;
    }

    mLog.l("Failed to load Music", alias);
    return false;
}