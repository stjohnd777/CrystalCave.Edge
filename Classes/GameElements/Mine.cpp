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

const std::string Mine::PNG= "space_mine.png" ;
const std::string Mine::SND_EXPLODE="Sound/shotgun.wav";

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32  )
pthread_mutex_t Mine::lock= PTHREAD_MUTEX_INITIALIZER;
#endif


Mine* Mine::create(
    Point spawnPoint,
    Point mineLocation,
    bool isUsingPhysics, bool isUsingOnContact,
    bool isStationary ){
    
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
     explodeMine();
}

void Mine::takeDamage(int weight){
    setHealth ( getHealth() - weight);
    if(getHealth() <= 0){
        explodeMine();
    }
}

void Mine::warn() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("000570954.caf", false);
    FiniteTimeAction* actionBlink   = Blink::create(1, 10);
    this->runAction(actionBlink);
};


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
    PhysicsBody *a = contact.getShapeA()->getBody();
    Node* nodeA = a->getNode();
    int tagA =a->getTag();
    
    PhysicsBody *b = contact.getShapeB()->getBody();
    Node* nodeB = b->getNode();
    int tagB = b->getTag();

    return true;
}

/**
 * Manual Collision Detection Rountine
 */
void Mine::collision(float dt){

    if ( getPlayer()->getBoundingBox().intersectsRect( getBoundingBox())){
        collisionOccured();
        return;
    }

}

void Mine::update(float dt){
    collision(dt);

}

void Mine::start( ) {

    setPosition(getSpawnPoint());
    
    if (getIsUsingPhysics()){
        usePhysics();
    }
    
    if ( getIsUsingOnContact()){
        useOnContact();
    }
    
//    if ( ! m_IsStationary ){
//        // constant velocity move
//        FiniteTimeAction* actionMove    = MoveTo::create(2, getMineLocation() );
//        FiniteTimeAction* delay         = DelayTime::create(3);
//        FiniteTimeAction* actionBlink   = Blink::create(1, 10);
//        FiniteTimeAction* actionExploed = CallFunc::create( [&]() {explodeMine();} );
//        FiniteTimeAction* actionCleanUp = CallFunc::create( [&]() {cleanUp();} );
//
//        this->runAction( Sequence::create(actionMove,delay,actionBlink, actionExploed,actionCleanUp,nullptr) );
//    }

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
    unscheduleAllCallbacks();
    removeFromParentAndCleanup(true);
}

Mine::~Mine(){
    log("~Mine()");
}
