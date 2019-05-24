#include "Utils.h"
#include "BaseLayer.h"
#include "SceneManager.h"

using namespace cocos2d;


BaseLayer* BaseLayer::create()
{
    BaseLayer* baseLayer = new BaseLayer();
    if ( baseLayer && baseLayer->init())
    {
        baseLayer->autorelease();
    }else{
        delete baseLayer;
        baseLayer = nullptr;

    }
    return baseLayer;
}


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

void BaseLayer::initBackMenu(std::function<void (Ref*)> f ,int size){

    int windowWidth = Director::getInstance()->getWinSize().width;
    int windowHeight =  Director::getInstance()->getWinSize().height;

    auto spriteBack = Sprite::create(GameAssets::Sprite::BTN_BACK);
    Utils::setSize(spriteBack,size,size);
    auto spriteBackSel =Sprite::create(GameAssets::Sprite::BTN_BACK_SEL);
    Utils::setSize(spriteBackSel,size,size);

    auto offsetWidth = spriteBack->getContentSize().width /2;
    auto offsetHeight = spriteBack->getContentSize().height /2;

    auto backMenuItem = MenuItemSprite::create(spriteBack, spriteBackSel);

    backMenuItem->setCallback(f);

    Point pos = Vec2(offsetWidth, windowHeight - offsetHeight);

    backMenuItem->setPosition( pos );

    Menu* pMenu = Menu::create(backMenuItem, NULL);
    pMenu->setPosition( Vec2::ZERO );

    this->addChild(pMenu, 99);
}
