#include "BaseLayer.h"
//#include "Constants.h"
#include "GameSceneManager.h"

using namespace cocos2d;

bool BaseLayer::init() {
    
    if (!Layer::init() )
    {
        return false;
    }
    winSize = Director::getInstance()->getWinSize();
    
    return true;
}


void BaseLayer::strechBackgroundToScreen(std::string backgroundPath, int z){

    Size size = Director::getInstance()->getWinSize();
    pSpriteBackground = Sprite::create(backgroundPath);
    if (pSpriteBackground){
        pSpriteBackground->setZOrder(0);
        float scaleX = size.width/pSpriteBackground->getContentSize().width;
        pSpriteBackground->setScaleX(scaleX);
        float scaleY = size.height/pSpriteBackground->getContentSize().height;
        pSpriteBackground->setScaleY(scaleY);
        pSpriteBackground->setPosition( Vec2(size.width/2, size.height/2) );
        pSpriteBackground->setName("BG");
        this->addChild(pSpriteBackground, 0);
    }
 
}
void BaseLayer::strechBackgroundToScreen(std::string backgroundPath, int z, float percentage){
    
    Size size = Director::getInstance()->getWinSize();
    pSpriteBackground = Sprite::create(backgroundPath);
    if (pSpriteBackground){
        pSpriteBackground->setZOrder(0);
        float scaleX = percentage *size.width/pSpriteBackground->getContentSize().width;
        pSpriteBackground->setScaleX(scaleX);
        float scaleY = percentage * size.height/pSpriteBackground->getContentSize().height;
        pSpriteBackground->setScaleY(scaleY);
        pSpriteBackground->setPosition( Vec2(size.width/2, size.height/2) );
        this->addChild(pSpriteBackground, 0);
    }
    
}


void BaseLayer::initBackMenu(std::function<void (Ref*)> f ){
    
    auto backMenuItem =
    MenuItemSprite::create(
        Sprite::create(GameAssets::Sprite::BTN_WEST),
        Sprite::create(GameAssets::Sprite::BTN_WEST));

    backMenuItem->setCallback(f);


    Point pos =
    Vec2(
         backMenuItem->getContentSize().width -40 ,
         Director::getInstance()->getWinSize().height - (backMenuItem->getContentSize().height)/2
         );

    backMenuItem->setPosition( pos );

    Menu* pMenu = Menu::create(backMenuItem, NULL);
    pMenu->setPosition( Vec2::ZERO );

    this->addChild(pMenu, 99);
}
