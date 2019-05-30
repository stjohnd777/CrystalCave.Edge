#pragma once

#include "cocos2d.h"
#include "BaseLayer.h"

class FailedLayer : public BaseLayer {
    
public:
    
    static cocos2d::Scene* scene();
    
    static cocos2d::Layer* layer();
    
    CREATE_FUNC(FailedLayer);
    
    bool init();
    
private:
    
    void initBackGround();
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
//    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
//    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
//    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    
#if IS_DESKTOP
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseDown(cocos2d::Event *event);
    void onMouseUp(cocos2d::Event *event);
    void onMouseMove(cocos2d::Event *event);
    void onMouseScroll(cocos2d::Event *event);
#endif
};

