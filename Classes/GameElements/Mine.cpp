#include "Mine.h"
#include "Utils.h"

#include "SimpleAudioEngine.h"

#include <string>

using namespace cocos2d;
using namespace std;

const std::string Mine::IDENTITY = "Mine";
const int Mine::TAG = 200;
const int Mine::MAX_HEALTH = 200;
const int Mine::WEIGTH = 75;
const float Mine::MASS = 100;

#include "GameObject.h"

const std::string Mine::PNG= "space_mine.png" ;//__mine.png";
const std::string Mine::SND_EXPLODE="Sound/shotgun.wav";

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32  )
pthread_mutex_t Mine::lock= PTHREAD_MUTEX_INITIALIZER;
#endif


Mine* Mine::create(Point spawnPoint, Point mineLocation, bool isUsingPhysics, bool isUsingOnContact, bool isStationary ){
    
    Mine* mine = Mine::create();
    mine->setIsStationary(isStationary);
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


void Mine::collisionOccured()
{
    explodeMine();
}


void Mine::explodeMine(){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SND_EXPLODE.c_str(), false);
    GameObject::sun(5, .5);
    GameObject::explosion();
    if ( getPlayer() != nullptr)
    {
        if ( Utils::isInterscting(this, getPlayer()->getBoundingBox()) ){
            getPlayer()->takeDamage(WEIGTH);
        }
    }
    cleanUp();

}



void Mine::injured() {
}

void Mine::die(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SND_EXPLODE.c_str(), false);
    GameObject::sun(5, .5);
}

void Mine::takeDamage(int weight){
    setHealth ( getHealth() - weight);
    if(getHealth() <= 0){
        explodeMine();
    }
}

void Mine::warn() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("000570954.caf", false);
    FiniteTimeAction* actionBlink   = CCBlink::create(1, 10);
    this->runAction(actionBlink);
};


void Mine::usePhysics(){
    
    setIsUsingPhysics(true);
    auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
    body->setContactTestBitmask(true);
//    body->setTag(GameAssets::Sprite::TAG_METEOR);
    body->setDynamic(true);
    this->setPhysicsBody(body);
}

void Mine::useOnContact(){
    setIsUsingOnContact(true);
    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Mine::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

/*
 * -begin: 
 * Two shapes just started touching for the first time this step.
 * Return true from the callback to process the collision normally or false to cause physics engine to
 * ignore the collision entirely.
 *
 * If you return false, the preSolve() and postSolve() callbacks will never be run, but you will still
 * receive a separate event when the shapes stop overlapping.
 */
bool Mine::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    Node* nodeA = a->getNode();
    int tagA =a->getTag();
    
    PhysicsBody *b = contact.getShapeB()->getBody();
    Node* nodeB = b->getNode();
    int tagB = b->getTag();
    
//    Projectile* projectile = nullptr;
//    Mine* mine = nullptr;
//
//
//    if ( tagA == GameAssets::Sprite::TAG_MINE && tagB == GameAssets::Sprite::TAG_PROJECTILE ){
//        projectile = dynamic_cast<Projectile*>(nodeB);
//        mine = dynamic_cast<Mine*>(nodeA);
//        if (mine && projectile) {
//            mine->takeDamage(projectile->getWeight());
//            mine->removeFromParentAndCleanup(true);
//            projectile->removeFromParentAndCleanup(true);
//        }
//    }else if ( tagB == GameAssets::Sprite::TAG_MINE && tagA == GameAssets::Sprite::TAG_PROJECTILE){
//        projectile = dynamic_cast<Projectile*>(nodeA);
//        mine = dynamic_cast<Mine*>(nodeB);
//        if (mine && projectile){
//            mine->takeDamage(projectile->getWeight());
//            mine->removeFromParentAndCleanup(true);
//            projectile->removeFromParentAndCleanup(true);
//        }
//    }

    return true;
}

/**
 * Manual Collision Detection Rountine
 */
void Mine::collision(float dt){
    
    // collsion player
    if ( getPlayer()->getBoundingBox().intersectsRect( getBoundingBox())){
        collisionOccured();
        return;
    }
    
     // collsion projectile
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 )
//    pthread_mutex_lock(&lock);
//#endif
//    for (Projectile* pp:  *Projectile::m_ActiveProjectiles) {
//        if ( Utils::isInterscting(this, pp)){
//            collisionOccured();
//            break;
//        }
//    }
//
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32  )
//    pthread_mutex_unlock(&lock);
//#endif

    // collision target
};

void Mine::update(float dt){
    collision(0);

}

void Mine::start( ) {

    setPosition(getSpawnPoint());
    
    if (getIsUsingPhysics()){
        usePhysics();
    }
    
    if ( getIsUsingOnContact()){
        useOnContact();
    }
    
    if ( ! m_IsStationary ){
        // constant velocity move
        FiniteTimeAction* actionMove    = MoveTo::create(2, getMineLocation() );
        FiniteTimeAction* delay         = DelayTime::create(3);
        FiniteTimeAction* actionBlink   = CCBlink::create(1, 10);
        FiniteTimeAction* actionExploed = CallFunc::create( [&]() {explodeMine();} );
        FiniteTimeAction* actionCleanUp = CallFunc::create( [&]() {cleanUp();} );

        this->runAction( CCSequence::create(actionMove,delay,actionBlink, actionExploed,actionCleanUp,nullptr) );
    }
    
    // manual collision/pximity alarm and detonition trigger
    scheduleUpdate();

//    std::string name = "mine_idel";
//    std::string animationSheet = "mine.png";
//    std::string plist = "mine.plist";
//    std::string subject = "mine";
//    int length =10;
//    float dt =  .25;
//    bool isForEver = true;
//    animationSpriteSheet(
//                              name,
//                              animationSheet,
//                              plist,
//                              subject,
//                              length,
//                              dt,
//                              isForEver );
    
    setStatus(IN_PLAY);
}


void Mine::cleanUp(){
    unscheduleAllSelectors();
    removeFromParentAndCleanup(true);
}

Mine::~Mine(){
    log("~Mine()");
}
