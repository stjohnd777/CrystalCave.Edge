#pragma once

#include <string>
#include "cocos2d.h"
#include "GameObject.h"
#include "TargetObject.h"

#include "Constants.h"

class Mine : public TargetObject {

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32  )
    static pthread_mutex_t lock;
#endif
    
    
public:
    static const std::string IDENTITY;
    static const int TAG;
    static const int MAX_HEALTH;
    static const int WEIGTH;
    static const float MASS;
    static const std::string PNG;
    static const std::string SND_EXPLODE;
    
    // preprocessor macro for "static create()"
    CREATE_FUNC(Mine);
    
    bool  init() override;

    static Mine* create(
        cocos2d::Point spawnPoint,
        cocos2d::Point mineLocation,
        bool isUsingPhysics = false,
        bool isUsingOnContact = false,
        bool isStationary = true);
    

public:
    
    
    /**
     * If a collision or proxiimity is broken then ...
     */
    void collisionOccured();
    
    void explodeMine();
    
    CC_SYNTHESIZE(bool, m_IsStationary, IsStationary);
    
    CC_SYNTHESIZE(cocos2d::Point, spawnPoint, SpawnPoint);
    
    CC_SYNTHESIZE(cocos2d::Point, mineLocation, MineLocation);
    

public:
    
    // defined virtual in GameObject
    virtual void takeDamage(int weight) ;
    
    // defined virtual in GameObject
    virtual void injured();
    
    virtual void die();

    virtual void warn();

    // defined virtual in GameObject
    virtual void move(cocos2d::Point p,float dt){
        this->runAction( cocos2d::MoveTo::create(dt, p) );
    }
    
    
public:
    
    /**
     * Add you self as physics body to the Physics Engine
     */
    virtual void usePhysics();
    
    
    /**
     * Add Contact listener to Chipmunck Engine
     */
    virtual void useOnContact();
    
    /**
     * Invoked by pyhsics engine on contact between colloiding object 
     * not bitmasked off in Chipmonk Engine
     */
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    /**
     * Manual Collision Detection Rountine
     */
    void collision(float dt);

public:
    
    virtual void update(float dt) override;
    
    virtual void start();
    
public:
    
    void cleanUp();
    
    ~Mine();
    
private:
    

    
};
