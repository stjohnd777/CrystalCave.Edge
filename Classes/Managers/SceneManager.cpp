//
//  SceneManager.cpp
//  AsteroidTrouble
//
//  Created by Daniel St. John on 9/1/14.
//
//
#include "MyTMX.h"

#include <string>

#include "SceneManager.h"
#include "SoundManager.h"
#include "GameManager.h"

#include "WelcomeLayer.h"
#include "FailedLayer.h"
#include "SuccessLayer.h"
#include "OptionLayer.h"


using namespace cocos2d;

SceneManager *SceneManager::INSTANCE = NULL;

SceneManager *SceneManager::getInstance() {
    if( INSTANCE == NULL)
    {
        INSTANCE = new SceneManager();
        INSTANCE->gameManager =  GameManager::getInstance();
    }
    return INSTANCE;
}


void  SceneManager::Welcome(){
    auto pScene = WelcomeLayer::scene();
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}

void SceneManager::Options(){
    auto pScene = OptionLayer::scene();
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}


void SceneManager::Game(int level) {
    std::string tmx = gameManager->getTmx(level);
    auto pScene =  MyTMX::scene(tmx);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}

void SceneManager::Failed()
{
    Scene *pScene =FailedLayer::scene();
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}


void SceneManager::Success()
{
    Scene *pScene =  SuccessLayer::scene();
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}


void SceneManager::Exit(){
    SoundManager::bell();
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

