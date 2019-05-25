
#include "GameObject.h"

#include <sstream>
#include "SimpleAudioEngine.h"
#include "GameAssets.h"
#include "Utils.h"


using namespace std;

using namespace cocos2d;

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32  )
    pthread_mutex_t GameObject::lock= PTHREAD_MUTEX_INITIALIZER;
#endif


GameObject::GameObject() :
m_Weight(100),
m_Value(100),
m_Health(100),
m_MaxHealth(100),
m_usesHealthLabel(false),
m_IsUsingIndependentCollisionDetection(false),
m_IsUsingPhysics(false),
m_IsUsingOnContact(false) ,
m_GameLayer(nullptr),
m_Player(nullptr),
usesInfoLabel ( false)
{
    
    static int counter = 0;
    m_uuid = counter ++;

    
    log("%d > GameObject::GameObject()",m_uuid);

}

void GameObject::setSizeInPercentageScene(float percentage){
    
    Size me = getContentSize();
    Size size = Director::getInstance()->getWinSize();
    float scaleX = percentage* size.width/me.width;
    setScaleX(scaleX);
    float scaleY = percentage*size.height/me.height;
    setScaleY(scaleY);
    
}

void GameObject::setSizeInPercentageScene(float percentageX, float percentageY){
    
    Size me = getContentSize();
    Size size = Director::getInstance()->getWinSize();
    float scaleX = percentageX* size.width/me.width;
    setScaleX(scaleX);
    float scaleY = percentageY*size.height/me.height;
    setScaleY(scaleY);
}

void GameObject::setSize(float x, float y){
    GameObject::setScale( x/ getContentSize().width,  y/getContentSize().height);
}

void  GameObject::setSize(cocos2d::Size s){
    // TODO
    setScale( s.width/ this->getContentSize().width,  s.height/ this->getContentSize().height);
}



void GameObject::decrementHealth (int decrement){
    
    setHealth (getHealth() - decrement);
    if ( getHealth() <= 0){
        die();
    }
    
}
void   GameObject::incrementHealth (int increment){
    setHealth (getHealth() + increment);
}

/*
 * It is very nice idea to have a game mechanic that is inspired by BorderLands,
 * where every game object has a health bar that is visable when being attached,
 * or mouse overed, and hit point displayeyd on each hit, in seperate lable, then faded away
 * The health mechanism displays the bar and percent health, where the lables display the damage
 * taken
 */
void  GameObject::updateLabels(float dt){

    // label
    if ( getUsesHealthLabel()) {
        memset(m_szHealth, 0, 10);
        float percent = 100 * (float)getHealth() / (float)getMaxHealth();
        sprintf(m_szHealth,"%3.0f %%", percent);
        m_healthLabel->setString(m_szHealth);

        // bar
        int contentwidth = getContentSize().width / 32;
        m_healthBarScale = contentwidth* percent/100 ;
        m_healthBar->setScaleX(m_healthBarScale);

        //Point pos = Vec2(getPosition().x  -16,getPosition().y  + getContentSize().height/2 + 17 );
        
        
        m_healthLabel->setRotation(-getRotation());
        m_healthBar->setRotation(-getRotation());
        m_hollow->setRotation(-getRotation());
        
//        m_healthLabel->setPosition(pos);
//        m_healthBar->setPosition(pos);
//        m_hollow->setPosition(pos);
    }
    
    

    if (usesInfoLabel){
   
        std::stringstream ss;
        float mass = getPhysicsBody()->getMass();
        Vec2 velocity = getPhysicsBody()->getVelocity();
        float angularVelocity = getPhysicsBody()->getAngularVelocity();
        //float moment = getPhysicsBody()->getMoment();
        Vec2 pos = getPhysicsBody()->getPosition();
        float rotation = getPhysicsBody()->getRotation();
        ss<< "p:" <<"("<<pos.x<<","<<pos.y <<")" << endl;
        ss<<"rot:" << rotation << endl;
        ss << "mass:"<<mass<<endl;
        ss<<"v:"<< "("<<velocity.x<<","<<velocity.y <<")" << endl;
        ss<< "angular v:" << angularVelocity << endl;
        sprintf(m_szInfo,"%s", ss.str().c_str());
        
        m_InfoLabel->setString(m_szInfo);
        m_InfoLabel->setRotation(-getRotation());
        
        //m_InfoLabel->setPosition(pos + Vec2(getContentSize().width/2,0));
    }

    
}


void GameObject::move(cocos2d::Point p,float dt) {
 
    //MoveTo* actionMove =MoveTo::create(dt,p);
    //this->runAction( actionMove );
}


