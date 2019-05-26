#pragma once

#include <string>
#include <vector>
#include "cocos2d.h"
#include "GameObject.h"

class LunarModule : public GameObject {
    
public:
    static const int TAG;
    static const int WEIGHT;
    static const int HEALTH;
    
    static const float MASS;
    static const float MAX_THRUST;
    
    static const std::string THRUST_SOUND;
    static const std::string LAND_SOUND;
    static const std::string HIT_SOUND;
    static const std::string DIE_SOUND;
    
    static const std::string PNG;

    static LunarModule* getInstance(){
        assert(INSTANCE);
        return INSTANCE;
    }
    static LunarModule* INSTANCE;

public:
    
    CREATE_FUNC(LunarModule);
    
    bool init() override;

public:
    
    void update(float dt) override;

    unsigned int  soundId;
public:
    
    void thrushOff();

    int maxThrust;
    
    /**
     * 0 point up unit (0,1)
     */
    int angleDegree = 0;
    
    int percentageThrust = 100;

    void applyThrush(cocos2d::Vec2 force, float percentage);

    void applyTourque(float t ){
        
        angleDegree = angleDegree + t* 10;
        
        runAction (cocos2d::RotateBy::create(.1,t*10));
    }
    
    /**
     * Generic move object to point p in time dt in straigh line
     */
    virtual void move(cocos2d::Point p,float dt) override;
    
    /**
     * Take Damage
     */
    virtual void takeDamage(int weight) override;
    
    /**
     * injured behavior optional, like a limping ship, and
     * give default of nothing
     */
    virtual void injured() override;
    
    /**
     * Object do you death sequence
     */
    virtual void die() override;
    
public:
    
    cocos2d::Vector<cocos2d::SpriteFrame*> vectorSpriteFrames ;
    /**
     * uses Physics engine
     */
    void usePhysics() override;
    /**
     * uses Physics engine collision
     */
    void useOnContact() override;
    /**
     * Physics engine notification of contact
     */
    bool onContactBegin(cocos2d::PhysicsContact& contact) ;
};
