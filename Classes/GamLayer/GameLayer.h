#pragma once

#include <string>
#include <sstream>

#include "cocos2d.h"

#include "MyMacros.h"
#include "BaseLayer.h"
#include "LunarModule.h"
#include "HudLayer.h"
#include "CtrlLayer.h"


class HudLayer;

class GameLayer : public BaseLayer{
    
public:
    
    static GameLayer* INSTANCE;
    
    static GameLayer* getInstance() {
        return INSTANCE;
    }

    static cocos2d::Scene* scene();

    static GameLayer* create();

public:

    GameLayer();
    
    bool init() override;

private:

    void CreateCrystalCeilingFloor();

    void CreateMineField();

    void CreateCrystalObsticals();

    void AddLighting();

    void AddElectricFrences();

    void CreateWallOnLeft();

    void AddFinishLine();


    void  AddVerticalElectricFence(int posLine ,
                                   float percentLen,
                                   float blinkRate ,
                                   float percentageRun ,
                                   float speedRun );

    void  AddLigthning(Point a,
                       Point b,
                       int numberBolts,
                       int thickness,
                       int displacement,
                       int detail,
                       Color4F myColor ,
                       bool isRandomColor);

    void AddMine();

    
private:

    int lenghts;

    Sprite* finsh ;

    int  currentLevel = 1;

    bool isCompeletedLevel;

    bool isKeyDown = true;

    EventKeyboard::KeyCode gkeyCode ;

    char buffer[64] ;

    bool m_IsTouching;

    Point m_LocationOfTouch;

    int percentage;

    CC_SYNTHESIZE (std::string ,BACKGROUND , Background);
    
    CC_SYNTHESIZE(LunarModule* ,ship ,Ship);
    CC_SYNTHESIZE(CtrlLayer * ,m_CtrlLayer,CtrlLayer);
    CC_SYNTHESIZE(HudLayer * ,m_HudLayer,HudLayer);


    CC_SYNTHESIZE(cocos2d::Vec2, m_gravity, Gravity);
    CC_SYNTHESIZE(cocos2d::PhysicsWorld*, mWorld,_PhysicsWorld);


    void initBackground();
    
    void initControlLayer();
    
    void initPlayer();
    
    void initHud() ;
    
    
    void setPhysicsWorld(cocos2d::PhysicsWorld* world)
    {
        mWorld = world;
        mWorld->setGravity(m_gravity);
    }

public:

    void thrust(float dt) ;
    
    void update(float dt) override ;
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    
#if IS_DESKTOP
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void onMouseDown(Event *event);
    void onMouseUp(Event *event);
    void onMouseMove(Event *event);
    void onMouseScroll(Event *event);
#endif

    bool canEnterFinishedProcess = true;
    bool canEnterDiedProcess = true;
};
