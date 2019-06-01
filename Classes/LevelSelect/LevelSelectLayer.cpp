//
//  LevelSelectLayer.cpp
//  CrystalCave.Edge-mobile
//
//  Created by St John, Daniel J on 5/28/19.
//

#include "LevelSelectLayer.h"

#include "GameAssets.h"
#include "Utils.h"

using namespace cocos2d;

 
//Scene* LevelSelectLayer::scene() {
//
//    Scene *scene = Scene::create();
//
//    auto *layer = LevelSelectLayer::create();
//
//    scene->addChild(layer);
//
//    return scene;
//}

//LevelSelectLayer* LevelSelectLayer::create()
//{
//    LevelSelectLayer *pRet = new(std::nothrow) LevelSelectLayer(); 
//    if (pRet && pRet->init())
//    {
//        pRet->autorelease();
//        return pRet;
//    }
//    else
//    {
//        delete pRet;
//        pRet = nullptr;
//        return nullptr;
//    }
//}

//bool LevelSelectLayer::init(){
//    
//    auto f = [](Ref* ref){
//        SceneManager::getInstance()->Welcome();
//    };
//    
//    // Back Menu
//    initBackMenu(f);
//    
//    auto size = Director::getInstance()->getWinSize();
//    
//    int divisionX = size.width /3;//m_ROW;
//    int divisionY = size.width /3;//m_Col;
//    
//    for ( int row = 0 ; row < 3 ; row ++){
//        
//        
//        for ( int col = 0 ; col < 3 ; col ++){
//            
//            Point p ( col * divisionX , size.height -  row * divisionY );
//            
//            auto levelSprite = Sprite::create(GameAssets::Sprite::LEVEL_BG);
//            levelSprite->setAnchhor(Vec2(0,1));
//            levelSprite->setPosition(p);
//            Utils::setSize(levelSprite,128,128);
//        }
//        
//    }
//    
//}
