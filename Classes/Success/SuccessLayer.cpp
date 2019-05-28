
#include <string>
#include <sstream>

#include "GameAssets.h"
#include "SuccessLayer.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"


using namespace cocos2d;
using namespace CocosDenshion;

Scene* SuccessLayer::scene() {
    Scene *scene = Scene::create();
    SuccessLayer *layer = SuccessLayer::create();
    scene->addChild(layer);
    return scene;
}


bool SuccessLayer::init() {
    
    if ( ! Layer::init() ){
        return false;
    }

    Size size = Director::getInstance()->getWinSize();

    //strechBackgroundToScreen("SIFI_GUI/Window/WindowMedium.png", 0, 1);
    strechBackgroundToScreen(GameAssets::SUCCESS_BACKGROUND, 1);


    std::stringstream ss;
    ss << "Level " << GameManager::getInstance()->getLevel() <<  " Completed !! ";

    const char* font = GameAssets::Fonts::TTF::MarkerFelt;
    auto title = std::string(ss.str());
    auto* pLabel = Label::createWithTTF(title, font, 78);
    pLabel->enableShadow();
    pLabel->enableOutline(Color4B::RED);
    pLabel->setPosition( Vec2(size.width / 2,  .68 *size.height  ) );
    this->addChild(pLabel);


    auto* pTime = Label::createWithTTF("Tap to Continue to next Level", font, 42);
    pTime->enableShadow();
    pTime->enableOutline(Color4B::RED);
    pTime->setPosition( Vec2(size.width / 2,  size.height/2  ) );
    this->addChild(pTime);


    
 
    
    auto singleTouchListener = EventListenerTouchOneByOne::create();
    singleTouchListener->setSwallowTouches(true);
    singleTouchListener->onTouchBegan = CC_CALLBACK_2(SuccessLayer::onTouchBegan, this);


    getEventDispatcher()->addEventListenerWithSceneGraphPriority(singleTouchListener, this);

    return true;
}



bool SuccessLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    int lastLEvel = GameManager::getInstance()->getLevel();
    GameManager::getInstance()->setLevel(lastLEvel +1);
    SceneManager::getInstance()->Game(GameManager::getInstance()->getLevel());
    return true;
}
