//
//  GameObjectDescriptor.cpp
//  DsjTemplate
//
//  Created by Daniel St. John on 10/22/15.
//
//

#include "GameObjectDescriptor.h"
#include  "GameAssets.h"


GameObjectDescriptor::GameObjectDescriptor():
m_Identity("box"),
m_tag(-1),
m_Name("box"),
m_Png("box.green.64.64.png"),
m_IsFileBased(true),m_IsFrameBased(false),
m_IsUsingHealthLabel(false),m_IsUsingInfoLabel(false),
m_ScaleX(1),m_ScaleY(1),
m_HitSound(GameAssets::Sound::BELL),
m_DieSound(GameAssets::Sound::SHOTGUN),
m_Weight(100),m_Value(1000),m_MaxHealth(100),m_Health(100),
m_IsUsingPhysics(false),
m_IsDynamic(false),m_EffectedByGravity(false),
m_Mass(100),

m_CategoryBitmask(0xFFFFFFFF),
m_ContactTestBitmask(true),
m_CollisionBitmask(0xFFFFFFFF),

m_PhysicsBody(nullptr)
{
    
    m_TakeDamage = nullptr;
    m_Die        = nullptr;
    m_Attack     = nullptr;
}


GameObjectDescriptor::GameObjectDescriptor(
                     int tag,
                     std::string name,
                     std::string png,
                     bool isFileBased,
                     bool isUsingPhysics,
                     int prefabShapeType):
m_tag(tag),
m_Name(name),
m_Png(png),
m_IsFileBased(true),
m_IsFrameBased(false),
m_ScaleX( 1),
m_ScaleY (1),

m_Weight( 100),
m_Value( 1000),
m_MaxHealth( 100),
m_Health(100),

m_HitSound( GameAssets::Sound::BELL),
m_DieSound( GameAssets::Sound::SHOTGUN),

m_IsUsingPhysics( isUsingPhysics),
m_IsDynamic(true),m_EffectedByGravity(false),

m_Position(Point(0,0)),
m_Velocity( Vec2(0,0)),
m_Mass(100),
m_LinearDamping(0),

m_CategoryBitmask(0xFFFFFFFF),m_ContactTestBitmask(true),m_CollisionBitmask(0xFFFFFFFF),

m_PrefabShapeType (prefabShapeType),

m_PhysicsBody (nullptr)
{
    
}

GameObjectDescriptor::GameObjectDescriptor(std::string identity,
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
                     
                     Point position,
                     Vec2 velocity,
                     float mass,
                     float linearDamping,
                     
                     int categoryBitmask,
                     bool contactTestBitmask,
                     int collisionBitmask,
                     
                     int prefabShapeType,

                     PhysicsBody* physicsBody ):

m_tag(tag),
m_Name(name),
m_Png(png),
m_IsFileBased(isFileBased),
m_IsFrameBased(isFrameBased),
m_ScaleX( scaleX),
m_ScaleY (scaleY),

m_Weight( weight),
m_Value( value),
m_MaxHealth( maxHealth),
m_Health(health),

m_HitSound( hitSound),
m_DieSound( dieSound),

m_IsUsingPhysics( isUsingPhysics),
m_IsDynamic(isDynamic),

m_Position(position),
m_Velocity( velocity),
m_Mass(mass),
m_LinearDamping(linearDamping),

m_CategoryBitmask( categoryBitmask),
m_ContactTestBitmask( contactTestBitmask),
m_CollisionBitmask( collisionBitmask),

m_PrefabShapeType (prefabShapeType),
 
m_PhysicsBody (physicsBody)

{
    
}


void GameObjectDescriptor::addComponent(GameObjectComponent * c){
    m_Components.push_back(c);
}
