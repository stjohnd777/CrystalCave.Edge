#include "GLVertFence.h"

#include <string>

 
//#include "Ship.h"
#include  "Utils.h"

#include "SimpleAudioEngine.h"
#include "LabelManager.h"

using namespace cocos2d;
using namespace std;


const std::string GLVertFence::IDENTITY = "GLVertFence";
const int         GLVertFence::TAG = 4663;
const int         GLVertFence::WEIGHT = 10;
const int         GLVertFence::HEALTH = 999;
const std::string GLVertFence::HIT_SOUND = "shotgun.wav";
const std::string GLVertFence::DIE_SOUND ="NA";
const std::string GLVertFence::PNG_TOP = "top.elecfence.32x32.png";
const std::string GLVertFence::PNG_BOTTOM = "top.elecfence.32x32.png";
const float       GLVertFence::SCALE = 2;

bool GLVertFence::init(int hit) {

    setHit(hit);
    
    Size winSize = Director::getInstance()->getWinSize();
    setPosition(Vec2(0,0));
    
    setPositionLine(winSize.height/2);
    setWidth(100);
    setStep(30);
    setIncreasing(true);
    setShowBoundingLines(false);
    setLength(1);
    setXTranslate(0);
    setYTranslate(0);
    setSpeedX(10);
    setSpeedY(0);
    setOn(true);
    setIsBlinking(false);
    setShowBeamOrgin(false);
    setrunFactor(1);
    setBlinkInterval(1);
    m_GameLayer = nullptr;
    m_player = nullptr;
    tempV = nullptr;
    
    return true;
}

void GLVertFence::start(Node* node ,float dt){
    

    m_GameLayer = node;
    
    Size screenSize = Director::getInstance()->getWinSize();
    
    if (showBeamOrgin) {
        
        
        top = Sprite::createWithSpriteFrameName("top.elecfence.32x32.png");
        top->setAnchorPoint(Vec2(.5,1));
        top->setZOrder(100);
        top->setScale(SCALE);
        m_GameLayer->addChild(top,1000);
 
        
        bottom = Sprite::createWithSpriteFrameName("bottom.elecfence.32x32.png");
        bottom->setZOrder(100);
        bottom->setScale(SCALE);
        m_GameLayer->addChild(bottom,1000);
        
        top->setPosition(Vec2(posLine + offsetX + getXTranslate()+getWidth()/2,getYTranslate() +screenSize.height * length-top->getContentSize().height + offsetY));
        bottom->setPosition(Vec2(posLine + offsetX + getXTranslate()+getWidth()/2,getYTranslate() +top->getContentSize().height+offsetY));
        bottom->setAnchorPoint(Vec2(.5,0));
    }
    
    m_GameLayer->addChild(this,1000);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("elec.wav", true);
    
    scheduleUpdate();

    
    if (getIsBlinking()) {
        schedule(  schedule_selector( GLVertFence::blinkUpdate ),getBlinkInterval());
    }
    
}


void GLVertFence::blinkUpdate(float dt)
{
    on = !on;
}


void GLVertFence::drawElectricFence()
{
    if ( tempV != nullptr){
        tempV->removeFromParentAndCleanup(true);
        tempV = nullptr;
    }
    
    tempV = DrawNode::create();
    addChild(tempV);
    
    Size screenSize = Director::getInstance()->getWinSize();
    
    //Node::draw();
    
    Size winSize = Director::getInstance()->getWinSize();
    float dy = winSize.height / step *length;
    
    static float random_value_from  = CCRANDOM_0_1() * getWidth() ;
    static float random_value_to  = 0;
    
    offsetX = counterX ;
    
    if (on) {
        
        for (int i = 1; i < step ; i++){

            random_value_to  = CCRANDOM_0_1()* getWidth();
            
            Color4F color(1,1* CCRANDOM_0_1(),1* CCRANDOM_0_1(),1);
            Vec2 orgin( (posLine +offsetX ) +random_value_from + getXTranslate(), (i-1)*dy +getYTranslate() + offsetY);
            Vec2 dest( (posLine +offsetX) +random_value_to + getXTranslate()   , i*dy+getYTranslate() + offsetY);

            tempV->drawSegment(orgin, dest, 1, color);
            
            random_value_from = random_value_to;
            
        }
        
        if ( getShowBeamOrgin())
        {
            top->setPosition(Vec2(posLine + offsetX + getXTranslate()+getWidth()/2,    getYTranslate() +screenSize.height * length-top->getContentSize().height + offsetY));
            bottom->setPosition(Vec2(posLine + offsetX + getXTranslate()+getWidth()/2 ,getYTranslate() +top->getContentSize().height + offsetY));
        }
        if ( getShowBoundingLines())
        {
            Color4F colorEnds(1,1,1,1);
            tempV->drawSegment(
                  Vec2( posLine + offsetX + getXTranslate(),winSize.height  * length + getYTranslate() + offsetY),
                  Vec2( posLine + offsetX  + getXTranslate(), 0+ getYTranslate()+offsetY ), 1,
                  colorEnds);
            

            
            tempV->drawSegment(
                       Vec2( posLine + offsetX + getWidth() + getXTranslate() ,winSize.height * length + getYTranslate()+offsetY  ),
                       Vec2( posLine + offsetX + getWidth()+ getXTranslate(), 0+ getYTranslate() + offsetY),
                       1,
                       colorEnds
                       );
        }
    }
    
    
    
}


 

/*
 * This method will be called periodically, gives oportunity for
 * collection detection and shutdown conditions on the level
 */

void GLVertFence::update(float dt)
{
 
    drawElectricFence();
    
    //  X (px) = v (px/sec) * t (sec);
    if ( speedX)
    {
        if ( increasing)
        {
            counterX = counterX + dt* speedX;
        } else {
            counterX = counterX - dt* speedX;
        }
        
        if ( counterX >  Utils::getWindowSize().width *runFactor)
        {
            increasing = false;
        } else if ( counterX < 0)
        {
            increasing = true;
        }
    }
    
    
    Size winSize = Director::getInstance()->getWinSize();
    
    if (getPlayer() == nullptr ){
        return;
    }
    
    collision();

    
    
    
}


void GLVertFence::collision(){
    
    Point pos = getPlayer()->getPosition();
    Size winSize = Director::getInstance()->getWinSize();
    if (on) {
        
    
        if ( pos.x > ( posLine + offsetX  ) && pos.x < ( posLine  + offsetX + getWidth())
            &&
            (pos.y > ( getYTranslate() + offsetY)) &&  ( pos.y  < ( winSize.height *length + getYTranslate() + offsetY)  )
            )
        {
            // TODO
           int hit = getHit();
           getPlayer()->takeDamage(WEIGHT);
            
            LabelManager::getInstance()->makeHitLabel(hit,pos, Color3B::RED);
            
        }
    }
}

