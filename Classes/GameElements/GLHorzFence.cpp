#include "GLHorzFence.h"

#include <string>

 
//#include "Ship.h"
#include "Utils.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;


bool GLHorzFence::init(int hit) {

    setHit(hit);

    Size winSize = Director::getInstance()->getWinSize();
    
 
    setAnchorPoint(Vec2(.5,.5));
    setPositionLine(winSize.height/2);
    
    setWidth(100);
    setStep(30);
    setIncreasing(true);
    setLength(1);
    setXTranslate(0);
    setYTranslate(0);
    setSpeed(10);
    setIsElectricFenceOn(true);
    setrunFactor(1);
    
    m_GameLayer = nullptr;
    m_player = nullptr;
 
    
    tempH = nullptr;
    
    //setPosition(Utils::getMidPoint());
    
    return true;
}

void GLHorzFence::start(Node* node ,float dt){
    
    Size winSize = Director::getInstance()->getWinSizeInPixels();
    
    if (showBeamOrgin) {
        
        int lengthOfHorzFenceInPixels =  winSize.width*length;
        int scale = 2;
        
        west = CCSprite::createWithSpriteFrameName("west.elecfence.32x32.png");
        west->setScale(scale);
        addChild(west,99);
        auto pw =Vec2(  -scale*west->getContentSize().width + offset + lengthOfHorzFenceInPixels , getPositionLine()+ getWidth()/2 );
        west->setPosition(pw);
        
        east = CCSprite::createWithSpriteFrameName("east.elecfence.32x32.png");
        east->setScale(2);
        addChild(east,99);
        auto pe = Vec2( scale*west->getContentSize().width + offset   , getPositionLine()+ getWidth()/2 );
        east->setPosition(pe);
     
    }
    node->addChild(this);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("elec.wav", true);
    
    scheduleUpdate();

    if (isBlinking) {
        schedule(  schedule_selector( GLHorzFence::blinkUpdate ),getBlinkInterval());
    }
}


void GLHorzFence::drawElectricFence()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    if ( tempH != nullptr){
        tempH->removeFromParentAndCleanup(true);
        tempH = nullptr;
    }
    
    tempH = DrawNode::create();
    addChild(tempH);
    
    
    
    float dx =  (winSize.width / step) * length;
    
    static float y0  = CCRANDOM_0_1() * getWidth() ;
    static float y1  = 0;
    
    offset = counter ;
    
    /*
     * If the electric fence is off do not draw the OpenGL
     * commands
     */
    if (isElectricFenceOn) {
        for (int i = 1; i < step ; i++){
            
            float x0 = (i-1)*dx;
            float x1 = i*dx;
            
            y1 = CCRANDOM_0_1() * getWidth() ;
            
            Vec2 origin      = Vec2(x0 + getXTranslate(), (posLine + offset) + y0 + getYTranslate() );
            Vec2 destination = Vec2(x1 + getXTranslate(), (posLine + offset) + y1 + getYTranslate() );
            
            Color4F color(1,CCRANDOM_0_1(),CCRANDOM_0_1(),1);
            
            tempH->drawSegment(origin, destination, 1, color);
           
            y0 = y1;

        }
    }
    
    /*
     * Show the bean bookends if true
     */
    if ( getShowBeamOrgin()){
        
        east->setPosition(Vec2(-west->getContentSize().width + getXTranslate()                         ,  getPositionLine()+ getWidth()/2 +  offset));
        west->setPosition(Vec2( west->getContentSize().width + getXTranslate() + winSize.width*length  ,  getPositionLine()+ getWidth()/2 +  offset ));
    }
    
    
    if ( getShowBoundingLines())
    {

        Color4F color(1,1,1,1);
        
        // Bottom Line
        tempH->drawSegment(
                   Vec2(0+getXTranslate(),                        posLine + offset + getYTranslate()) ,
                   Vec2(winSize.width * length + getXTranslate(), posLine + offset + getYTranslate()),
                           1,
                          color
                   );
        // top Line
        tempH->drawSegment(
                   Vec2(0+getXTranslate(),                        posLine + offset +  getYTranslate() + getWidth()),
                   Vec2(winSize.width * length + getXTranslate(), posLine + offset +  getYTranslate() + getWidth()),
                           1,
                           color
                   );
    }
}

#include "LabelManager.h"
/*
 * This method will be called periodically, gives oportunity for
 * collection detection and shutdown conditions on the level
 */

void GLHorzFence::update(float dt)
{
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("elec.wav", true);
   
    drawElectricFence();
    
    if ( increasing)
    {
        counter = counter + dt* speed;
    } else {
        counter = counter - dt* speed;
    }
    
    /*
     * Since counter started at 0 we move the line back to
     * where it started
     */
    if ( abs(counter) >  Utils::getWindowSize().height * runFactor  )
    {
        increasing = false;
    } else if ( counter < 0)
    {
        increasing = true;
    }
    
 
    
    if (isElectricFenceOn) {
 
        if (getPlayer() == nullptr){
            return;
        }
        collision();
    }
    
}

void GLHorzFence::blinkUpdate(float dt)
{
    isElectricFenceOn = !isElectricFenceOn;
}



void GLHorzFence::collision(){
    
    Size winSize = Director::getInstance()->getWinSize();
    
    Point pos = getPlayer()->getPosition();// Ship::getInstance()->getPosition();
    
    if ( ( pos.y > ( posLine  + offset ) ) && (pos.y < ( posLine + getWidth() + offset ) )
        &&
        (pos.x > getXTranslate() ) &&  ( pos.x  < ( winSize.width *length + getXTranslate() ) )
        )
        
    {
        // TODO

        getPlayer()->takeDamage(getHit());
        LabelManager::getInstance()->makeHitLabel(getHit(), pos, Color3B::RED);
        
    }
}
    
