////////////////////////////////////////////////////////////
// ShaderSystem.cpp
//
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreSystems/ShaderSystem.hpp"
#include "CoreComponents/CNode.hpp"
#include "CoreComponents/CRenderShader.hpp"


ShaderSystem::ShaderSystem()
: mLog("ShaderSystem")
{
    mLog.l("System Created!");
}


ShaderSystem::~ShaderSystem()
{
    mLog.l("System Destroyed!");
}


void ShaderSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, float dt)
{
    for(auto e : entities.entities_with_components<CRenderShader>())
    {
        auto shader = e.component<CRenderShader>();
        shader->time += sf::seconds(dt);
        shader->onShade(entities, shader->shader, shader->time);
    }    
} 