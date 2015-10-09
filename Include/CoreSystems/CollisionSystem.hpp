////////////////////////////////////////////////////////////
// CollisionSystem.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <list>
#include <map>
#include <entityx/entityx.h>
#include <SFML/Graphics/VertexArray.hpp>

#include "Core/Logger.hpp"
#include "Core/Context.hpp"

////////////////////////////////////////////////////////////
/// \brief Tests collision between all CCollider components.
////////////////////////////////////////////////////////////
class CollisionSystem
: public entityx::System<CollisionSystem>
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    /// \param context The game's Context.
    ////////////////////////////////////////////////////////////
                                    CollisionSystem(Arc::Context context);
                                    
    ////////////////////////////////////////////////////////////
    /// \brief Default destructor.
    ////////////////////////////////////////////////////////////
                                    ~CollisionSystem();
    
    ////////////////////////////////////////////////////////////
    /// \brief Updates the System.
    /// \param entities The EntityManager.
    /// \param events The EventManager.
    /// \param dt The delta time.
    ////////////////////////////////////////////////////////////
	void                            update(entityx::EntityManager& entities,
									entityx::EventManager& events, float dt) override;
    
    ////////////////////////////////////////////////////////////
    /// \brief Static function to check if a bounding box contains
    /// a point.
    /// \param aBounds The sf::VertexArray to check.
    /// \param point The point to test.
    /// \return The result of the collision.
    ////////////////////////////////////////////////////////////
    static bool                     contains(sf::VertexArray aBounds, sf::Vector2f point);
    
    ////////////////////////////////////////////////////////////
    /// \brief Static function to check if a bounding box intersects
    /// with another bounding box.
    /// \param aBounds The sf::VertexArray to check.
    /// \param bBounds The sf::VertexArray to check.
    /// \return The result of the collision.
    ////////////////////////////////////////////////////////////    
    static bool                     intersects(sf::VertexArray aBounds, sf::VertexArray bBounds);
    
    ////////////////////////////////////////////////////////////
    /// \brief Static function to get the axes of a sf::VertexArray.
    /// \param verts The sf::VertexArray to get axes from.
    /// \return The list of axes.
    ////////////////////////////////////////////////////////////       
    static std::list<sf::Vector2f>  getAxes(sf::VertexArray& verts);
    
    ////////////////////////////////////////////////////////////
    /// \brief Static function to get the projection of axis on
    /// sf::VertexArray.
    /// \param verts The sf::VertexArray to project.
    /// \param axis The axis to project.
    /// \return The resulting projection.
    ////////////////////////////////////////////////////////////         
    static sf::Vector2f             getProjection(sf::VertexArray& verts, sf::Vector2f& axis);

private:
    ////////////////////////////////////////////////////////////
    // Member data.
    ////////////////////////////////////////////////////////////
    Arc::Logger                     mLog;
    Arc::Context                    mContext;
    
    std::map<entityx::Entity,
    std::set<entityx::Entity>>      mTestedMap;
};
