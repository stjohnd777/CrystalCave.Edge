//
//  GLFence.h
//  AsteroidTrouble.cocos2dx.3.2
//
//  Created by Daniel St. John on 5/7/15.
//
//
#pragma once

#include "cocos2d.h"
#include "GameObject.h"

class GLFence : public  cocos2d::Node{

    
    CC_SYNTHESIZE(Node*, m_GameLayer, GameLayer);
    
    CC_SYNTHESIZE(GameObject*, m_player, Player);
    
    
    /*
     * This value determines a line y=posLne, and this posLine
     * is the centers od the horzonal fence, that is posLine + width/2
     * and posLine - width / 2 are the max, min extents of the fence
     */
    CC_SYNTHESIZE(int, posLine, PositionLine);
    
    /**
     * The number of points in the fences length to compute
     * subline, for example if lenght is 1 = > 100%  and the
     * ipad retina is 2056 width in pixels, and setp it 250, the
     * we have 250 subsection on the in the fence
     */
    CC_SYNTHESIZE(int, step, Step);
    
    /*
     * The width of the fences in pixels
     */
    CC_SYNTHESIZE(float, width, Width);
    
    
    /*
     * This determins the lenght of the fence as a percentage of
     * the scene with
     */
    CC_SYNTHESIZE(float, length, Length);
    
    /*
     * For a moving fence the percetage of the scene height to move.
     * so .5 will move the fence .5 * winSize.height
     */
    CC_SYNTHESIZE(float, runFactor, runFactor);
    
    /*
     * The natural direction for a moving fence is inline with
     * corrdinate sytems if true, otherwise reversed
     */
    CC_SYNTHESIZE(bool, increasing, Increasing);
    
    
    
    /*
     * Determins how fast the fence is moving if at all
     */
    CC_SYNTHESIZE(float, speed, Speed);
    CC_SYNTHESIZE(float, speedX, SpeedX);
    CC_SYNTHESIZE(float, speedY, SpeedY);

    
    /**
     * If true the electric fence is set to blink on and off
     * otherwise the fence is constant
     */
    CC_SYNTHESIZE(bool, isBlinking, IsBlinking);
    
    /**
     * The delay between turning fence on and off
     */
    CC_SYNTHESIZE(float, m_blinkInterval, BlinkInterval);
    
    /**
     * Show sprite bookends as orgins
     */
    CC_SYNTHESIZE(bool, showBeamOrgin, ShowBeamOrgin);
    
    /*
     * If true draw guide line about the fences boundy otherwise
     * do not. This allows one to visualize the Horiantal fence
     * as a rectangle
     */
    CC_SYNTHESIZE(bool, showBoundingLines, ShowBoundingLines);
    
    
    /**
     * Used when fence is blinking on/off
     * true is the electric fence is on else false
     *
     */
    CC_SYNTHESIZE(bool, isElectricFenceOn, IsElectricFenceOn);
    
    
    
    
    /**
     * Generic move object to point p in time dt in straigh line
     */
    virtual void move(cocos2d::Point p,float dt) {};
    
    /**
     * Take Damage
     */
    virtual void hit(int weight) {};
    
    /**
     * injured behavior optional, like a limping ship, and
     * give default of nothing
     */
    virtual void injured() {};
    
    /**
     * Object do you death sequence
     */
    virtual void die() {};
};
