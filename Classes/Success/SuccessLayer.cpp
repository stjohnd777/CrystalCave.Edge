//
//  SuccessLayer.cpp
//  CrystalCave.c2dx.2.8
//
//  Created by Daniel St. John on 9/28/15.
//
//

#include "SuccessLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
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
    strechBackgroundToScreen("SIFI_GUI/Window/WindowMedium.png", 0, 1);
    strechBackgroundToScreen("Success.jpeg", 1, .25);
 
    
    auto singleTouchListener = EventListenerTouchOneByOne::create();
    singleTouchListener->setSwallowTouches(true);
    singleTouchListener->onTouchBegan = CC_CALLBACK_2(SuccessLayer::onTouchBegan, this);

//    singleTouchListener->onTouchMoved = CC_CALLBACK_2(SuccessLayer::onTouchMoved, this);
//
//    singleTouchListener->onTouchEnded = CC_CALLBACK_2(SuccessLayer::onTouchEnded, this);
//
//    singleTouchListener->onTouchCancelled = CC_CALLBACK_2(SuccessLayer::onTouchCancelled, this);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(singleTouchListener, this);

    return true;
}



bool SuccessLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    SceneManager::getInstance()->Game(GameLayer::level);
    return true;
}

//void SuccessLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
//}
//
//void SuccessLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
//
//}
//void  SuccessLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event){
//
//}
