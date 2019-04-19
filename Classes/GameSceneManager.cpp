//
//  GameSceneManager.cpp
//  AsteroidTrouble
//
//  Created by Daniel St. John on 9/1/14.
//
//

#include "GameSceneManager.h"
#include  "SimpleAudioEngine.h"

#include "WellcomeScene.h"
#include "FailedScene.h"
#include "OptionLayer.h"
#include "GameLayer.h"

using namespace cocos2d;

GameSceneManager *GameSceneManager::INSTANCE = NULL;

GameSceneManager *GameSceneManager::getInstance() {
    if( INSTANCE == NULL)
    {
        INSTANCE = new GameSceneManager();
    }
    return INSTANCE;
}


void  GameSceneManager::Welcome(){

    Scene *pScene = getScene(WELCOME_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}

void GameSceneManager::Options(){
    Scene *pScene = getScene(OPTIONS_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}


void GameSceneManager::Game(int level) {
    Scene *pScene = getScene(GAME_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}

void GameSceneManager::Failed()
{
    Scene *pScene = getScene(FAILURE_LAYER);
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene);
    Director::getInstance()->replaceScene(animation);
}


Scene*GameSceneManager::getScene(int layerId)
{
    setCurrentScene(layerId);
    
    Scene* theScene = NULL;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
    switch (layerId) {
        case WELCOME_LAYER:
            theScene = WellcomeScene::scene();
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
            theScene =  FailedScene::scene();
            break;
        default:;
            theScene = WellcomeScene::scene();
            break;
    }
    
    return theScene;
}
