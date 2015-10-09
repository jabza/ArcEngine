////////////////////////////////////////////////////////////
// CCollider.hpp
//
// Created by Thomas Kilsby on 06/04/2014.
// Copyright (c) 2014 Thomas Kilsby. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include <set>

////////////////////////////////////////////////////////////
/// \brief Represents a bounding box for collision testing.
////////////////////////////////////////////////////////////
class CCollider
: public entityx::Component<CCollider>
{
friend class CollisionSystem;
public:
    ////////////////////////////////////////////////////////////
    /// \brief FloatRect constructor.
    /// \param alignedBounds The sf::FloatRect to construct the
    /// bounding box from.
    ////////////////////////////////////////////////////////////
                                CCollider(sf::FloatRect alignedBounds);
                                
    ////////////////////////////////////////////////////////////
    /// \brief Vertex constructor.
    /// \param vertices The sf::VertexArray to construct the
    /// bounding box from.
    ////////////////////////////////////////////////////////////
                                CCollider(sf::VertexArray vertices);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the bounds based on a sf::FloatRect.
    /// \param alignedBounds The sf::FloatRect to construct the
    /// bounding box from.
    ////////////////////////////////////////////////////////////                                
    void                        setBounds(sf::FloatRect alignedBounds);
    
    ////////////////////////////////////////////////////////////
    /// \brief Sets the bounds based on a sf::VertexArray.
    /// \param vertices The sf::VertexArray to construct the
    /// bounding box from.
    ////////////////////////////////////////////////////////////     
    void                        setBounds(sf::VertexArray vertices);
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the size of the bounding box.
    /// \return The box size.
    ////////////////////////////////////////////////////////////
    sf::Vector2f                getSize();

    ////////////////////////////////////////////////////////////
    /// \brief Gets the aligned bounding box.
    /// \return The aligned bounding box.
    ////////////////////////////////////////////////////////////    
    sf::FloatRect               getAlignedBounds();

    ////////////////////////////////////////////////////////////
    /// \brief Gets the resulting aligned bounding box, 
    /// transformed by a sf::Transform.
    /// \return The aligned bounding box.
    ////////////////////////////////////////////////////////////    
    sf::FloatRect               getAlignedBounds(sf::Transform transform);

    ////////////////////////////////////////////////////////////
    /// \brief Gets the sf::VertexArray of the bounding box.
    /// \return The sf::VertexArray.
    ////////////////////////////////////////////////////////////    
    sf::VertexArray             getVerts();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the sf::VertexArray of the bounding box,
    /// transformed by a sf::Transform.
    /// \return The sf::VertexArray.
    ////////////////////////////////////////////////////////////    
    sf::VertexArray             getVerts(sf::Transform transform);
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the set of entity ids the component is
    /// currently colliding with.
    /// \return The set of colliders.
    ////////////////////////////////////////////////////////////    
    std::set<entityx::Entity>   colliders;
    
private:
    ////////////////////////////////////////////////////////////
    // Member data.
    ////////////////////////////////////////////////////////////
    sf::VertexArray             mVertices;

};
