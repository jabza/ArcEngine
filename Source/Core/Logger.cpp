////////////////////////////////////////////////////////////
// Logger.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Core/Logger.hpp"

using namespace Arc;

int Logger::nextID = 0;

Logger::Logger(const sf::String logSource)
: mLogID(nextID++)
, mLogSource("LOGID: "+std::to_string(mLogID)+", SRC: "+logSource+", MSG: ")
{
}


void Logger::l(const sf::String& logMsg)
{
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<std::endl;
}


void Logger::l(const sf::String& logMsg, const sf::String& logVal)
{
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<logVal.toAnsiString()<<std::endl;
}


void Logger::l(const sf::String& logMsg, const std::exception& logVal)
{
    std::stringstream ss;
    ss << logVal.what();
    
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<ss.str()<<std::endl;
}


void Logger::l(const sf::String& logMsg, int logVal)
{
    std::stringstream ss;
    ss << logVal;
    
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<ss.str()<<std::endl;
}


void Logger::l(const sf::String& logMsg, double logVal)
{
    std::stringstream ss;
    ss << logVal;
    
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<ss.str()<<std::endl;
}


void Logger::l(const sf::String& logMsg, float logVal)
{
    std::stringstream ss;
    ss << logVal;
    
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<ss.str()<<std::endl;
}


void Logger::l(const sf::String& logMsg, bool logVal)
{
    std::stringstream ss;
    ss << logVal;
    
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<ss.str()<<std::endl;
}


void Logger::l(const sf::String& logMsg, const sf::Vector2f& logVal)
{
    std::stringstream ss;
    ss << "x: " << logVal.x;
    ss << ", y: " << logVal.y;
    
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<ss.str()<<std::endl;
}


void Logger::l(const sf::String& logMsg, const sf::Vector2i& logVal)
{
    std::stringstream ss;
    ss << "x: " << logVal.x;
    ss << ", y: " << logVal.y;
    
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<ss.str()<<std::endl;
}


void Logger::l(const sf::String& logMsg, const sf::FloatRect& logVal)
{
    std::stringstream ss;
    ss << "x: " << logVal.left;
    ss << ", y: " << logVal.top;
    ss << ", width: " << logVal.width;
    ss << ", height: " << logVal.height;
    
    std::cout<<mLogSource.toAnsiString()<<logMsg.toAnsiString()<<" - "<<ss.str()<<std::endl;
}