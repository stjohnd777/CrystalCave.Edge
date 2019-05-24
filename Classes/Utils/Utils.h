#pragma once

#include "cocos2d.h"

#include "GameObject.h"
#include "HostileObject.h"





/**
 * A Collection of commonly needed routines
 *
 @brief General Utilitites
 */
class Utils {

public:
    
    /**
     <ul>
        <li>CC_PLATFORM_IOS</li>
        <li>CC_PLATFORM_ANDROID<li>
        <li>CC_PLATFORM_WIN32<li>
        <li>CC_PLATFORM_MAC</li>
        <li>CC_PLATFORM_LINUX</li>
     </ul>
     */
    static std::string getPlatform();
    

    /**
     Return Window Size
     */
    static cocos2d::Size getWindowSize();
    /**
     Return midpoint Window
     */
    static cocos2d::Point getMidPoint();
    

    //////////////// Random ////////////////////////
    
    /**
     Return bool random
     */
    static bool FlipCoin();
    /**
     Return random int bwtween (bottom,top)
     */
    static int getRandomIntBetweenTopBottom(int bottom, int top);
    /**
     Return random float bwtween (bottom,top)
     */
    static float getRandomFloatBetweenTopBottom(float bottom, float top);
    /**
     Return x on the scene bwtween (0,width)
     */
    static int getRandomX();
    /**
     Return y on the scene bwtween (height)
     */
    static int getRandomY();
    /**
     Return xpoint scene bwtween (0-width,0-height)
     */
    static cocos2d::Point getRandomPointOnScene();
    
    /**
     Return xpoint scene bwtween (0-width, height + 100)
     */
    static cocos2d::Point getRandomPointAboveScene();
    
    /**
     Return n random int between (floor,celling)
     */
    static std::vector<int> getRandumNumbers(int n, int floor, int celling);

    //////////////// Intesection ////////////////////////
    static cocos2d::Rect getBoundingRect(cocos2d::Sprite *s);
    
    static bool isOutOfSceneBounds(cocos2d::Sprite *s);
   
    static bool isInterscting(cocos2d::Sprite *s,cocos2d::Sprite *t);
    
    static bool isInterscting( cocos2d::Rect targetRectS ,cocos2d::Sprite *t);
    
    static bool isInterscting(cocos2d::Sprite *s,cocos2d::Rect targetRectT);
    
     //////////////// Scaling ////////////////////////
    
    static cocos2d::Node* SetSizeInPercentageScene(std::string path, float percentage);
    
    static cocos2d::Node* SetSizeInPercentageScene(cocos2d::Node* node, float percentage);
    
    
    static cocos2d::Node* setSizeInPercentageScene(std::string path, float percentageX, float percentageY);
    
    static cocos2d::Node* setSizeInPercentageScene( cocos2d::Node* node, float percentageX, float percentageY);
    
    static void  setSize(cocos2d::Node* node,float x, float y);

};

