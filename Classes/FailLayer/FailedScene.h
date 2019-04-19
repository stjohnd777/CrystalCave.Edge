#pragma once

#include "cocos2d.h"
#include "BaseLayer.h"

class FailedScene : public BaseLayer {
    
public:
    
    static cocos2d::Scene* scene();
    
    static cocos2d::Layer* layer();
    
    CREATE_FUNC(FailedScene);
    
    bool init();
    
private:
    
    void initBackGround();
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32   || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void onMouseDown(Event *event);
    void onMouseUp(Event *event);
    void onMouseMove(Event *event);
    void onMouseScroll(Event *event);
#endif
};

