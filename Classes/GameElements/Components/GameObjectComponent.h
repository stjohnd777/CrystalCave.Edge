//
//  Component.hpp
//  DsjTemplate
//
//  Created by Daniel St. John on 10/11/15.
//
//
#pragma once

#include "cocos2d.h"
#include "MyMacros.h"
#include <sstream>

/*
 * The interface contract for Sprites adhering the component based model for behaviors applied to
 * the subject
 */
class GameObjectComponent {

public:

    GameObjectComponent(){};

    // The subject has this behavior
    //CC_SYNTHESIZE(cocos2d::Sprite*, m_GameObject, Subject)
    CC_SYNTHESIZE(cocos2d::Node*, m_Node, Subject);

    CC_SYNTHESIZE(std::string, m_Name, Name)

    // Called once int the life cycle of the object, here is the oportunity
    // to manange the one time initilization such as action based or create
    // a component based behavior on repeating action
    virtual void start(float dt) =0;

    // Ideally called once per frame through the sujects update method, but not necessarly
    // once per frame, but on the scheduler this priority queue
    virtual void update(float dt) =0;

    // stop the behavior
    virtual void stop(float dt) =0;

    // designed for one time of isoloated
    // behaviors
    virtual void executeOnce( ) {};

    // If the Component has start
    ATTR(bool, m_HasStart, HasStart, false)

    ATTR(bool, m_HasExuctueOnce, HasExuctueOnce, false)

    ATTR(bool, m_HasUpdate, HasUpdate, true)
    
    std::string toString(){

        std::stringstream ss;

        ss << "Nane:" << m_Name << std::endl;
        ss << "m_HasStart:" << m_HasStart << std::endl;
        ss << "m_HasExuctueOnce:" << m_HasExuctueOnce << std::endl;
        ss << "m_HasUpdate:" << m_HasUpdate << std::endl;
        ss << "m_HasExuctueOnce:" << m_HasExuctueOnce << std::endl;
        return ss.str();
        
    }
    
};
