#include "GLHorzFence.h"

#include <string>

#include "GameAssets.h"
#include "LabelManager.h"
#include "SoundManager.h"
#include "Utils.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;

//NS_DSJ_BEGIN
bool GLHorzFence::init() {

    if( !Node::init()){
        return false;
    }
    tempH = nullptr;
    
    return true;
}

bool  GLHorzFence::init( int initYPixel, int minYPixel, int maxYPixel,
           int steps,
           int beamWidthInPixels,
           int beamEastXPixel, int beamWestXPixel,
           bool isBlinking,float blinkRateInSeconds,
           bool isMoving,float speedPixelPerSecond, bool increasing,
           bool showBeamBookEnd,
           bool showBeamBoundry,
           bool isRandomColor ,
           Color4F beamColor) {

    if( !Node::init()){
        return false;
    }
    tempH = nullptr;

    this->initY =initYPixel;
    
    this->minY=minYPixel;
    this-> maxY =maxYPixel;
    
    this-> beamWidth=beamWidthInPixels;
    this-> step  = steps;
    this-> beamEast=beamEastXPixel;
    this-> beamWest=beamWestXPixel;
    this-> isBlinking =isBlinking;
    this-> m_blinkInterval=blinkRateInSeconds;
    this-> isMovingBeam=isMoving;
    this-> speed = speedPixelPerSecond;
    this-> increasing=increasing;
    this-> showBeamOrgin=showBeamBookEnd;
    this-> showBoundingLines =showBeamBoundry;
    this->beamColorRandom =isRandomColor;
    this->beamColor =beamColor;

    return true;

}

void GLHorzFence::start(Node* node ,float dt){

    
    if (showBeamOrgin) {

        west = Sprite::create(GameAssets::Sprite::STEAL_BALL);
        node->addChild(west,1000);
        auto pw =Vec2( beamWest, initY );
        west->setPosition(pw);
 
        east = Sprite::create(GameAssets::Sprite::STEAL_BALL);
        node->addChild(east,1000);
        auto pe = Vec2( beamEast  , initY );
        east->setPosition(pe);

    }
    node->addChild(this,z);
    SoundManager::electric();
    
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

    //float dx =  (winSize.width / step) * length;
    
    static float y0  = CCRANDOM_0_1() * getBeamWidth() ;
    static float y1  = 0;
    
    offsetY = counter ;
    
    /*
     * If the electric fence is off do not draw the OpenGL
     * commands
     */
    if (isElectricFenceOn) {
        for (int x = beamEast; x < beamWest ; x = x + step ){
            
            float x0 = x ;
            float x1 = x + step ;
            
            y1 = CCRANDOM_0_1() * getBeamWidth() ;
            
            Vec2 origin      = Vec2(x0  , (initY + offsetY) + y0  -getBeamWidth()/2);
            Vec2 destination = Vec2(x1  , (initY + offsetY) + y1  -getBeamWidth()/2 );
            

            Color4F _color;
            if( getBeamColorIsRamdom()) {
                _color =  Color4F(1,1* CCRANDOM_0_1(),1* CCRANDOM_0_1(),1);
            } else {
                _color = getBeamColor();
            }

            tempH->drawSegment(origin, destination, 1, _color);
           
            y0 = y1;

        }
    }

    /*
     * Show the bean bookends if true
     */
    if ( getShowBeamOrgin()){
        
        east->setPosition(
            Vec2(
                beamEast,
                initY + offsetY
                )
        );

        west->setPosition(
            Vec2(
                 beamWest,
                 initY + offsetY
                 )
            );
    }
    
    
    if ( getShowBoundingLines())
    {

        Color4F color = Color4F::WHITE;
        

        tempH->drawSegment(
                   Vec2(beamEast, initY + offsetY),
                   Vec2(beamWest, initY+ offsetY),
                    1,
                    Color4F::RED
                   );

        tempH->drawSegment(
                           Vec2(beamEast, initY + offsetY - getBeamWidth()/2),
                           Vec2(beamWest, initY + offsetY- getBeamWidth()/2),
                           1,
                           color
                           );

        tempH->drawSegment(
                           Vec2(beamEast, initY + offsetY +getBeamWidth()/2),
                           Vec2(beamWest, initY+  offsetY +getBeamWidth()/2),
                           1,
                           color
                           );


    }


}


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
    if ( (initY +counter )>  maxY  )
    {
        increasing = false;
    } else if ( (initY +counter ) < minY)
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

    Point pos = getPlayer()->getPosition();
    Rect rect(beamEast, initY+offsetY-beamWidth/2, beamWest-beamEast, beamWidth);
    if ( rect.containsPoint(pos) ){
        int hit = 20;
        getPlayer()->takeDamage(hit);
        LabelManager::getInstance()->makeHitLabel(hit, pos, Color3B::RED);
    }
}
//NS_DSJ_END
    
