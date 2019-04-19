#pragma once

#include "cocos2d.h"

 

#include "GLFence.h"

class GLVertFence : public GLFence {

public:
    
    static const std::string IDENTITY;
    static const int         TAG;
    static const int         WEIGHT;
    static const int         HEALTH;
    static const std::string HIT_SOUND;
    static const std::string DIE_SOUND;
    static const std::string PNG_TOP;
    static const std::string PNG_BOTTOM;
    static const float      SCALE;
    
    
    CREATE_FUNC(GLVertFence);
    
    
    // TODO static create function with all params
    

    CC_SYNTHESIZE(bool, increasing, Increasing);
    
    bool  init(int hit = 50);

    CC_SYNTHESIZE(int, m_hit, Hit);


    CC_SYNTHESIZE(int, offsetX, OffsetX);
    
    CC_SYNTHESIZE(int, offsetY, OffsetY);
    
    CC_SYNTHESIZE(int, xTranslate, XTranslate);
    
    CC_SYNTHESIZE(int, yTranslate, YTranslate);
    
    CC_SYNTHESIZE(float, runFactor, runFactor);
    
    CC_SYNTHESIZE(bool, on, On);
    

    
    void start(Node* node ,float dt);
    
    void drawElectricFence();
    
    void update(float dt) override;
    
    void blinkUpdate(float dt);
    
 
    void collision();
    
private:

    cocos2d::DrawNode *tempV ;

    float counterX = 0;
    float counterY= 0;
    cocos2d::Sprite * top;
    cocos2d::Sprite * bottom;
    
};
