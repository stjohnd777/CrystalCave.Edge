//
//  GameObjectDescriptor.hpp
//  DsjTemplate
//
//  Created by Daniel St. John on 10/22/15.
//
//
#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

#include <sstream>

 
#include "GameObjectComponent.h"

using namespace cocos2d;


class GameObjectDescriptor {
    
public:
    
    
    GameObjectDescriptor();
    
    GameObjectDescriptor(
                         int tag,
                         std::string name,
                         std::string png,
                         bool isFileBased,
                         bool isUsingPhysics,
                         int preFabShapeType);
    
    GameObjectDescriptor(
                         std::string identity,
                         int tag,
                         std::string name,
                         std::string png,
                         bool isFileBased,
                         bool isFrameBased,
                         float scaleX,
                         float scaleY,
                         
                         int weight,
                         int value,
                         int maxHealth,
                         int health,
                         
                         std::string hitSound,
                         std::string dieSound,
                         
                         bool isUsingPhysics,
                         bool isDynamic,
                         
                         cocos2d::Point position,
                         Vec2 velocity,
                         float mass,
                         float linearDamping,
                     
                         int  categoryBitmask,
                         bool contactTestBitmask,
                         int collisionBitmask,
                         
                         int preFabShapeType = 0,
                         PhysicsBody* m_PhysicsBody= nullptr);

    
    void addComponent(GameObjectComponent * c);

    
    std::function<void()>  m_TakeDamage;
    std::function<void()>  m_Die;
    std::function<void()>  m_Attack;
    
    
private:
    
    CC_SYNTHESIZE (std::string, m_Identity, Identity);
    CC_SYNTHESIZE (int ,m_tag, Tag)
    CC_SYNTHESIZE (std::string , m_Name, Name);
    
    
    CC_SYNTHESIZE (std::string ,m_Png, Png);
    CC_SYNTHESIZE (bool , m_IsFileBased, IsFileBased);
    CC_SYNTHESIZE (bool , m_IsFrameBased, IsFrameBased);
    
    CC_SYNTHESIZE (bool , m_IsUsingHealthLabel, IsUsingHealthLabel);
    CC_SYNTHESIZE (bool , m_IsUsingInfoLabel, IsUsingInfoLabel);
    
    
    CC_SYNTHESIZE (float , m_ScaleX, ScaleX);
    CC_SYNTHESIZE (float , m_ScaleY, ScaleY);
    
    CC_SYNTHESIZE (int ,m_Weight, Weight);
    CC_SYNTHESIZE (int ,m_Value,  Value);
    
    CC_SYNTHESIZE (int , m_MaxHealth, MaxHealth);
    CC_SYNTHESIZE (int , m_Health, Health);
    
    CC_SYNTHESIZE (std::string ,m_HitSound, HitSound);
    CC_SYNTHESIZE (std::string ,m_DieSound, DieSound);
    
    CC_SYNTHESIZE(cocos2d::Point , m_Position, Position);
    CC_SYNTHESIZE(cocos2d::Vec2 ,  m_Velocity, Velocity);
    CC_SYNTHESIZE(bool,  m_IsUsingPhysics, IsUsingPhysics);
    CC_SYNTHESIZE(bool ,  m_IsDynamic, IsDynamic);
    CC_SYNTHESIZE(float , m_Mass, Mass);
    CC_SYNTHESIZE(bool , m_EffectedByGravity, EffectedByGravity);
    CC_SYNTHESIZE(float , m_LinearDamping, LinearDamping);
    
    
    CC_SYNTHESIZE(int , m_CategoryBitmask, CategoryBitmask);//0xFFFFFFFF
    CC_SYNTHESIZE(bool, m_ContactTestBitmask, ContactTestBitmask);// 0x00000000
    CC_SYNTHESIZE(int, m_CollisionBitmask, CollisionBitmask);// 0xFFFFFFFF
    
    CC_SYNTHESIZE (int , m_PrefabShapeType, PrefabShapeType);

    CC_SYNTHESIZE(PhysicsBody*, m_PhysicsBody, PhysicBody);

    
    CC_SYNTHESIZE(std::vector<GameObjectComponent*>, m_Components, Components);

public:

