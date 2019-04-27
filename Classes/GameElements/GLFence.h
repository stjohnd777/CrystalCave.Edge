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

//NS_DSJ_BEGIN
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
     * we have setp subsection on the in the fence
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
     * For a moving fence the percetage of the scene width to move.
     * so .5 will move the fence .5 * winSize.width
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

};
//NS_DSJ_END
