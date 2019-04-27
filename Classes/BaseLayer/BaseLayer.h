#pragma once

#include <string>
#include "cocos2d.h"
#include "GameObject.h"
#include "GameAssets.h"

#include <functional>

//std::function<void (Ref*)> f = [] (Ref a) { };


class BaseLayer : public cocos2d::Layer {
    
public:


    static BaseLayer* create();

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