void  GameObject::useHealthLabel(){
    
    setUsesHealthLabel(true);
 
    
    int contentHeight = getContentSize().height;
    Point pos  = Vec2(getPosition().x ,getPosition().y + contentHeight );
    
    memset(m_szHealth, 0, 256);
    sprintf(m_szHealth,"%s","100%");

    auto font = GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL;
    m_healthLabel = Label::createWithBMFont(font,m_szHealth);
    m_healthLabel->setAnchorPoint(Vec2(0,0.5));
    m_healthLabel->setColor(Color3B::YELLOW);
 
    m_healthLabel->setPosition(pos);
    m_healthLabel->setZOrder(9999);
 
    addChild(m_healthLabel);
    
 

    m_healthBar = Sprite::create("box.red.32.32.png");
    if (m_healthBar){
        m_healthBarScale = 1;
        m_healthBar->setScaleX(m_healthBarScale);
        m_healthBar->setPosition(pos);
        m_healthBar->setAnchorPoint(Vec2(0,0.5));
        addChild(m_healthBar);
    }
    
    m_hollow = Sprite::create("box.red.hollow.32.32.png");
    if (m_hollow){
        m_hollow->setScaleX(m_healthBarScale);
        m_hollow->setPosition(pos);
        m_hollow->setAnchorPoint(Vec2(0,.5));
        addChild(m_hollow);
    }


    schedule( schedule_selector(GameObject::updateLabels) );
}


void  GameObject::useInfoLabel(){
    
    usesInfoLabel = true;
    
    memset(m_szInfo, 0, 256);
    sprintf(m_szInfo,"%s","Info Label");
    auto font = GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL;
    m_InfoLabel = Label::createWithBMFont(font,m_szInfo);
    m_InfoLabel->setWidth(2* getContentSize().width);
    m_InfoLabel->setHeight(2* getContentSize().height);
    m_InfoLabel->setAnchorPoint(Vec2(0,.5));
    m_InfoLabel->setColor(Color3B::YELLOW);
    m_InfoLabel->setPosition(this->getPosition());
    m_InfoLabel->setZOrder(9999);
    m_InfoLabel->retain();
    m_InfoLabel->setPosition( Vec2(getContentSize().width,0));
    //getGameLayer()->
    addChild(m_InfoLabel);
    
}


ParticleSystemQuad*  GameObject::randumParticalEffect(float scale,float duration){
    
    ParticleSystemQuad* effect;
    int randInt = Utils::getRandomIntBetweenTopBottom(0,11);
    switch (randInt) {
        case EXPLOSION:
            effect = explosion(scale, duration);
            break;
        case SMOKE:
            effect = smoke(scale, duration);
            break;
        case FIRE:
            effect = fire(scale, duration);
            break;
        case GALAXY:
            effect = galaxy(scale, duration);
            break;
        case FIREWORKS:
            effect = fireworks(scale, duration);
            break;
        case METEOR:
            effect = meteor(scale, duration);
            break;
        case FLOWER:
            effect = flower(scale, duration);
            break;
        case RAIN:
            effect = rain(scale, duration);
            break;
        case SNOW:
            snow(scale, duration);
            break;
        case SPIRAL:
            effect = spiral(scale, duration);
            break;
        case SUN:
            effect = sun(scale, duration);
            break;
        default:
            effect = spiral(scale, duration);
            break;
    }
    return effect;
}


ParticleSystemQuad*  GameObject::explosion(float scale,float duration){
    
    // TODO make effect tied to target type
    ParticleSystemQuad* particalSystem = ParticleExplosion::create();
    particalSystem->setPosition(getPosition());
    particalSystem->setDuration(duration);
    particalSystem->setScale(scale);
    particalSystem->setTag(287);
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&ParticleExplosion::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);
    
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}

ParticleSystemQuad* GameObject::smoke(float scale,float duration){
    ParticleSystemQuad* particalSystem =ParticleSmoke::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    auto pos =getPosition();
    particalSystem->setPosition(getPosition());

    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);

    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&ParticleSmoke::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);

    return particalSystem;
}

ParticleSystemQuad* GameObject::fire(float scale,float duration){
    ParticleSystemQuad* particalSystem =ParticleFire::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&ParticleFire::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}

ParticleSystemQuad* GameObject::galaxy(float scale,float duration){
    ParticleSystemQuad* particalSystem =ParticleGalaxy::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&ParticleGalaxy::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);

    return particalSystem;    
}

