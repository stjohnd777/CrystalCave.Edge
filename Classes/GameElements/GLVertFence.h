#pragma once

#include "cocos2d.h"

#include "GLFence.h"
#include "GameAssets.h"
#include "MyMacros.h"
#include "GameObject.h"

//NS_DSJ_BEGIN
class GLVertFence : public cocos2d::Node {

public:
    
    //CREATE_FUNC(GLVertFence);

    bool  init() override;

public:

    ///////////////////////////////////////////////////////
    //
    //                    beamTopYPixel
    //         minXPixel  initXPixel     maxXPixel
    //
    //                     steps
    //
    //                       BE  -->increasing
    //         |     beamWidthInPixels
    //         |           |||||            |
    //         |             |              |
    //         |             |              |
    //         |             | isBlinling   |
    //         |             | blinkRateInSeconds
    //         |             |              |
    //         |             |              |
    //         |             |              |
    //                       BE
    //                       beamBottomYPixel
    //
    ///////////////////////////////////////////////////////

    static GLVertFence* create(
                int initXPixel, int minXPixel, int maxXPixel,
                int steps,
                int beamWidthInPixels,
                int beamBottomYPixel, int beamTopYPixel,
                bool isBlinling,float blinkRateInSeconds,
                bool isMoving,float speedPixelPerSecond, bool increasing,
                bool showBeamBookEnd = true,
                bool showBeamBoundry = false,
                bool isRandomColor = true,
                cocos2d::Color4F beamColor = cocos2d::Color4F::WHITE)
    {
        GLVertFence *pRet = new(std::nothrow) GLVertFence();
        if (pRet && pRet->init( initXPixel,  minXPixel,  maxXPixel,
                                steps,
                                beamWidthInPixels,
                                beamBottomYPixel,  beamTopYPixel,
                                isBlinling, blinkRateInSeconds,
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

    static GLVertFence* createWallWest(){
        cocos2d::Size size = cocos2d::Director::getInstance()->getWinSizeInPixels();

        int initXPixel = 32;
        int minXPixel = 32;
        int maxXPixel = size.width;
        int steps = 10;
        int beamWidthInPixels = 64;
        int beamBottomYPixel = 100;
        int beamTopYPixel = size.height -100;
        bool isBlinling = true;
        float blinkRateInSeconds = 3;
        bool isMoving = true;
        float speedPixelPerSecond =100;
        bool increasing = true;
        bool showBeamBookEnd = true;
        bool showBeamBoundry = false;
        bool isRandomColor = true;
        cocos2d::Color4F beamColor = cocos2d::Color4F::WHITE;

        return create(initXPixel,  minXPixel,  maxXPixel,
                       steps,
                       beamWidthInPixels,
                       beamBottomYPixel, beamTopYPixel,
                       isBlinling,blinkRateInSeconds,
                       isMoving, speedPixelPerSecond,  increasing,
                       showBeamBookEnd,
                       showBeamBoundry ,
                       isRandomColor ,
                       beamColor );

    }

    bool  init( int initXPixel, int minXPixel, int maxXPixel,
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


    ATTR(Node*, m_GameLayer, GameLayer,nullptr);

    ATTR(GameObject*, m_player, Player,nullptr);

public:

    float scaleBookends;
    
     ATTR(int ,  z, Z, 10);

    // The bottom of the beam,
    ATTR(int ,  beamTop, BeamBottom,0);

    // Top of the beam
    ATTR(int, beamBottom,BeamTop,cocos2d::Director::getInstance()->getWinSize().height);

    // The initial position of the vertical beam on the x axis
    ATTR(int ,initX , InitX,cocos2d::Director::getInstance()->getWinSize().width/2)

    // if beam is moving the max X
    ATTR(int ,  maxX , MaxX,cocos2d::Director::getInstance()->getWinSize().width)

    // if beam is moving the min Y
    ATTR(int, minX , MinX, 0);

    // The beam offset from the start position in pixels
    // [ minX, maxX]
    ATTR(int, offsetX, OffsetX,0);

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

    void start(Node* node ,float dt);
    
    void drawElectricFence();
    
    void update(float dt) override;
    
    void blinkUpdate(float dt);
    
    void collision();
    
private:

    cocos2d::DrawNode *tempV ;

    float counterX = 0;
    float counterY= 0;
    cocos2d::Sprite * top;
    cocos2d::Sprite * bottom;
    
};
//NS_DSJ_END
