
#pragma once
#include <iostream>
#include <string>

//#include <stdio.h>
//#include "clips.h"


#include "cocos2d.h"

/**
 @brief Base object for all GameObject, both HOSTILE and FRIENDLY. 
 
 GameObject 
 
 1> has an identity
 2> has uuid
 3> has a State
 4> has a weight ( dammage it give an collision/interaction )
 5? has a value  ( value it gives on destructioon/interaction)
 
 GameObject
 1> references the player
 2> references the game layer
 
 1> can render them selves on to the GameScene
 getPosition
 */
class GameObject : public cocos2d::Sprite{

protected:
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32  )
    static pthread_mutex_t lock;
#endif
    
public:
    
    // Bounding Box Test: The shapes are not colliding if their bounding boxes are not overlapping.
    
    // Category Mask Test: The categories of each shape are bitwise ANDed against the
    // category mask of the other shape. If either result is 0, the shapes do not collide.
    CC_SYNTHESIZE(int, m_ChipmunkCategoryMask, ChipmunkCategoryMask);
    
    // Group Test: Shapes shouldn’t collide with other shapes in the same non-zero group.
    CC_SYNTHESIZE(int, m_ChipmunkGroup, ChipmunkGroup);
    
    
    
    char m_szInfo[256];
    CC_SYNTHESIZE(cocos2d::Label*, m_InfoLabel, InfoLabel);
    CC_SYNTHESIZE(bool, usesInfoLabel, UsesInfoLabel);
    void  useInfoLabel();
    
    enum State {
        SKIP     = -1,      // Skip processing this object, continue to next Game Object
                            // no question asked, just pass on it
        ON_DECK  =  0,      // Skip, leave resources intact, this GameObject will most likely
                            // be in play soon
        IN_PLAY  =  1,      // This object is in play, process it
        DEAD     = 99       // This object is dead, skip process,
                            // and some one in the chain may clean up it resources
    };
    
    enum ParticalEffects {
        EXPLOSION = 0,
        SMOKE,
        FIRE,
        GALAXY,
        FIREWORKS,
        METEOR,
        FLOWER,
        RAIN,
        SNOW,
        SPIRAL,
        SUN
    };
    
 
    GameObject();
    
    void  decrementHealth (int decrement);
    
    void  incrementHealth (int increment);
    
    
public: // references
    
    /**
     * The Game Layer
     */
    CC_SYNTHESIZE(cocos2d::Node*, m_GameLayer, GameLayer);
    /**
     * Player Game Object, Ship in Asteroids
     */
    CC_SYNTHESIZE(GameObject*, m_Player, Player);
    
    
public: // has a
    
    /**
     Unique integer for GameObject
     */
    CC_SYNTHESIZE(int, m_uuid, UUID);
    
    /**
     char string in human readable form describing the object
     identity, for example 'Asteroid'
     */
    CC_SYNTHESIZE(const char*, m_Identity, Identity);
    
    /**
     The damage the GameObject carries, for example small Asteroid
     gives 40% health damage of the player
     */
    CC_SYNTHESIZE(int, m_Weight, Weight); // TODO: rename Damage
                                          // Add another ivar for physics weigth
    
    /**
     The value the GameObject carries, for example the samll Asteroid
     is worth 750 point to the score when the player destroy it
     */
    CC_SYNTHESIZE(int, m_Value, Value);
    
    /**
     State
     */
    CC_SYNTHESIZE(State, m_Status, Status);
    

