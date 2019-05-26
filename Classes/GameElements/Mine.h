#pragma once

#include <string>
#include "cocos2d.h"

#include "HostileObject.h"

#include "GameAssets.h"

class Mine : public HostileObject {

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
    
    CC_SYNTHESIZE(cocos2d::Point, spawnPoint, SpawnPoint);
    
    CC_SYNTHESIZE(cocos2d::Point, mineLocation, MineLocation);
    
    
    virtual void start();
    
    
    virtual void update(float dt) override;
    
    /**
     * Manual Collision Detection Rountine
     */
    void manualCollisionCheck(float dt);
    
    void manualWarningProximityCheck();
    
    void explodeMine();
    
    // defined virtual in GameObject
    virtual void takeDamage(int weight) override;
    
    // defined virtual in GameObject
    virtual void injured() override;
    
    /**
     * Add you self as physics body to the Physics Engine
     */
    virtual void usePhysics() override;
    
    
    /**
     * Add Contact listener to Chipmunck Engine
     */
    virtual void useOnContact() override;
    
    /**
     * Invoked by pyhsics engine on contact between colloiding object 
     * not bitmasked off in Chipmonk Engine
     */
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact) override;
    

    
public:
    
    void cleanUp();
    
    ~Mine();
    
private:
    

    
};