ParticleSystemQuad* GameObject::fireworks(float scale,float duration){
    ParticleSystemQuad* particalSystem =ParticleFireworks::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&ParticleFireworks::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);
    
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}

ParticleSystemQuad* GameObject::meteor(float scale,float duration){
    ParticleSystemQuad* particalSystem =ParticleMeteor::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&ParticleMeteor::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);
    
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}

ParticleSystemQuad* GameObject::rain(float scale,float duration){
    ParticleSystemQuad* particalSystem =CCParticleRain::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&CCParticleRain::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);
    
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}

ParticleSystemQuad* GameObject::snow(float scale,float duration){
    ParticleSystemQuad* particalSystem =CCParticleSnow::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&CCParticleSnow::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);
    
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}

ParticleSystemQuad* GameObject::flower(float scale,float duration){
    ParticleSystemQuad* particalSystem =ParticleFlower::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&ParticleFlower::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);
    
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}

ParticleSystemQuad* GameObject::spiral(float scale,float duration){
    ParticleSystemQuad* particalSystem =ParticleSpiral::create();
    particalSystem->setDuration(scale);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    getGameLayer()->addChild(particalSystem);
 
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc*   removeAndCleanUp =    CallFunc::create( std::bind(&CCParticleSpiral::removeFromParent,particalSystem));
    Sequence*   seq = Sequence::create(delayTimeAction,removeAndCleanUp,NULL);
    particalSystem->runAction(seq);
    
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}

ParticleSystemQuad* GameObject::sun(float scale,float duration){
    ParticleSystemQuad* particalSystem =ParticleSun::create();
    particalSystem->setDuration(duration);
    particalSystem->setScale(scale);
    particalSystem->setPosition(getPosition());
    
    
    if ( getGameLayer()  == nullptr){
        setGameLayer( getParent());
    }
    
    assert ( getGameLayer() != nullptr);
    
    getGameLayer()->addChild(particalSystem);
    
    DelayTime*  delayTimeAction = DelayTime::create(2*duration);
    CallFunc* removeLabel =    CallFunc::create( std::bind(&ParticleSun::removeFromParent,particalSystem));
    Sequence*   lableSequence = Sequence::create(delayTimeAction,removeLabel,NULL);
    particalSystem->runAction(lableSequence);
    
    
    //GameObjectManager::getInstance()->addParticalEffect(particalSystem);
    return particalSystem;
    
}


void GameObject::animation(
                           std::string name,
                           bool isForEver
                           )
{
    
    Animation * animation =  m_MapName2Animation.at(name);
    
    assert(animation!=nullptr);
    
    if (isForEver){
        this->runAction( RepeatForever::create( Animate::create(animation) ) );
    }else {
        this->runAction(  Animate::create(animation)  );
    }
}

void GameObject::animationSpriteSheet(
                           std::string name,
                           std::string animationSheet,
                           std::string plist,
                           std::string subject,
                           int length,
                           float dt,
                           bool isForEver
                           )
{
    
    // A SpriteBatchNode object contains the actual image texture of all the sprite frames.
    // You must add it to a scene, even though it won’t draw anything itself; it just needs
    // to be there so that it is part of the rendering pipeline. For example:
    SpriteBatchNode* spriteBatch = SpriteBatchNode::create(animationSheet);
    this->addChild(spriteBatch);
    
    
    // SpriteFrameCache singleton to keep track how frame names correspond to frame bounds
    // – that is, what rectangular area of the sprite sheet.
    //SpriteFrameCache * cache = SpriteFrameCache::getInstance();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
    
    Vector<SpriteFrame*> v;
    for(int i = 0; i < length; i++) {
        std::stringstream ss;
        ss << subject << "_"  << i << ".png";
        std::string name = ss.str();
        
        
        // Now we need to create a Vector object and add all frames of the animation to it.
        // In the case of this animation, we know all 4 frames have the same size, so we can
        // use a nested loop to iterate through them all, and break the loop when we finish
        // adding the 4th frame
        
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( name );
        v.pushBack(frame);
    }
    
    Animation* idleanimation = Animation::createWithSpriteFrames(v, dt);
    
    if (isForEver){
        this->runAction( RepeatForever::create( Animate::create(idleanimation) ) );
    }else {
        this->runAction(  Animate::create(idleanimation)  );
    }
 
}

