#pragma once

#include <stdio.h>

#include "BaseLayer.h"

#include "ui/CocosGUI.h"

#include "LunarModule.h"

class CtrlLayer : public BaseLayer{

public:

    static cocos2d::Scene* scene();

    static CtrlLayer* create();
    
    CC_SYNTHESIZE(LunarModule* ,m_ship ,Ship);
    
    bool init() override;

    int getThrust();

    void setThrust(int num);

    float getThrustPercentage();

private:

    char buffer[64] = {0};

    int m_ThrusterIntPercentage = 50;

    cocos2d::Label* m_LabelThrust;

    ui::Slider* m_slider;

    cocos2d::Sprite* finsh ;

    cocos2d::Sprite* sprite ;
    
    void initControlLayer();
};


