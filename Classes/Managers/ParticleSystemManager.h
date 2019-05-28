#pragma once

#include "cocos2d.h"

using namespace cocos2d;

/**
 * The term particle system refers to a computer graphics technique that uses a large number of very 
 * small sprites or other graphic objects to simulate certain kinds of “fuzzy” phenomena, which are 
 * otherwise very hard to reproduce with conventional rendering techniques - usually highly chaotic systems, 
 * natural phenomena, and/or processes caused by chemical reactions.
 
 cocos2d-x comes with some predefined particles that can be customized in runtime. List of predefined particles:

 ParticleFire:      Point particle system. Uses Gravity mode.
 ParticleFireworks: Point particle system. Uses Gravity mode.
 ParticleSun:       Point particle system. Uses Gravity mode.
 ParticleGalaxy:    Point particle system. Uses Gravity mode.
 ParticleFlower:    Point particle system. Uses Gravity mode.
 ParticleMeteor:    Point particle system. Uses Gravity mode.
 ParticleSpiral:    Point particle system. Uses Gravity mode.
 ParticleExplosion: Point particle system. Uses Gravity mode.
 ParticleSmoke:     Point particle system. Uses Gravity mode.
 ParticleSnow:      Point particle system. Uses Gravity mode.
 ParticleRain:      Point particle system. Uses Gravity mode.
 
 MODE:
    Radius:
        Enabling:
            m_nEmitterMode = kCCParticleModeGravity;
            modeA.gravity = ccp(0,-90);
        Only Properties:


    Gravity:
        Enabling:
            m_nEmitterMode = kCCParticleModeRadius;
            modeB.startRadius = 0;
            modeB.startRadiusVar = 0;//ccp(0,0);
        Only Properties: These properties are only valid in Radius Mode:
            startRadius       (a float)  The starting radius of the particles
            startRadiusVar    (a float)  The starting radius variance
            endRadius         (a float)  The ending radius of the particles.
            endRadiusVar      (a float)  The ending radius variance
            otatePerSecond    (a float)  Number of degress to rotate a particle around the source pos per second.
            rotatePerSecondVar(a float)  Number of degrees variance.


    Common:
 
            startSize: Start size of the particles in pixels
            startSizeVar
            endSize:    Use kCCParticleStartSizeEqualToEndSize if you want that the start size == end size.
            endSizeVar
            startColor      (a ccColor4F)
            startColorVar   (a ccColor4F)
            endColor        (a ccColor4F)
            endColorVar     (a ccColor4F)
            startSpin       Only used in ParticleSystemQuad
            startSpinVar    Only used in ParticleSystemQuad
            endSpin         Only used in ParticleSystemQuad
            endSpinVar      Only used in ParticleSystemQuad
            life:           time to live of the particles in seconds
            lifeVar:
            angle:          (a float). Starting degrees of the particle
            angleVar
            positon:        (a Point)
            posVar
            centerOfGravity (a Point)
 
 
    Common properties of the system:
 
            emissionRate    (a float)
                            How many particle are emitted per second
            duration        (a float)
                            How many seconds does the particle system (different than the life property) lives. 
                            Use kCCParticleDurationInfinity for infity.
            blendFunc       (a ccBlendFunc) 
                            The OpenGL blending function used for the system
            positionType    (a tCCPositionType)
                            Use kCCPositionTypeFree (default one)for moving particles freely. 
                            Or use kCCPositionTypeGrouped to move them in a group.

            texture         (a Texture2D)
                            The texture used for the particles

 */
class ParticleSystemManager {

public:

    /**
     * Should be set by the game layer of game 
     * object contracting the service fro this class
     */
    static Node* m_GameLayer;

    /**
     * Add Smoke to GameLayer
     */
    static ParticleSystemQuad* smoke(
                cocos2d::Point p,
                float scale ,
                float duration){



        ParticleSystemQuad* particalSystem = ParticleSmoke::create();
        particalSystem->setDuration(scale);
        particalSystem->setScale(scale);
        particalSystem->setPosition(p);

        m_GameLayer->addChild(particalSystem);

        DelayTime*  delayTimeAction    = DelayTime::create(2*duration);
        CallFunc*   removeAndCleanUp   = CallFunc::create( std::bind(&cocos2d::ParticleGalaxy::removeFromParent,particalSystem));
        Sequence*   seq                = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
        particalSystem->runAction(seq);

        return particalSystem;
    }

    /**
     * Add Smoke to target, this is used for example on the player ship in
     * asteroid to indicate the player is injured, smmoking comming off the ship
     * for example
     */
    static ParticleSystemQuad* smoke(Node* taget,float scale ,float duration){


        cocos2d::ParticleSystemQuad* particalSystem =cocos2d::ParticleSmoke::create();
        particalSystem->setDuration(scale);
        particalSystem->setScale(scale);

        taget->addChild(particalSystem);

        DelayTime*  delayTimeAction  =  DelayTime::create(2*duration);
        CallFunc*   removeAndCleanUp =  CallFunc::create( std::bind(&cocos2d::ParticleGalaxy::removeFromParent,particalSystem));
        Sequence*   seq              =  Sequence::create(delayTimeAction,removeAndCleanUp,NULL);

        particalSystem->runAction(seq);
        
        return particalSystem;
        
    }

    /**
     * Add explosion to target, this is used for example on the player ship in
     * asteroids to indicate the player took damage of game object was destoyed
     */
    static cocos2d::ParticleSystemQuad*   sun(
                cocos2d::Node* target,
                float scale,
                float duration){


        ParticleSystemQuad* particalSystem = ParticleSun::create();
        particalSystem->setDuration(duration);
        particalSystem->setScale(scale);
        particalSystem->setPosition(target->getPosition());

        target->addChild(particalSystem);

        DelayTime*  delayTimeAction = DelayTime::create(2*duration);
        CallFunc*   removeLabel     = CallFunc::create( std::bind(&cocos2d::ParticleSun::removeFromParent,particalSystem));
        Sequence*   lableSequence   = Sequence::create(delayTimeAction,removeLabel,NULL);
        particalSystem->runAction(lableSequence);

        return particalSystem;

    }

    static cocos2d::ParticleSystemQuad*  galaxy(
                                                cocos2d::Node* target,
                                                float scale,
                                                float duration){

        cocos2d::ParticleSystemQuad* particalSystem =cocos2d::ParticleGalaxy::create();
        particalSystem->setDuration(scale);
        particalSystem->setScale(scale);
        particalSystem->setPosition(target->getPosition());

        target->addChild(particalSystem);

        cocos2d::DelayTime*  delayTimeAction = cocos2d::DelayTime::create(2*duration);
        cocos2d::CallFunc*   removeAndCleanUp =    cocos2d::CallFunc::create( std::bind(&cocos2d::ParticleGalaxy::removeFromParent,particalSystem));
        cocos2d::Sequence*   seq = cocos2d::Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
        particalSystem->runAction(seq);
        
        return particalSystem;
        
    }

};
