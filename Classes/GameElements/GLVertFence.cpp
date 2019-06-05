#include "GLVertFence.h"

#include <string>


#include  "Utils.h"
#include "LabelManager.h"
#include "SoundManager.h"



using namespace cocos2d;
using namespace std;

//NS_DSJ_BEGIN

bool GLVertFence::init() {

    if ( ! Node::init()){
        return false;
    }

    Size winSize = Director::getInstance()->getWinSize();

    return true;
}

bool  GLVertFence::init( int initXPixel, int minXPixel, int maxXPixel,
                        int steps,
                        int beamWidthInPixels,
                        int beamBottomYPixel, int beamTopYPixel,
                        bool isBlinking,float blinkRateInSeconds,
                        bool isMoving,float speedPixelPerSecond, bool increasing,
                        bool showBeamBookEnd,
                        bool showBeamBoundry,
                        bool isRandomColor ,
                        Color4F beamColor) {

    if ( ! Node::init()){
        return false;
    }

    this->initX =initXPixel;
    this->minX=minXPixel;
    this-> maxX =maxXPixel;
    this-> beamWidth=beamWidthInPixels;
    this-> step  = steps;
    this-> beamBottom=beamBottomYPixel;
    this-> beamTop=beamTopYPixel;
    this-> isBlinking =isBlinking;
    this-> m_blinkInterval=blinkRateInSeconds;
    this-> isMovingBeam=isMoving;
    this-> speed = speedPixelPerSecond;
    this-> increasing=increasing;
    this-> showBeamOrgin=showBeamBookEnd;
    this-> showBoundingLines =showBeamBoundry;
    this->beamColorRandom =isRandomColor;
    this->beamColor =beamColor;

    Size winSize = Director::getInstance()->getWinSize();

    return true;

}

void GLVertFence::start(Node* node ,float dt){

    Size winSize = Director::getInstance()->getWinSize();

    m_GameLayer = node;

    Size screenSize = Director::getInstance()->getWinSize();

    if (showBeamOrgin) {

        top = Sprite::create("TMX-Cave/steelball.png");
        //top->setScale(4);
        m_GameLayer->addChild(top,1000);

        bottom = Sprite::create("TMX-Cave/steelball.png");
        //bottom->setScale(4);
        m_GameLayer->addChild(bottom,1000);

        top->setPosition
        (
         Vec2(
              initX ,
              beamTop - top->getContentSize().height
              )

         );

        bottom->setPosition(
                            Vec2(
                                 initX,
                                 beamBottom + top->getContentSize().height
                                 )

                            );
    }

    m_GameLayer->addChild(this,z);


    SoundManager::electric();
    
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
 

    static float random_value_from  = CCRANDOM_0_1() * getBeamWidth() ;
    static float random_value_to  = 0;

    offsetX = counterX ;

    if (on) {

        for (int y = beamBottom; y < beamTop ; y = y + step){

            random_value_to  = CCRANDOM_0_1() * getBeamWidth();

            Color4F _color;
            if( getBeamColorIsRamdom()) {
                _color =  Color4F(1,1* CCRANDOM_0_1(),1* CCRANDOM_0_1(),1);
            } else {
                _color = getBeamColor();
            }

            Vec2 orgin
            (
             (initX +offsetX) + random_value_from  - getBeamWidth()/2  ,
             y
             );
            Vec2 dest
            (
             (initX +offsetX) + random_value_to -getBeamWidth()/2  ,
             y+step
             );

            tempV->drawSegment(orgin, dest, 1, _color);

            random_value_from = random_value_to;

        }
    }

    if ( getShowBeamOrgin())
    {
        top->setPosition(
                         Vec2(
                              initX + offsetX ,
                              beamTop)
                         );

        bottom->setPosition(
                            Vec2(
                                 initX + offsetX  ,
                                 beamBottom)
                            );
    }

    if ( getShowBoundingLines())
    {
        Color4F colorEnds(1,1,1,1);

        tempV->drawSegment(
                           Vec2( initX + offsetX + getBeamWidth()/2 , beamTop),
                           Vec2( initX + offsetX + getBeamWidth()/2, beamBottom),
                           1,
                           colorEnds);


        tempV->drawSegment(
                           Vec2( initX + offsetX  , beamTop),
                           Vec2( initX + offsetX , beamBottom),
                           1,
                           Color4F::RED);

        tempV->drawSegment(
                           Vec2( initX + offsetX - getBeamWidth()/2 , beamTop),
                           Vec2( initX + offsetX -getBeamWidth()/2, beamBottom),
                           1,
                           colorEnds);


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
    if ( speed)
    {
        if ( increasing)
        {
            counterX = counterX + dt* speed;
        } else {
            counterX = counterX - dt* speed;
        }


        if ( (counterX + initX) >  maxX)
        {
            increasing = false;
        }
        //else if ( counterX < 0)
        else if ( (counterX + initX) < minX)
        {
            increasing = true;
        }
    }
    
    
    if (getPlayer() != nullptr && on){
        collision();
    }
    
}


void GLVertFence::collision(){
    
    Point pos = getPlayer()->getPosition();
    Rect rect(initX+offsetX-beamWidth/2,beamBottom,beamWidth,beamTop-beamBottom);

    if ( rect.containsPoint(pos) ){
        int hit = 20;
        getPlayer()->takeDamage(hit);
        LabelManager::getInstance()->makeHitLabel(hit, pos, Color3B::RED);
    }
}

//NS_DSJ_END
