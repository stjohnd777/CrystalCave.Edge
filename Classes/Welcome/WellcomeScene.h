#pragma once

#include "cocos2d.h"
#include "BaseLayer.h"

class WellcomeScene : public BaseLayer  {
    
public:
    
    static cocos2d::Scene* scene();
    
    static WellcomeScene* create(std::string bg,std::string title);

    virtual bool init(std::string bg,std::string title);
    
private:
    
    void initLabels();
    void initMenu();

#if IS_DESKTOP
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void onMouseDown(Event *event);
    void onMouseUp(Event *event);
    void onMouseMove(Event *event);
    void onMouseScroll(Event *event);

    void keyListener();
#endif

    std::string titleLabelString ;
    std::string backGroundImage ;

    function<void( cocos2d::Ref* sender)> play ;
    function<void( cocos2d::Ref* sender)> settings;
    function<void( cocos2d::Ref* sender)> exit ;
};

