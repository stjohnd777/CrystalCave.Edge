//
//  SceneManager.cpp
//  AsteroidTrouble
//
//  Created by Daniel St. John on 9/1/14.
//
//

#include "SceneManager.h"
#include  "SimpleAudioEngine.h"

#include "WelcomeLayer.h"
#include "FailedLayer.h"
#include "SuccessLayer.h"
#include "OptionLayer.h"
#include "GameLayer.h"

using namespace cocos2d;

SceneManager *SceneManager::INSTANCE = NULL;

SceneManager *SceneManager::getInstance() {
    if( INSTANCE == NULL)
    {
        INSTANCE = new SceneManager();
    }
    return INSTANCE;
}


void  SceneManager::Welcome(){

    Scene *pScene = getScene(WELCOME_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}

void SceneManager::Options(){
    Scene *pScene = getScene(OPTIONS_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}


void SceneManager::Game(int level) {
    Scene *pScene = getScene(GAME_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}

void SceneManager::Failed()
{
    Scene *pScene = getScene(FAILURE_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}


void SceneManager::Success()
{
    Scene *pScene = getScene(SUCCESS_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}


void SceneManager::Exit(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

Scene*SceneManager::getScene(int layerId)
{
    setCurrentScene(layerId);
    
    Scene* theScene = NULL;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
    switch (layerId) {
        case WELCOME_LAYER:
            theScene = WelcomeLayer::scene();
            break;
        case GAME_LAYER:
            theScene =  GameLayer::scene();
            break;
        case OPTIONS_LAYER:
            theScene = OptionLayer::scene();
            break;
        case ADVANCED_OPTIONS:
            //theScene = AdvanceOptionLayer::scene();
            break;
        case FAILURE_LAYER:
            theScene =  FailedLayer::scene();
            break;

        case SUCCESS_LAYER:
            theScene =  SuccessLayer::scene();
            break;
        default:;
            theScene = WelcomeLayer::scene();
            break;
    }
    
    return theScene;
}
