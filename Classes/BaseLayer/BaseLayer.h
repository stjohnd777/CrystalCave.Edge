#pragma once

#include <string>
#include "cocos2d.h"
#include "GameObject.h"
#include "Constants.h"

#include <functional>

//std::function<void (Ref*)> f = [] (Ref a) { };


class BaseLayer : public cocos2d::Layer {
    
public:


    /**
     * This macro generates the create method below.
     * 1> the returned Layer is autorelease, that is 
     *    reference counted object
     */
    CREATE_FUNC(BaseLayer);
    /*
     static BaseLayer* create()
     {
         BaseLayer* baseLayer = new BaseLayer();
         if ( baseLayer && baseLayer->init())
         {
             baseLayer->autorelease();
             retrun baseLayer;
         }else{
             delete baseLayer;
             baseLayer = NULL;
             return NULL;
        }
     }
     */
    
    /*
     * From the above code we see that this is where
     * we construct our abject, this is the Objective-C
     * way.
     */
    bool init();


    CC_SYNTHESIZE(cocos2d::Sprite*, pSpriteBackground, BackgroundSprite)
    /**
    * return the screen size
    */
    CC_SYNTHESIZE(cocos2d::Size, winSize, WindowSize);
    
    /**
     * The Game Layer
     */
    CC_SYNTHESIZE(cocos2d::Layer*, m_GameLayer, GameLayer);
    /**
     * Player Game Object, Ship in Asteroids
     */
    CC_SYNTHESIZE(GameObject*, m_Player, Player);

    
    
    /**
     * Scale the image to the sceen size and place using the z-order z
     */
    void strechBackgroundToScreen(std::string path,int z);
    void strechBackgroundToScreen(std::string backgroundPath, int z, float percentage);
    
    /**
     * Back menu item in top left corner 
     */
    void initBackMenu(std::function<void (Ref*)> f  );
    
    
};