public: // Health management, and Health Lable Health Bar
    
    /** 
     The max point of health for object, for example boss
     spider max have 1000 point health and minion spider will have
     100 point, this is so object can take damange like a boss as
     ususl and the health bar above object will reflect the percenmtage 
     of remaining health
     */
    CC_SYNTHESIZE(int, m_MaxHealth, MaxHealth);
    
    /**
     The current object health
     */
    CC_SYNTHESIZE(int, m_Health, Health);
    
    
    /**
     Buffer for the health label associated with the GameObject
     */
    char m_szHealth[256];
    /**
     * displays health
     */
    CC_SYNTHESIZE(cocos2d::Label*, m_healthLabel, HealthLabel);
   
    
    /**
     If game object uses health label then this is true, otherwise 
     the health status bar on the object will not be displayed
     */
    CC_SYNTHESIZE(bool, m_usesHealthLabel, UsesHealthLabel);
    
    /**
     Helper method that sets up the health label, alloc and the
     lot
     */
    void   useHealthLabel();
    
    
    /**
     * update the health lable and the health bar
     * consider
     */
    void   updateLabels(float dt);
    

    /**
     Health bar needs to be scaled to the size og the object as not to
     be out of proportion, we calculate the textures width on for 
     this,clearly there are edge cases and they are ignorred since on small
     object it make little sence to display a health lable
     */
    CC_SYNTHESIZE(double, m_healthBarScale, HealthBarScale);
    /**
     Health bar Sprite and outliine for usual visual one expects for
     the objects health status bar
     */
    CC_SYNTHESIZE(cocos2d::Sprite*, m_healthBar, HealthBar);
    
    /**
     * The actual bar inside the hollow outline that indicates the 
     * GameObject health
     */
    CC_SYNTHESIZE(cocos2d::Sprite*, m_hollow,    HealthBarHollow);

    
    
public: // inherited functionality
    /**
     Object can explode, and ... here are convence methods for the effects
     */
    cocos2d::ParticleSystemQuad* randumParticalEffect(float scale,float duration);
    cocos2d::ParticleSystemQuad* explosion(float scale,float duration);
    cocos2d::ParticleSystemQuad* smoke(float scale,float duration);
    cocos2d::ParticleSystemQuad* fire(float scale,float duration);
    cocos2d::ParticleSystemQuad* galaxy(float scale,float duration);
    cocos2d::ParticleSystemQuad* fireworks(float scale,float duration);
    cocos2d::ParticleSystemQuad* meteor(float scale,float duration);
    cocos2d::ParticleSystemQuad* flower(float scale,float duration);
    cocos2d::ParticleSystemQuad* rain(float scale,float duration);
    cocos2d::ParticleSystemQuad* snow(float scale,float duration);
    cocos2d::ParticleSystemQuad* spiral(float scale,float duration);
    cocos2d::ParticleSystemQuad* sun(float scale,float duration);

    
   void animation(std::string name,bool isForEver = false);
    
    void animationSpriteSheet(
                   std::string name,
                   std::string animationSheet,
                   std::string plist,
                   std::string subject,
                   int length,
                   float dt,bool isForEver );
    
    void animationManual(
                   std::string name,
                   cocos2d::Vector<cocos2d::SpriteFrame*> v,
                   std::string plist,
                   std::string subject,
                   int length,
                   float dt,
                         bool isForEver );
    
    
    void explosion();
    
    void sparkel();
    
    
    void cleanUp(cocos2d::Node* sender);
    
    
/**
 * Physics and Collision section
 */
    
    CC_SYNTHESIZE(bool, m_IsUsingIndependentCollisionDetection, IsUsingIndependentCollisionDetection);
    
    CC_SYNTHESIZE(bool, m_IsUsingPhysics, IsUsingPhysics);
    
    CC_SYNTHESIZE(bool, m_IsUsingOnContact, IsUsingOnContact);
    
    ///////////////////////////////////////////////////////////////
    // TODO : oportunity to make this inherited functionality
    // not virtual
    // add another collisionHandelerMethod
    //////////////////////////////////////////////////////////////
    /**
     * use physics, this game object is or is not a
     * physical body ... this method is concrete, and typically
     * does to override this but may
     */
     virtual void usePhysics();
    
    /**
     * use the chipmunk physics engine for collision
     */
     virtual void useOnContact( ) ;
    
    /**
     * Physics engine notification of contact
     */
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact){};

   
    
    
public: // virtual section
    
    
    /**
     * Generic move object to point p in time dt in straigh line
     */
    virtual void move(cocos2d::Point p,float dt);
    
    /**
     * Take Damage
     */
    virtual void takeDamage(int weight) = 0;

protected:
    /**
     * injured behavior optional, like a limping ship, and
     * give default of nothing
     */
    virtual void injured() {};
    
    /**
     * Object do you death sequence
     */
    virtual void die() {};



    
    
public:
    
    /**
     clean up, harder then it sounds
     */
    virtual ~GameObject();
    
    
    
private :
    
    cocos2d::Map<std::string, cocos2d::Animation*> m_MapName2Animation;
    
};



