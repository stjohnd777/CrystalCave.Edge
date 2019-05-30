#pragma once

#include <functional>

#include "cocos2d.h"
#include "BaseLayer.h"

class WelcomeLayer : public BaseLayer  {
    
public:
    
    static cocos2d::Scene* scene();
    
    static WelcomeLayer * create(std::string bg,std::string title);

    virtual bool init(std::string bg,std::string title);
    
private:
    void  CreateCrystalCeilingFloor();
    void  AddLighting(int n);
    void  AddLigthning(Point a,
                                    Point b,
                                    int numberBolts,
                                    int thickness,
                                    int displacement,
                                    int detail,
                                    Color4F myColor ,
                      bool isRandomColor);
    


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

    std::function<void( cocos2d::Ref* sender)> play ;
    std::function<void( cocos2d::Ref* sender)> levelSelect ;
    std::function<void( cocos2d::Ref* sender)> settings;
    std::function<void( cocos2d::Ref* sender)> exit ;
};

