#include "Constants.h"

#include "SimpleAudioEngine.h"
#include "OptionLayer.h"
#include "WellcomeScene.h"
#include "OptionLayer.h"
#include "FailedScene.h"
#include "GameLayer.h"

#include "GameSceneManager.h"


using namespace cocos2d;
using namespace CocosDenshion;

Scene* FailedScene::scene() {
    
    Scene *scene = Scene::create();
    FailedScene *layer = FailedScene::create();
    scene->addChild(layer);
    
    return scene;
}

Layer* FailedScene::layer() {
    // 'layer' is an autorelease object
    FailedScene *layer = FailedScene::create();
    return layer;
}


bool FailedScene::init() {
    
    if ( ! Layer::init() ){
        return false;
    }
    
    setTag(GameAssets::Layer::TAG_FAILED_LAYER);
    
    initBackGround();
 
    
    auto singleTouchListener = EventListenerTouchOneByOne::create();
    singleTouchListener->setSwallowTouches(true);
    singleTouchListener->onTouchBegan = CC_CALLBACK_2(FailedScene::onTouchBegan, this);
    singleTouchListener->onTouchMoved = CC_CALLBACK_2(FailedScene::onTouchMoved, this);
    singleTouchListener->onTouchEnded = CC_CALLBACK_2(FailedScene::onTouchEnded, this);
    singleTouchListener->onTouchCancelled = CC_CALLBACK_2(FailedScene::onTouchCancelled, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(singleTouchListener, this);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32   || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    // mouse and keyboard listener for input
    
    setKeypadEnabled(true);
    
    auto listenerKey = EventListenerKeyboard::create();
    listenerKey->onKeyPressed = CC_CALLBACK_2(FailedScene::onKeyPressed, this);
    listenerKey->onKeyReleased = CC_CALLBACK_2(FailedScene::onKeyReleased , this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
    
    
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(FailedScene::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(FailedScene::onMouseUp, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(FailedScene::onMouseDown, this);
    mouseListener->onMouseScroll = CC_CALLBACK_1(FailedScene::onMouseScroll, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#endif
    
    return true;
}

void FailedScene::initBackGround(){
    
    strechBackgroundToScreen(GameAssets::Backgrounds::FAILED_BACKGROUND, 0);
 
    
}


bool FailedScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Scene *pScene =GameLayer::scene();
    TransitionCrossFade *animation = TransitionCrossFade::create(.5,  pScene);
    Director::getInstance()->replaceScene(pScene);
    //Director::getInstance()->replaceScene(animation);
    //GameSceneManager::getInstance()->showGameLayer(0);
    return true;
}

void FailedScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
}

void FailedScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
 
}
void  FailedScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event){
  
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32   || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

 
void FailedScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
        Scene* scene = GameLayer::scene();
        TransitionCrossFade *animation = TransitionCrossFade::create(.5,  scene);
        Director::getInstance()->replaceScene(animation);
        Director::getInstance()->replaceScene(animation);
    }
}

void FailedScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}

void FailedScene::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    Point p = Point(e->getCursorX(),e->getCursorY());

}

void FailedScene::onMouseUp(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "Mouse Up detected, Key: ";
}

void FailedScene::onMouseMove(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "MousePosition X:";
}

void FailedScene::onMouseScroll(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "Mouse Scroll detected, X: ";
}
#endif



