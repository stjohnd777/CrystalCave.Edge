//
//  LunarModule.cpp
//  AsteroidTrouble.cocos2dx.3.2
//
//  Created by Daniel St. John on 5/17/15.
//
//
#include "GameAssets.h"
#include "LunarModule.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
#include "SimpleAudioEngine.h"


const int LunarModule::TAG = 8745;
const int LunarModule::WEIGHT = 75; // hit pts
const int LunarModule::HEALTH = 100;
const float LunarModule::MASS = 75; //kg
const float LunarModule::MAX_THRUST = 5000;//1500; //kg

const std::string LunarModule::THRUST_SOUND = "thrusters.mp3";
const std::string LunarModule::LAND_SOUND = "applause.mp3";
const std::string LunarModule::HIT_SOUND = "debris.wav";
const std::string LunarModule::DIE_SOUND = "wawawa.mp3";
const std::string LunarModule::PNG ="red_falcon.png";

float scale =  .75;

bool LunarModule::init(){
    
    this->initWithFile(PNG);
    
    setScale( scale);
    
    soundId = -1 ;
    
    setIdentity("LunarModule");
    setTag(TAG);
    setWeight(WEIGHT);
    setMaxHealth(HEALTH);
    setHealth(HEALTH);
    usePhysics();
    useOnContact();
    
    return true;
}


void LunarModule::thrushOff(){
    if ( soundId != -1){
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
        soundId = -1;
    }
}

void LunarModule::applyThrush(Vec2 force, float percentage){
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::WOOSH, false);
    //CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1);

    float forcex = ( percentage * MAX_THRUST) * force.x;
    float forcey = ( percentage * MAX_THRUST) * force.y;
    Vec2 thrustAdjustedForceImplusVector(forcex,forcey);


    if (this) {

        float offset = 128 / 2 * .1;
        Point posBust = this->getPosition();
        if ( force.x > 0){
            posBust.x = posBust.x - (getContentSize().width  + offset);
        }
        if ( force.x < 0){
            posBust.x = posBust.x + (getContentSize().width + offset);
        }
        if ( force.y > 0){
            posBust.y = posBust.y - (getContentSize().width  + offset);
        }
        if ( force.y < 0){
            posBust.y = posBust.y + (getContentSize().width  + offset);
        }

        //auto particalEffectBurst = smoke(1, .5);

        ParticleSystemQuad* particalEffectBurst =ParticleSmoke::create();
        particalEffectBurst->setDuration(1);
        particalEffectBurst->setScale(.5);
        particalEffectBurst->setPosition(posBust);
        getGameLayer()->addChild(particalEffectBurst);
        DelayTime*  delayTimeAction = DelayTime::create(2*1);
        CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&ParticleSmoke::removeFromParent,particalEffectBurst));
        Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,nullptr);

        particalEffectBurst->runAction(seq);
    }

    getPhysicsBody()->applyImpulse(thrustAdjustedForceImplusVector);

}


void LunarModule::update(float dt) {
    
};


/**
 * Generic move object to point p in time dt in straigh line
 */
 void LunarModule::move(cocos2d::Point p,float dt)
{
    
}

/**
 * Take Damage
 */
void LunarModule::takeDamage(int weight){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav");
    explosion();
    decrementHealth(weight);
    if ( getHealth() <=0){
        die();
    }
}

/**
 * injured behavior optional, like a limping ship, and
 * give default of nothing
 */
 void LunarModule::injured() {
 };

/**
 * Object do you death sequence
 */
 void LunarModule::die() {
     explosion();
 };


/**
 * uses Physics engine
 */
void LunarModule::usePhysics() {
    setIsUsingPhysics(true);
    auto body = PhysicsBody::createCircle(this->getContentSize().width * scale / 2);
    body->setContactTestBitmask(true);
    body->setTag(TAG);
    body->setMass(MASS);
    body->setDynamic(true);
    this->setPhysicsBody(body);
};
/**
 * uses Physics engine collision
 */
void LunarModule::useOnContact() {
    setIsUsingOnContact(true);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LunarModule::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
};
/**
 * Physics engine notification of contact
 */
bool LunarModule::onContactBegin(cocos2d::PhysicsContact& contact) {
    
//    PhysicsBody *a = contact.getShapeA()->getBody();
//    Node* nodeA = a->getNode();
//    int tagA =a->getTag();
//    
//    PhysicsBody *b = contact.getShapeB()->getBody();
//    Node* nodeB = b->getNode();
//    int tagB = b->getTag();
//    
//            Projectile* projectile = NULL;
//            Seeker * seeker = NULL;
//    
//            if ( tagA == TAG_SEEKER && tagB == GameAssets::Sprite::TAG_PROJECTILE ){
//                projectile = dynamic_cast<Projectile*>(nodeA);
//                seeker = dynamic_cast<Seeker*>(nodeB);
//                if (seeker) {
//                    seeker->hit(projectile->getWeight());
//                }
//                return true;
//            }else if ( tagB ==TAG_SEEKER && tagA == GameAssets::Sprite::TAG_PROJECTILE){
//                projectile = dynamic_cast<Projectile*>(nodeA);
//                seeker = dynamic_cast<Seeker*>(nodeB);
//                if (seeker) {
//                    seeker->hit(projectile->getWeight());
//                }
//                return true;
//    
//            }
//     //not interested
    return false;
    
};
