////////////////////////////////////////////////////////////
// RenderSystem.cpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CoreSystems/RenderSystem.hpp"
#include "CoreComponents/CNode.hpp"
#include "CoreComponents/CRenderSprite.hpp"
#include "CoreComponents/CRenderVerts.hpp"
#include "CoreComponents/CRenderRect.hpp"
#include "CoreComponents/CRenderCirc.hpp"
#include "CoreComponents/CRenderText.hpp"
#include "CoreComponents/CRenderShader.hpp"
#include "Core/Engine.hpp"


RenderSystem::RenderSystem(Arc::Context context)
: mLog("RenderSystem")
, mContext(context)
{
    mLog.l("System created!");
}


RenderSystem::~RenderSystem()
{
    mLog.l("System destroyed!");
}


void RenderSystem::setRenderRoot(entityx::Entity root)
{
    if(root.valid())
    {
        if(root.component<CNode>())
            mRenderRoot = root;
    }
}


void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, float dt)
{
    if(mRenderRoot.valid())
    {
        if(mRenderRoot.component<CNode>())
        {
            sf::RenderStates worldStates = sf::RenderStates::Default;
            renderEntity(mRenderRoot, worldStates);
        }
    }
}


void RenderSystem::renderEntity(entityx::Entity entity, sf::RenderStates worldStates)
{
    auto node = entity.component<CNode>();
    
    if(node->visible)
    {
        sf::RenderTarget *renderTarget = mContext.window;
        worldStates.transform = node->getWorldTransform();
        
        if(entity.component<CRenderShader>())
            worldStates.shader = &entity.component<CRenderShader>()->shader;
            
        if(entity.component<CRenderVerts>())
        {
            auto renderVerts = entity.component<CRenderVerts>();
            worldStates.texture = &mContext.resources->getTexture(renderVerts->textureID);
            renderTarget->draw(renderVerts->vertexArray, worldStates);
        }
        
        if(entity.component<CRenderRect>())
            renderTarget->draw(entity.component<CRenderRect>()->rectangleShape, worldStates);
            
        if(entity.component<CRenderCirc>())
            renderTarget->draw(entity.component<CRenderCirc>()->circleShape, worldStates);
        
        if(entity.component<CRenderSprite>())
            renderTarget->draw(entity.component<CRenderSprite>()->sprite, worldStates);
        
        if(entity.component<CRenderText>())
            renderTarget->draw(entity.component<CRenderText>()->text, worldStates);
        
        for(entityx::Entity child : node->getChildren())
        {
            if(child.valid())
            {
                if(child.component<CNode>())
                    renderEntity(child, worldStates);
            }
        }
    }
}
