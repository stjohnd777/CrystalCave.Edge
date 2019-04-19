#pragma once

#include "cocos2d.h"

#include "GameObject.h"
#include "TargetObject.h"





/**
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
    
    static const char*  const platformString();
    
    /**
     Return
     */
    static cocos2d::Size getWindowSize();
    
    static cocos2d::Point getMidPoint();
    

    //////////////// Random ////////////////////////
    
    static int getRandomIntBetweenTopBottom(int bottom, int top);
    
    static float getRandomFloatBetweenTopBottom(float bottom, float top);
    
    static int getRandomX();
    
    static int getRandomY();
    
    static cocos2d::Point getRandomPointOnScene();
    
    static cocos2d::Point getRandomPointAboveScene();
    
    // rest call to random.org
    static std::vector<int> getRandumNumbers(int n, int floor, int celling);

    
     //////////////// Intesection ////////////////////////
    static cocos2d::Rect getBoundingRect(cocos2d::Sprite *s);
    
    static bool isOutOfSceneBounds(cocos2d::Sprite *s);
   
    static bool isInterscting(cocos2d::Sprite *s,cocos2d::Sprite *t);
    
    static bool isInterscting( cocos2d::Rect targetRectS ,cocos2d::Sprite *t);
    
    static bool isInterscting(cocos2d::Sprite *s,cocos2d::Rect targetRectT);
    

    // device introspection
    static void deviceInfo() ;
    

    //////////////// HTML View ////////////////////////

    static void displayHtmlPage(std::string uri){};
    
    static void removeHtmlPage(){};
    
};