void GameObject::explosion(){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explosion.wav");
    
    std::string plist = "animation_explosion.plist";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
    
    std::string animationSheet = "animation_explosion.png";
    SpriteBatchNode* spriteBatch = SpriteBatchNode::create(animationSheet);
    spriteBatch->setPosition(getPosition());
 
    Sprite * tempExp = Sprite::create();
    tempExp->setPosition(getPosition());
    getGameLayer()->addChild(tempExp,99);
    tempExp->addChild(spriteBatch);

    int length = 49;
    std::string subject = "e";
    Vector<SpriteFrame*> v;
    for(int i = 0; i < length; i++) {
        std::stringstream ss;
        ss << subject << "_"  << i << ".png";
        std::string name = ss.str();
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( name );
        v.pushBack(frame);
    }

    float dt =  .1;
    Animation* idleanimation = Animation::createWithSpriteFrames(v, dt);

        
    CallFunc* cleanUp = CallFunc::create([&](){
        //tempExp->removeFromParentAndCleanup(true);
    });
    
    Sequence * seq = Sequence::create(Animate::create(idleanimation),cleanUp,nullptr);
    tempExp->runAction( seq  );
 
}


void GameObject::sparkel(){
    
    
    std::string name ="sparkel";
    std::string animationSheet = "sparkel.png";
    std::string plist = "sparkel.plist";
    std::string subject = "sparkel";
    int length = 4;
    float dt =  .25;
    bool isForEver = true;

    
    Sprite * tempExp = Sprite::create();
    tempExp->setPosition(getPosition());
    this->addChild(tempExp,99);
    SpriteBatchNode* spriteBatch = SpriteBatchNode::create(animationSheet);
    tempExp->addChild(spriteBatch);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
    
    Vector<SpriteFrame*> v;
    for(int i = 0; i < length; i++) {
        std::stringstream ss;
        ss << subject << "_"  << i << ".png";
        std::string name = ss.str();
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( name );
        v.pushBack(frame);
    }
    Animation* idleanimation = Animation::createWithSpriteFrames(v, dt);
    tempExp->runAction( RepeatForever::create( Animate::create(idleanimation) ) );
    
}
void  GameObject::animationManual(
                     std::string name,
                     Vector<cocos2d::SpriteFrame*> v,
                     std::string plist,
                     std::string subject,
                     int length,
                     float dt,
                     bool isForEver )

{
//    Vector<SpriteFrame*> animFrames(length);
//    char str[100] = {0};
//    for(int i = 1; i < length; i++)
//    {
//        std::stringstream ss;
//        ss << subject << "_"  << i << ".png";
//        std::string name = ss.str();
//        
//        Image* image = Image::initWithImageFile(name.c_str());
//        Texture2D* texture= Texture2D::initWithImage(image);
//        cocos2d::Sprite* sprite = cocos2d::Sprite::createWithTexture(texture);
//        sprite->initWithFile(name);
//        Rect r = sprite->getContentSize();
//        
//        auto frame = SpriteFrame::create(name,r);
//        animFrames.pushBack(frame);
//       }
//                                         
//        auto animation = Animation::createWithSpriteFrames(animFrames, dt);
//       auto animate = Animate::create(animation);
    
}
                                         


void GameObject::usePhysics() {
    
    setIsUsingPhysics(true);
    // collision detection with chipmuk physics engine
    
    // Rigid Bodies:
    // A rigid body holds the physical properties of an object.
    // (mass, position, rotation, velocity, etc.)
    // It does not have a shape until you attach one or more collision shapes to it.
    // If you’ve done physics with particles before, rigid bodies differ in that they are able to rotate.
    // Rigid bodies generally tend to have a 1:1 correlation to sprites in a game,
    // use the position and rotation of the rigid body for drawing your sprite.
    auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
    body->setContactTestBitmask(getChipmunkCategoryMask());
    body->setGroup(getChipmunkGroup());
    body->setDynamic(true);
    body->setTag(getTag());
    setPhysicsBody(body);
}

void GameObject::useOnContact( ) {
    setIsUsingOnContact(true);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameObject::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameObject::cleanUp(cocos2d::Node* sender)
{
    removeFromParentAndCleanup(true);
}

GameObject::~GameObject()
{
    log("%d > ~GameObject",m_uuid);
 
    if (getUsesHealthLabel()){
        
        unscheduleAllSelectors();
        
//        m_healthLabel->setVisible(false);
//        m_healthBar->setVisible(false);
//        m_hollow->setVisible(false);
        
//        m_healthLabel->removeFromParentAndCleanup(true);
//        m_healthBar->removeFromParentAndCleanup(true);
//        m_hollow->removeFromParentAndCleanup(true);
    }
    // destructor virtual
}
