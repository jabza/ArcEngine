////////////////////////////////////////////////////////////
// main.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Core/Engine.hpp"
#include "States/LoadState.hpp"

int main()
{
    Arc::Logger log("MainThread");
    log.l("Instantiating Engine...");

    try
    {
        Arc::Engine game;
        game.pushState(new LoadState(game.getContext()));
        game.run();
    }
    catch(std::exception& e)
    {
        std::cout << "\nFatal Exception: " << e.what() << std::endl;
        return -1;
    }

    log.l("Quit Cleanly.");

    return 0;
}