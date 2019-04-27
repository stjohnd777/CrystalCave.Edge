//
//  SuccessLayer.hpp
//  CrystalCave.c2dx.2.8
//
//  Created by Daniel St. John on 9/28/15.
//
//

#pragma once

#include "BaseLayer.h"

class SuccessLayer : public BaseLayer{
    
public:
    
    static cocos2d::Scene* scene();
    
    CREATE_FUNC(SuccessLayer);
    
    bool init() override;
    
    CC_SYNTHESIZE(char*, background, Backgound);
    
private:
    

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;

//    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
//    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
//    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

};


