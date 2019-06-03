//
//  LunarModule.cpp
//  AsteroidTrouble.cocos2dx.3.2
//
//  Created by Daniel St. John on 5/17/15.
//
//
#include "GameAssets.h"
#include "SoundManager.h"
#include "LunarModule.h"
#include "SimpleAudioEngine.h"
#include "LabelManager.h"

using namespace cocos2d;
//using namespace CocosDenshion;
//#include "SimpleAudioEngine.h"


const int LunarModule::TAG = GameAssets::TAGS::PLAYER;
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

LunarModule* LunarModule::INSTANCE = nullptr;

bool LunarModule::init(){

    INSTANCE = this;
    
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
    
    
    for(int i = 0; i < 5; i++) {
        std::stringstream ss;
        
        ss << "⁨Animations⁩/Thruster⁩/thruster" << i << ".png";
        std::string name = ss.str();
        auto sprite = Sprite::create();
        sprite->initWithFile(name);
        auto spriteFrame = sprite->getSpriteFrame();
        vectorSpriteFrames.pushBack(spriteFrame);
    }
    
    return true;
}


void LunarModule::thrushOff(){
    if ( soundId != -1){
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
        soundId = -1;
    }
}

void LunarModule::applyThrush(Vec2 force, float percentage){
    
 
    SoundManager::playEffect(GameAssets::Sound::WOOSH);

    float forcex = ( percentage * MAX_THRUST) * force.x;
    float forcey = ( percentage * MAX_THRUST) * force.y;
    Vec2 thrustAdjustedForceImplusVector(forcex,forcey);


    if (this) {

        Point posBust =  this->getPosition();
        if ( force.x > 0){
            posBust.x = this->getPosition().x - 64 ;
        }
        if ( force.x < 0){
            posBust.x = posBust.x + 64 ;
        }
        
        if ( force.y > 0){
            posBust.y = posBust.y - 64 ;
            
        
            auto animation = Animation::createWithSpriteFrames(vectorSpriteFrames, 1/60);
            Sprite * thrustContainer = Sprite::create();
            thrustContainer->setTag(777);
            thrustContainer->setPosition(getPosition());
            thrustContainer->setPosition(Vec2(0,-64));
            this->addChild(thrustContainer,1000);
            CallFunc* cleanUp = CallFunc::create([&](){
                this->removeChildByTag(777);
               
            });
            Sequence * seq = Sequence::create(Animate::create(animation),cleanUp,nullptr);
            thrustContainer->runAction( seq );
            
        }
        
        if ( force.y < 0){
            posBust.y = posBust.y +64;
        }

        ParticleSystemQuad* particalEffectBurst = ParticleSmoke::create();
        particalEffectBurst->setDuration(.1);
        particalEffectBurst->setPosition(posBust);
        getGameLayer()->addChild(particalEffectBurst);
        
        // TODO :: is this needed
        DelayTime*  delayTimeAction = DelayTime::create(2*1);
        CallFunc*   removeAndCleanUp = CallFunc::create(std::bind(&ParticleSmoke::removeFromParent,particalEffectBurst));
        Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,nullptr);

        particalEffectBurst->runAction(seq);
    }

    getPhysicsBody()->applyImpulse(thrustAdjustedForceImplusVector);

}


void LunarModule::update(float dt) {
    //log("LunarModule:update");
    injured();
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
    //log("LunarModule:takeDamage");
    SoundManager::debris();
    
    LabelManager::getInstance()->makeHitLabel(weight, getPosition());
    
    decrementHealth(weight);
    if ( getHealth() <=0){
        die();
    }
}

/**
 * injured behavior optional, like a limping ship, and
 * give default of nothing
 */
bool isOnFire = false;
float duration = -1;
int injuredTag = 38374;
int soundId = 0;
int soundIdAlarms = 0;
 void LunarModule::injured() {
     //log("LunarModule:injured");
     
     // DAMAGED
     if ( getHealth() < 50 && isOnFire == false) {
         
         isOnFire = true;
         float scale =    1; //100/ getHealth();
         ParticleSystemQuad* particalSystem =ParticleFire::create();
         particalSystem->setDuration(duration);
         particalSystem->setScale(scale);
         particalSystem->setTag(injuredTag);
         particalSystem->setPosition(Vec2::ZERO);
         this->addChild(particalSystem);
         soundId = SoundManager::alarm(true);
 
         float interval = 17;
         unsigned int repeat = 0;
         float delay = 0;
         const std::string key = "alarm";
         
         this->schedule([&](float dt){
              soundId = SoundManager::alarm(true);
         }, interval, repeat, delay, key);
        
     }
     // RECOVERED
     else if ( getHealth() > 50 && ( isOnFire || soundId != 0 || soundIdAlarms !=0) ) {
 
         isOnFire = false;
         if (soundId != 0){
             this->unschedule("alram");
             SoundManager::stopEffect(soundId);
             soundId = 0;
         }
         if (soundIdAlarms!=0){
             this->unschedule("alrams");
             SoundManager::stopEffect(soundIdAlarms);
             soundIdAlarms = 0;
            
         }
         auto fireEffect =  this->getChildByTag(injuredTag);
         if ( fireEffect!= nullptr){
             this->getChildByTag(injuredTag)->removeFromParentAndCleanup(true);
         }
        
     }
     
     
     // CRITICAL
     if ( getHealth()  <  10  && isOnFire){
         float scale = 2;//100/ getHealth();
         auto effect = this->getChildByTag(injuredTag);
         if ( effect) {
            effect ->setScale(scale);
         }
     }
 }

/**
 * Object do you death sequence
 */
 void LunarModule::die() {
     //log("LunarModule::die");
     explosion();
 };


bool LunarModule::stop(){
    
    isOnFire = false;
    if (soundId != 0){
        this->unschedule("alram");
        SoundManager::stopEffect(soundId);
        soundId = 0;
    }
    if (soundIdAlarms!=0){
        this->unschedule("alrams");
        SoundManager::stopEffect(soundIdAlarms);
        soundIdAlarms = 0;
        
    }
    auto fireEffect =  this->getChildByTag(injuredTag);
    if ( fireEffect!= nullptr){
        this->getChildByTag(injuredTag)->removeFromParentAndCleanup(true);
    }
    
    unscheduleAllCallbacks();
    
    return true;
}


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
    
    PhysicsBody *a = contact.getShapeA()->getBody();
    Node* nodeA = a->getNode();
    int tagA =a->getTag();

    PhysicsBody *b = contact.getShapeB()->getBody();
    Node* nodeB = b->getNode();
    int tagB = b->getTag();
    
    if ( tagA == LunarModule::TAG ){
        log("LunarModule::onContactBegin");
    }
    if ( tagB == LunarModule::TAG ){
        log("LunarModule::onContactBegin");
    }
    
    return false;
    
};
