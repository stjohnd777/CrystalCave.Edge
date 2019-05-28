#include "GameAssets.h"

#include "SimpleAudioEngine.h"
#include "OptionLayer.h"
#include "WelcomeLayer.h"
#include "OptionLayer.h"
#include "FailedLayer.h"

#include "SceneManager.h"


using namespace cocos2d;
using namespace CocosDenshion;

Scene* FailedLayer::scene() {
    
    Scene *scene = Scene::create();
    FailedLayer *layer = FailedLayer::create();
    scene->addChild(layer);
    
    return scene;
}

Layer* FailedLayer::layer() {
    // 'layer' is an autorelease object
    FailedLayer *layer = FailedLayer::create();
    return layer;
}


bool FailedLayer::init() {
    
    if ( ! Layer::init() ){
        return false;
    }
    
    setTag(GameAssets::TAGS::FAILED_LAYER);
    
    initBackGround();
 
    
    auto singleTouchListener = EventListenerTouchOneByOne::create();
    singleTouchListener->setSwallowTouches(true);
    singleTouchListener->onTouchBegan = CC_CALLBACK_2(FailedLayer::onTouchBegan, this);
//    singleTouchListener->onTouchMoved = CC_CALLBACK_2(FailedLayer::onTouchMoved, this);
//    singleTouchListener->onTouchEnded = CC_CALLBACK_2(FailedLayer::onTouchEnded, this);
//    singleTouchListener->onTouchCancelled = CC_CALLBACK_2(FailedLayer::onTouchCancelled, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(singleTouchListener, this);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32   || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    // mouse and keyboard listener for input
    
    setKeypadEnabled(true);
    
    auto listenerKey = EventListenerKeyboard::create();
    listenerKey->onKeyPressed = CC_CALLBACK_2(FailedLayer::onKeyPressed, this);
    listenerKey->onKeyReleased = CC_CALLBACK_2(FailedLayer::onKeyReleased , this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
    
    
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(FailedLayer::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(FailedLayer::onMouseUp, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(FailedLayer::onMouseDown, this);
    mouseListener->onMouseScroll = CC_CALLBACK_1(FailedLayer::onMouseScroll, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#endif
    
    return true;
}

void FailedLayer::initBackGround(){

    //GameOver002.png
    strechBackgroundToScreen(GameAssets::FAILED_BACKGROUND_2, 0, 1);
    strechBackgroundToScreen(GameAssets::FAILED_BACKGROUND, 2, .5);
}


bool FailedLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    SceneManager::getInstance()->Game(GameManager::getInstance()->getLevel());
    return true;
}

//void FailedLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
//}
//
//void FailedLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
//
//}
//void  FailedLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event){
//
//}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32   || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

 
void FailedLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    bool play = false;
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_ENTER:
            play = true;
            break;

        case EventKeyboard::KeyCode::KEY_X:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
            Director::getInstance()->end();
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
            #endif
            break;
    }
    if ( play){
        
        SceneManager::getInstance()->Game(GameManager::getInstance()->getLevel());
    }
}

void FailedLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}

void FailedLayer::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    Point p = Point(e->getCursorX(),e->getCursorY());

}

void FailedLayer::onMouseUp(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "Mouse Up detected, Key: ";
}

void FailedLayer::onMouseMove(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "MousePosition X:";
}

void FailedLayer::onMouseScroll(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "Mouse Scroll detected, X: ";
}
#endif



