//
//  LevelSelectLayer.cpp
//  CrystalCave.Edge-mobile
//
//  Created by St John, Daniel J on 5/28/19.
//

#include "LevelSelectLayer.h"



static LevelSelectLayer* create()
{
    LevelSelectLayer *pRet = new(std::nothrow) LevelSelectLayer(); \
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool LevelSelectLayer::init(){
    
    auto f = [](Ref* ref){
        SceneManager::getInstance()->Welcome();
    };
    
    // Back Menu
    initBackMenu(f);
    
    
}
