//
//  TMX.cpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 4/17/19.
//

#include <string>
#include <sstream>

#include "MyTMX.h"
#include "MyMacros.h"
#include  "SimpleAudioEngine.h"
#include "LabelManager.h"

#include "TileMap.h"

using namespace cocos2d;

cocos2d::Scene* MyTMX::scene(std::string tmx, Vec2 g){

    auto scene = Scene::createWithPhysics();

    auto myTmxLayer =  MyTMX::create(tmx);

    myTmxLayer -> phyWorld = scene->getPhysicsWorld();

    myTmxLayer -> m_gravity = g;

    myTmxLayer->phyWorld ->setGravity(myTmxLayer -> m_gravity);

    if (DEBUG){
        myTmxLayer->phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    }

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

    // boundry
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



    if (DEBUG) {
        drawNode = DrawNode::create();

        Color4F color(0, 1, 0, 1);
        Size winSize = Director::getInstance()->getWinSize();
        float dx = 64;
        float dy = 64;

        int cols = winSize.width / 64;
        int rows = winSize.height / 64;

        for (int i = 0; i <= rows ; i++){
            drawNode -> drawSegment(
                                    Vec2(0,dy*i),
                                    Vec2(winSize.width,dy*i),
                                    1,
                                    color);
        }


        for (int i = 0; i <= cols ; i++){
            drawNode -> drawSegment(
                                    Vec2(i*dx, 0),
                                    Vec2(i*dx, winSize.height),
                                    1,
                                    color);
        }

        LabelManager::getInstance()->setTarget(this);

        for (int x = 0; x <= winSize.width ; x=x+dx){

            for (int y = 0; y <= winSize.height ; y=y+dy){

                Vec2 p(x,y);
                drawNode -> drawPoint(p, 10, Color4F::RED);
                std::stringstream ss;
                ss << "(" << x << "," << y << ")";
                //LabelManager::getInstance()->makePerminateLabel(ss.str().c_str(), p);

                Label* l = Label::createWithBMFont(
                                                   GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL,
                                                   ss.str().c_str());
                l->setWidth( 200);
                l->setColor(Color3B::ORANGE);
                l->setAnchorPoint(Vec2(0,0));
                l->setPosition(p);
                l->setScale(1.5);
                addChild(l);

            }
        }


        addChild(drawNode,0);
    }


    // TileMap
    dsj::TileMap* tileMap;
    try {
        //tileMap = new dsj::TileMap("TMX-Cave/level0_30x16x64.tmx");
        tileMap = new dsj::TileMap("TMX-Cave/simplest.tmx");
        log("%s", tileMap->to_string().c_str());
        tileMap->render(this);
    } catch (...) {
        std::exception_ptr p = std::current_exception();
        log("Error Tile Map");
    }

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



