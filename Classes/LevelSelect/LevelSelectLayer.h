//
//  LevelSelectLayer.hpp
//  CrystalCave.Edge-mobile
//
//  Created by St John, Daniel J on 5/28/19.
//

#pragma once

#include "cocos2d.h"

#include "BaseLayer.h"


class LevelSelectLayer : public BaseLayer {
    
public:
    
    static cocos2d::Scene* scene();
    
    static LevelSelectLayer* create()
    
    bool init();
    
protected:
    
    void NextPage();
    
    void PreviosPage();
    
};