    std::string toString(){

        std::stringstream ss;

        ss << "Identity:" << m_Identity << std::endl;
        ss << "Tag:" << m_tag << std::endl;
        ss << "Name:" << m_Name << std::endl;
        ss << "Png:" << m_Png << std::endl;
        ss << "m_IsFileBased:" << m_IsFileBased << std::endl;
        ss << "m_IsFrameBased:" << m_IsFrameBased << std::endl;
        ss << "m_IsUsingInfoLabel:" << m_IsUsingInfoLabel << std::endl;
        ss << "m_IsUsingHealthLabel:" << m_IsUsingHealthLabel << std::endl;
        ss << "m_ScaleX:" << m_ScaleX << std::endl;
        ss << "m_ScaleY:" << m_ScaleY << std::endl;
        ss << "m_Weight:" << m_Weight << std::endl;
        ss << "m_Value:" << m_Value << std::endl;
        ss << "m_MaxHealth:" << m_MaxHealth << std::endl;
        ss << "m_Health:" << m_Health << std::endl;
        ss << "m_HitSound:" << m_HitSound << std::endl;
        ss << "m_DieSound:" << m_DieSound << std::endl;

        ss << "m_IsUsingPhysics:" << m_IsUsingPhysics << std::endl;
        ss << "m_IsDynamic:" << m_IsDynamic << std::endl;
        ss << "m_EffectedByGravity:" << m_EffectedByGravity << std::endl;
        ss << "m_Mass:" << m_Mass << std::endl;
        ss << "m_LinearDamping:" << m_LinearDamping << std::endl;

        ss << "m_CategoryBitmask:" << m_CategoryBitmask << std::endl;
        ss << "m_ContactTestBitmask:" << m_ContactTestBitmask << std::endl;
        ss << "m_Mass:" << m_Mass << std::endl;
        ss << "m_CollisionBitmask:" << m_CollisionBitmask << std::endl;

        ss << "m_PrefabShapeType:" << m_PrefabShapeType << std::endl;

        for( auto c : m_Components){
            ss << "m_Components:" << c << std::endl;
        }

        std::string str = ss.str();
        return str;

    }

    std::stringstream  toString(std::stringstream ss){

        ss << "Identity:" << m_Identity << std::endl;
        ss << "Tag:" << m_tag << std::endl;
        ss << "Name:" << m_Name << std::endl;
        ss << "Png:" << m_Png << std::endl;
        ss << "m_IsFileBased:" << m_IsFileBased << std::endl;
        ss << "m_IsFrameBased:" << m_IsFrameBased << std::endl;
        ss << "m_IsUsingInfoLabel:" << m_IsUsingInfoLabel << std::endl;
        ss << "m_IsUsingHealthLabel:" << m_IsUsingHealthLabel << std::endl;
        ss << "m_ScaleX:" << m_ScaleX << std::endl;
        ss << "m_ScaleY:" << m_ScaleY << std::endl;
        ss << "m_Weight:" << m_Weight << std::endl;
        ss << "m_Value:" << m_Value << std::endl;
        ss << "m_MaxHealth:" << m_MaxHealth << std::endl;
        ss << "m_Health:" << m_Health << std::endl;
        ss << "m_HitSound:" << m_HitSound << std::endl;
        ss << "m_DieSound:" << m_DieSound << std::endl;

        ss << "m_IsUsingPhysics:" << m_IsUsingPhysics << std::endl;
        ss << "m_IsDynamic:" << m_IsDynamic << std::endl;
        ss << "m_EffectedByGravity:" << m_EffectedByGravity << std::endl;
        ss << "m_Mass:" << m_Mass << std::endl;
        ss << "m_LinearDamping:" << m_LinearDamping << std::endl;

        ss << "m_CategoryBitmask:" << m_CategoryBitmask << std::endl;
        ss << "m_ContactTestBitmask:" << m_ContactTestBitmask << std::endl;
        ss << "m_Mass:" << m_Mass << std::endl;
        ss << "m_CollisionBitmask:" << m_CollisionBitmask << std::endl;

        ss << "m_PrefabShapeType:" << m_PrefabShapeType << std::endl;

        for( auto c : m_Components){
            ss << "m_Components:" << c << std::endl;
        }

        return ss;
        
    }
   
    
};