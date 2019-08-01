
#include "SoundManager.h"
#include "Mine.h"
#include "Utils.h"

#include <string>

using namespace cocos2d;
using namespace std;

const std::string Mine::IDENTITY = "Mine";
const int Mine::TAG = GameAssets::TAGS::MINE;// 200;
const int Mine::MAX_HEALTH = 200;
const int Mine::WEIGTH = 75;
const float Mine::MASS = 100;

#include "GameObject.h"

const std::string Mine::PNG= GameAssets::Sprite::MINE ;
const std::string Mine::SND_EXPLODE= GameAssets::Sound::SHOTGUN;

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32  )
pthread_mutex_t Mine::lock= PTHREAD_MUTEX_INITIALIZER;
#endif


Mine* Mine::create(
    Point spawnPoint,
    Point mineLocation,
    bool isUsingPhysics, bool isUsingOnContact,
    bool isStationary ){
    
    Mine* mine = Mine::create();
    mine->spawnPoint = spawnPoint;
    mine->mineLocation = mineLocation;
    return mine;
}


bool  Mine::init()
{
    this->setIdentity(IDENTITY.c_str());
    this->initWithFile(PNG);
    this->setTag(TAG);
    this->setMaxHealth(MAX_HEALTH);
    this->setHealth(MAX_HEALTH);
    
    return true;
}


void Mine::start( ) {
    
    setPosition(getSpawnPoint());
    
    if (getIsUsingPhysics()){
        usePhysics();
    }
    
    if ( getIsUsingOnContact()){
        useOnContact();
    }
    
    scheduleUpdate();
    
    setStatus(IN_PLAY);
}


void Mine::explodeMine(){
    setStatus(DEAD);
    SoundManager::playEffect(SND_EXPLODE);
    GameObject::sun(5, .5);
    cleanUp();
}


void Mine::takeDamage(int weight){
    setHealth ( getHealth() - weight);
    if(getHealth() <= 0){
        explodeMine();
    }
}


void Mine::update(float dt){
    
    if (  getReferenceCount() == 0 ){
        return;
    }
    manualCollisionCheck(dt);
    manualWarningProximityCheck();
    injured();
}


void Mine::manualWarningProximityCheck() {
    
 
    if (  getReferenceCount() == 0 ){
        return;
    }
    float distanceWarn = 2 * getContentSize().width;
    auto p = getPlayer()->getPosition();
    auto m = getPosition();
    float d =  m.getDistance(p);
    if ( d < distanceWarn) {
        SoundManager::bell();
    }
};

/**
 * Manual Collision Detection Rountine
 */
void Mine::manualCollisionCheck(float dt){
    
    if ( getPlayer()->getBoundingBox().intersectsRect( getBoundingBox())){
        log("Mine::collision");
        getPlayer()->takeDamage(WEIGTH);
        explodeMine();
        return;
    }
}

void Mine::injured() {
}




void Mine::usePhysics(){
    setIsUsingPhysics(true);
    auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    this->setPhysicsBody(body);
}

void Mine::useOnContact(){
    setIsUsingOnContact(true);
    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Mine::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

/**
* Chipmunk Physics Collision
*/
bool Mine::onContactBegin(cocos2d::PhysicsContact& contact)
{
    log("Mine::onContactBegin");
    
    PhysicsBody *a = contact.getShapeA()->getBody();
    Node* nodeA = a->getNode();
    int tagA =a->getTag();
    
    PhysicsBody *b = contact.getShapeB()->getBody();
    Node* nodeB = b->getNode();
    int tagB = b->getTag();
    
    if ( tagA ==  TAG ){
        
        log("Mine::onContactBegin");
        
        if (tagB == getPlayer()->getTag()){
             log("Mine::onContactBegin(Mine,Player)");
        }
        if (tagB == GameAssets::TAGS::PLAYER_PROJECTILE){
              log("Mine::onContactBegin(Mine,PlayerProjectile)");
        }

    }
    if ( tagB ==  TAG ){
        log("Mine::onContactBegin");
        if (tagA == getPlayer()->getTag()){
              log("Mine::onContactBegin(Player,Mine)");
        }
        if (tagA == GameAssets::TAGS::PLAYER_PROJECTILE){
                log("Mine::onContactBegin(PlayerProjectile,mine)");
        }
    }

    return true;
}



void Mine::cleanUp(){
    unscheduleUpdate();
    unscheduleAllCallbacks();
    setVisible(false);
    //removeFromParent();
    removeFromParentAndCleanup(true);
}

//Mine::~Mine(){
//    setStatus(DEAD);
//    cleanUp();
//    log("~Mine()");
//    removeFromParent();
//}
