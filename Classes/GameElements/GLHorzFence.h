#pragma once

#include "cocos2d.h"
#include "GLFence.h"

#include "GameAssets.h"
#include "MyMacros.h"
#include "GameObject.h"
/*
 maxY    -----------------
 
 initY   {---------------} beamwidth |

 minY    ------------------
 
 */



//NS_DSJ_BEGIN
class GLHorzFence : public  cocos2d::Node {

private:
    float counter = 0;
    cocos2d::Sprite * west;
    cocos2d::Sprite * east;

public:
    
    CREATE_FUNC(GLHorzFence);
    
    bool  init() override;

public:

    static GLHorzFence* create(
                               int initYPixel, int minYPixel, int maxYPixel,
                               int steps,
                               int beamWidthInPixels,
                               int beamEastXPixel, int beamWestXPixel,
                               bool isBlinking,float blinkRateInSeconds,
                               bool isMoving,float speedPixelPerSecond, bool increasing,
                               bool showBeamBookEnd,
                               bool showBeamBoundry,
                               bool isRandomColor = true,
                               cocos2d::Color4F beamColor = cocos2d::Color4F::WHITE)
    {
        GLHorzFence *pRet = new(std::nothrow) GLHorzFence();
        if (pRet && pRet->init( initYPixel,  minYPixel,  maxYPixel,
                               steps,
                               beamWidthInPixels,
                               beamEastXPixel,  beamWestXPixel,
                               isBlinking, blinkRateInSeconds,
                               isMoving, speedPixelPerSecond,  increasing,
                               showBeamBookEnd,
                               showBeamBoundry,
                               isRandomColor,beamColor))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }

    bool  init(
               int initYPixel, int minYPixel, int maxYPixel,
               int steps,
               int beamWidthInPixels,
               int beamBottomYPixel, int beamTopYPixel,
               bool isBlinking,float blinkRateInSeconds,
               bool isMoving,float speedPixelPerSecond, bool increasing,
               bool showBeamBookEnd,
               bool showBeamBoundry,
               bool isRandomColor ,
               cocos2d::Color4F beamColor) ;
public:

    ATTR(cocos2d::Node*, m_GameLayer, GameLayer,nullptr);

    ATTR(GameObject*, m_player, Player,nullptr);

public:

    float scaleBookends;
    
    ATTR(int ,  z, Z, 10);

    // The bottom of the beam,
    ATTR(int ,  beamEast, BeamEast,0);

    // Top of the beam
    ATTR(int, beamWest,BeamWest,cocos2d::Director::getInstance()->getWinSize().width);

    // The initial position of the vertical beam on the x axis
    ATTR(int ,initY , InitY,cocos2d::Director::getInstance()->getWinSize().height/2)

    // if beam is moving the max X
    ATTR(int ,  maxY , MaxY,cocos2d::Director::getInstance()->getWinSize().height)

    // if beam is moving the min Y
    ATTR(int, minY , MinY, 0);

    // The beam offset from the start position in pixels
    // [ minX, maxX]
    ATTR(int, offsetY, OffsetY,0);

    /**
     * we have setp subsection on the in the fence
     */
    ATTR(int, step, Step, 30);

    /*
     * The width of the fence in pixels about the posiiton
     */
    ATTR(float, beamWidth, BeamWidth,100);


    /*
     * Is the beam moving
     */
    ATTR(bool, isMovingBeam,IsMovingBeam,false);

    /*
     * The natural direction for a moving fence is inline with
     * corrdinate sytems if true, otherwise reversed
     */
    ATTR(bool, increasing, Increasing,true);

    /*
     * Determins how fast the fence is moving if at all
     */
    ATTR(float, speed, Speed,100);


    /**
     * If true the electric fence is set to blink on and off
     * otherwise the fence is constant
     */
    ATTR(bool, isBlinking, IsBlinking,false);

    /**
     * The delay between turning fence on and off
     */
    ATTR(float, m_blinkInterval, BlinkInterval,1);

    /**
     * Show sprite bookends as orgins
     */
    ATTR(bool, showBeamOrgin, ShowBeamOrgin,true);

    ATTR(bool, beamColorRandom, BeamColorIsRamdom, true);

    ATTR(cocos2d::Color4F, beamColor, BeamColor, cocos2d::Color4F::RED);

    /*
     * If true draw guide line about the fences boundy otherwise
     * do not. This allows one to visualize the Horiantal fence
     * as a rectangle
     */
    ATTR(bool, showBoundingLines, ShowBoundingLines,false);

    ATTR(cocos2d::Size ,winSize, WinSize,cocos2d::Director::getInstance()->getWinSize())

    /**
     * Used when fence is blinking on/off
     * true is the electric fence is on else false
     *
     */
    ATTR(bool, isElectricFenceOn, IsElectricFenceOn,true);
    
    ATTR(bool, on, On,true);

public:
    
    void start(cocos2d::Node* node , float dt );
    
    virtual void drawElectricFence();
    
    void update(float dt) override;

    void blinkUpdate(float dt);
 
    void collision();
    
    
private:
    
    cocos2d::DrawNode *tempH ;
};
//NS_DSJ_END
