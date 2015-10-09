////////////////////////////////////////////////////////////
// Logger.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>

////////////////////////////////////////////////////////////
/// \brief Helper class for logging messages.
////////////////////////////////////////////////////////////
namespace Arc
{
    class Logger
    {
    public:
        static int  nextID;

                    Logger(const sf::String logSource = "");

        void        l(const sf::String &logMsg);
        void        l(const sf::String &logMsg, const sf::String &logVal);
        void        l(const sf::String &logMsg, const std::exception &logVal);
        void        l(const sf::String &logMsg, int logVal);
        void        l(const sf::String &logMsg, double logVal);
        void        l(const sf::String &logMsg, float logVal);
        void        l(const sf::String &logMsg, bool logVal);
        void        l(const sf::String &logMsg, const sf::Vector2f &logVal);
        void        l(const sf::String &logMsg, const sf::Vector2i &logVal);
        void        l(const sf::String &logMsg, const sf::FloatRect &logVal);

        template<class T>
        void        l(const sf::String &logMsg, const std::set<T> &logVals)
        {
            std::cout << mLogSource.toAnsiString() << logMsg.toAnsiString() << ":" << std::endl;
            for(auto &val : logVals)
            {
                std::stringstream ss;
                ss << val;
                std::cout << ss.str() << std::endl;
            }
        }

    private:
        int         mLogID;
        sf::String  mLogSource;
    };
}
