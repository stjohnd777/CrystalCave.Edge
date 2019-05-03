//
//  TMX.cpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 4/17/19.
//

#include "MyTMX.h"
#include "MyMacros.h"
#include  "SimpleAudioEngine.h"


using namespace cocos2d;

cocos2d::Scene* MyTMX::scene(std::string tmx, Vec2 g){

    auto scene = Scene::createWithPhysics();

    auto myTmxLayer =  MyTMX::create(tmx);

    myTmxLayer -> phyWorld = scene->getPhysicsWorld();

    myTmxLayer -> m_gravity = g;

    myTmxLayer->phyWorld ->setGravity(myTmxLayer -> m_gravity);

    myTmxLayer->phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    scene->addChild(myTmxLayer);

    //LabelManager::getInstance()->setTarget(layer);

    return scene;
}

MyTMX* MyTMX::create(std::string tmx)
{
    MyTMX *pRet = new(std::nothrow) MyTMX();

    if (pRet && pRet->init(tmx))
    {
        pRet -> tmxFileName = tmx;

        pRet->autorelease();

    }
    else
    {
        delete pRet;
        pRet = nullptr;

    }
    return pRet;
}


#include  <sstream>
#include "external/tinyxml2/tinyxml2.h"
#include "Utils.h"

//#include "LunarModule.h"
//#include "HudLayer.h"
//#include "CtrlLayer.h"

bool MyTMX::init(std::string tmx) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(GameAssets::Sound::GAME_BACKGROUND_SOUND, true);

    auto size = Director::getInstance()->getWinSize();
    PhysicsMaterial material(1.0f,1.0f,1.0f);
    float border = 5;
    PhysicsBody* boundry = PhysicsBody::createEdgeBox( size,   material,  border, Vec2(size.width/2,size.height/2));

    setPhysicsBody(boundry);

    // Player
    ship = LunarModule::create();
    ship->setGameLayer(this);
    ship->useHealthLabel();
    ship->useInfoLabel();
    ship->setPosition(Utils::getMidPoint());
    ship->getPhysicsBody()->setRotationEnable(false);
    ship->setGameLayer(this);
    //Follow* follow = Follow::create(ship);
    //this->runAction(follow);
    addChild(ship,99);

    // HUD
    m_HudLayer =  HudLayer::create();
    m_HudLayer->setShip(ship);
    m_HudLayer->setGameLayer(this);
    addChild(m_HudLayer,1000);
    //m_HudLayer->startTracking();

    // CTRL
    m_CtrlLayer =  CtrlLayer::create();
    m_CtrlLayer->setShip(ship);
    m_CtrlLayer->setGameLayer(this);
    addChild(m_CtrlLayer,3000);

#if IS_DESKTOP
    // Key listener
    setKeypadEnabled(true);
    auto listenerKey = EventListenerKeyboard::create();
    listenerKey->onKeyPressed = CC_CALLBACK_2(MyTMX::onKeyPressed, this);
    listenerKey->onKeyReleased = CC_CALLBACK_2(MyTMX::onKeyReleased , this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
#endif

    return true;
}

#if IS_DESKTOP
void MyTMX::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
    gkeyCode = keyCode;
    m_IsTouching = !m_IsTouching;
    isKeyDown = true;

    float percentThrust =  m_CtrlLayer->getThrustPercentage();

    log("thrust %f", percentThrust);

    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            ship->applyThrush(Vec2(-1,0), percentThrust);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            ship->applyThrush(Vec2(1,0),percentThrust);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            ship->applyThrush(Vec2(0,-1),  percentThrust);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            ship->applyThrush(Vec2(0,1), percentThrust);
            break;

        case EventKeyboard::KeyCode::KEY_1:
        case EventKeyboard::KeyCode::KEY_Q:
        case EventKeyboard::KeyCode::KEY_KP_MINUS:
            m_CtrlLayer->setThrust(m_CtrlLayer->getThrust() - 1 ) ;
            break;
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_2:
        case EventKeyboard::KeyCode::KEY_KP_PLUS:
            m_CtrlLayer->setThrust(m_CtrlLayer->getThrust() + 1 ) ;


        case EventKeyboard::KeyCode::KEY_ESCAPE:
            if (Director::getInstance()->isPaused()){
                Director::getInstance()->resume();
            }else {
                Director::getInstance()->pause();
            }
            break;

        case EventKeyboard::KeyCode::KEY_X:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
            Director::getInstance()->end();
            break;
    }
}
#endif

MyTMX::MyTMX(){

}



