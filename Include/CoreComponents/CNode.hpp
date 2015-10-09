////////////////////////////////////////////////////////////
// CNode.hpp
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
#include <list>
#include "Core/Origin.hpp"

////////////////////////////////////////////////////////////
/// \brief Basic component that gives entities a transform
/// and position in the node graph.
////////////////////////////////////////////////////////////
class CNode
: public entityx::Component<CNode>
{
friend class NodeSystem;

public:
    ////////////////////////////////////////////////////////////
    /// \brief The types of tag.
    ////////////////////////////////////////////////////////////
    enum Tags
    {
        Scene,
        GUI,
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ////////////////////////////////////////////////////////////
                                    CNode(sf::Vector2f position = sf::Vector2f(0,0), Arc::Origin origin = Arc::Origin::NORTH_WEST);
                                    CNode(float x, float y, Arc::Origin origin = Arc::Origin::NORTH_WEST);
    
    ////////////////////////////////////////////////////////////
    /// \brief Default destructor.
    ////////////////////////////////////////////////////////////
                                    ~CNode();

    entityx::ComponentHandle<CNode> getRootNode();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the parent CNode component.
    /// \return parent's CNode.
    ////////////////////////////////////////////////////////////
    entityx::ComponentHandle<CNode> getParentNode();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the parent.
    /// \return parent entity.
    ////////////////////////////////////////////////////////////
    entityx::Entity                 getParent();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets a set of all the CNode's children.
    /// \return The CNode's children.
    ////////////////////////////////////////////////////////////
    std::set<entityx::Entity>       getChildren();
    
    ////////////////////////////////////////////////////////////
    /// \brief Checks if the CNode has a specific children.
    /// \return true if has child, false if not.
    ////////////////////////////////////////////////////////////   
    bool                            hasChild(entityx::Entity child);
    
    ////////////////////////////////////////////////////////////
    /// \brief Adds a child to the CNode.
    /// \param child The child entity, that contains a CNode.
    ////////////////////////////////////////////////////////////    
    void                            addChild(entityx::Entity child);
    
    ////////////////////////////////////////////////////////////
    /// \brief Removes a child from the CNode.
    /// \param The child to be removed.
    ////////////////////////////////////////////////////////////   
    void                            removeChild(entityx::Entity child);
    
    ////////////////////////////////////////////////////////////
    /// \brief Removes all children from the CNode.
    ////////////////////////////////////////////////////////////   
    void                            removeChildren();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the local sf::Transform of the CNode.
    /// \return The local sf::Transform.
    ////////////////////////////////////////////////////////////   
    sf::Transform                   getTransform();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the world sf::Transform of the CNode.
    /// \return The world sf::Transform.
    ////////////////////////////////////////////////////////////      
    sf::Transform                   getWorldTransform();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the local position of the CNode.
    /// \return The local position.
    ////////////////////////////////////////////////////////////   
    sf::Vector2f                    getPosition();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the world position of the CNode.
    /// \return The world position.
    ////////////////////////////////////////////////////////////       
    sf::Vector2f                    getWorldPosition();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the local rotation of the CNode.
    /// \return The local rotation.
    ////////////////////////////////////////////////////////////      
    float                           getRotation();
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the world rotation of the CNode.
    /// \return The world rotation.
    ////////////////////////////////////////////////////////////    
    float                           getWorldRotation();

    ////////////////////////////////////////////////////////////
    /// \brief Gets the world visibility of the CNode.
    /// \return The world visibility.
    ////////////////////////////////////////////////////////////
    bool                            getWorldVisibility();

    ////////////////////////////////////////////////////////////
    /// \brief Adds a tag to the CTag.
    /// \param tag The tag to be added.
    ////////////////////////////////////////////////////////////
    void                            addTag(Tags tag);

    ////////////////////////////////////////////////////////////
    /// \brief Removes a tag from the CTag.
    /// \param tag The tag to be removed.
    ////////////////////////////////////////////////////////////
    void                            removeTag(Tags tag);

    ////////////////////////////////////////////////////////////
    /// \brief Checks if the CTag contains a tag.
    /// \return The result.
    ////////////////////////////////////////////////////////////
    bool                            hasTag(Tags tag);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the entity to be culled.
    ////////////////////////////////////////////////////////////
    void                            cull();
    
    ////////////////////////////////////////////////////////////
    // Public Member data.
    ////////////////////////////////////////////////////////////
    sf::Transformable               transform;
    bool                            active, visible;
    Arc::Origin                     origin;

private:
    ////////////////////////////////////////////////////////////
    // Member data.
    ////////////////////////////////////////////////////////////
    entityx::Entity                 mParent;
    std::set<entityx::Entity>       mChildren, mAddChildren, mRemoveChildren;
    
    sf::Transform                   mWorldTransform;
    float                           mWorldRotation;

    std::set<Tags>                  mTags;

    bool                            mCull;
};