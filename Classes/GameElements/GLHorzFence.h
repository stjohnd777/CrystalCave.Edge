#pragma once

#include "cocos2d.h"
#include "GLFence.h"

class GLHorzFence : public GLFence {

private:
    float counter = 0;
    cocos2d::Sprite * west;
    cocos2d::Sprite * east;
public:
    
    CREATE_FUNC(GLHorzFence);
    
    bool  init(int hit = 50);

    CC_SYNTHESIZE(int, m_hit, Hit);

    CC_SYNTHESIZE(int, offset, Offset);
    
    CC_SYNTHESIZE(int, xTranslate, XTranslate);
    
    CC_SYNTHESIZE(int, yTranslate, YTranslate);

    
    void start(cocos2d::Node* node , float dt );
    
    virtual void drawElectricFence();
    
    void update(float dt) override;

    void blinkUpdate(float dt);
 
    void collision();
    
    
private:
    
    cocos2d::DrawNode *tempH ;
};
