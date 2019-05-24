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
#include "SimpleAudioEngine.h"
#include "LabelManager.h"
#include "SceneManager.h"
#include "GameElementsFactory.h"

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


    Size size = Director::getInstance()->getWinSize();
    auto pSpriteBackground = Sprite::create("game.png");
    if (pSpriteBackground){
        pSpriteBackground->setZOrder(0);
        float scaleX = size.width/pSpriteBackground->getContentSize().width;
        pSpriteBackground->setScaleX(scaleX);
        float scaleY = size.height/pSpriteBackground->getContentSize().height;
        pSpriteBackground->setScaleY(scaleY);
        pSpriteBackground->setPosition( Vec2(size.width/2, size.height/2) );
        pSpriteBackground->setName("BG");
        this->addChild(pSpriteBackground, 0);
    }

    
    // Player
    ship = LunarModule::create();
    ship->setGameLayer(this);
    ship->useHealthLabel();
    ship->useInfoLabel();
    ship->getPhysicsBody()->setRotationEnable(false);
    ship->setGameLayer(this);
    //Utils::setSize(ship, 64, 64);
    ship->setScale(.25, .25);
    addChild(ship,50);

    GameElementsFactory::getInstance()->setPlayer(ship);
    GameElementsFactory::getInstance()->setGameLayer(this);

    // HUD
    auto m_HudLayer =  HudLayer2::create();
    m_HudLayer->setShip(ship);
    m_HudLayer->setGameLayer(this);
    addChild(m_HudLayer,100);
    m_HudLayer->startTracking();

    // CTRL
    m_CtrlLayer =  CtrlLayer::create();
    m_CtrlLayer->setShip(ship);
    m_CtrlLayer->setGameLayer(this);
    m_CtrlLayer->setScale(.25);
    m_CtrlLayer->setOpacity(128);
    addChild(m_CtrlLayer,3000);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MyTMX::onContactBegin, this);
    contactListener->onContactPreSolve =CC_CALLBACK_1(MyTMX::onPreSolve, this);
    contactListener->onContactPostSolve =CC_CALLBACK_1(MyTMX::onPostSolve, this);
    contactListener ->onContactSeparate = CC_CALLBACK_1(MyTMX::onContactSeperate, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);


    // TileMap
    dsj::TileMap* tileMap;
    try {
        //tileMap = new dsj::TileMap("TMX-Cave/level0_30x16x64.tmx");
        tileMap = new dsj::TileMap(tmx);//"TMX-Cave/simplest2.tmx");
        log("%s", tileMap->to_string().c_str());
        tileMap->render(this);
    } catch (...) {
        std::exception_ptr p = std::current_exception();
        log("Error Tile Map");
    }

    // TODO : pull from map properties
    m_isFollow = false;
    m_isConstrainedToVer = false;
    m_isConstrainedToHor = false;

    if ( m_isFollow){
        Follow* follow = Follow::create(ship);
        this->runAction(follow);
    }

    // TODO :: pull from map
    m_isBoundingBoxed = false;
    // boundry
    if ( m_isBoundingBoxed){
        auto sizeWindowView = Director::getInstance()->getWinSize();
        PhysicsMaterial material(1.0f,1.0f,1.0f);
        float border = 5;
        PhysicsBody* boundry = PhysicsBody::createEdgeBox( sizeWindowView,   material,  border, Vec2(sizeWindowView.width/2,sizeWindowView.height/2));
        setPhysicsBody(boundry);
    }

    // TODO :: pull spawn point form object layer to this lavel
    auto sizeWindowView = Director::getInstance()->getWinSize();
    std::vector<dsj::Object*> vSpwanPointPlayer = tileMap->getObjectsByType("SpawnPlayer");
    auto objectSpawn = vSpwanPointPlayer[0];
    int x = objectSpawn->GetAttributeInt("x");
    int y = sizeWindowView.height - objectSpawn->GetAttributeInt("y");
    Vec2 posPlayer(x,y);
    ship->setPosition(posPlayer);

    if (DEBUG) {
        drawNode = DrawNode::create();
        Color4F color(0, 1, 0, 1);
        Size winSize = Director::getInstance()->getWinSize();
        float dx = 64;
        float dy = 64;

        int cols = tileMap->getWidth(); // winSize.width / 64;
        int rows = tileMap->getHeight(); //winSize.height / 64;

        // Horizontal
        for (int i = rows; i >= 0 ; i--){
            drawNode -> drawSegment(
                                    Vec2(0,      sizeWindowView.height - dy*i),
                                    Vec2(cols*dx,sizeWindowView.height - dy*i),
                                    1,
                                    color);
        }


        for (int i = cols; i >= 0 ; i--){
            drawNode -> drawSegment(
                                    Vec2(i*dx, sizeWindowView.height),
                                    Vec2(i*dx, sizeWindowView.height-rows*dy),
                                    1,
                                    color);
        }

        LabelManager::getInstance()->setTarget(this);

                for (int x = 0; x <= cols * dx ; x=x+dx){

                    for (int y = 0  ; y <=  rows*dy ; y=y+dy){

                        Vec2 p(x, sizeWindowView.height- y);
                        drawNode -> drawPoint(p, 10, Color4F::BLUE);

//                        std::stringstream ss;
//                        ss << "(" << x << "," << y << ")";
//                        Label* l = Label::createWithBMFont(
//                                                           GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL,
//                                                           ss.str().c_str());
//                        l->setWidth( 200);
//                        l->setColor(Color3B::ORANGE);
//                        l->setAnchorPoint(Vec2(0,0));
//                        l->setPosition(p);
//                        l->setScale(.35);
//                        addChild(l,100);


                        std::stringstream sss;
                        sss << "(" << x << "," <<  (sizeWindowView.height -y) << ")";
                        Vec2 pp(x, sizeWindowView.height- y );
                        Label* ll = Label::createWithBMFont(
                                                           GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL,
                                                           sss.str().c_str());
                        ll->setWidth( 200);
                        ll->setColor(Color3B::WHITE);
                        ll->setAnchorPoint(Vec2(0,0));
                        ll->setPosition(p);
                        ll->setScale(.35);
                        addChild(ll,100);

                    }
                }


        addChild(drawNode,0);
    }

    this->scheduleUpdate();


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

Node* finsh;
bool canEnterDiedProcess = true;
bool canEnterFinishedProcess = true;
void MyTMX::GameLoop ( Ref* target){


    finsh = this->getChildByTag(12345);
    Size size = Director::getInstance()->getWinSize();
    //Level end success
    if ( canEnterFinishedProcess && finsh->getBoundingBox().intersectsRect( ship->getBoundingBox())){

        GameLayer::level ++;
        canEnterFinishedProcess = false;

        unscheduleAllCallbacks();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::TADA, false);

        auto scene = MyTMX::scene("TMX-cave/simplest2.tmx");
        TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  scene);
        Director::getInstance()->replaceScene(animation);
        //SceneManager::getInstance()->Success();
    }

    // Level End Failure
    if(ship->getHealth() <= 0 && canEnterDiedProcess){
        canEnterDiedProcess = false;
        unscheduleAllCallbacks();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::FAILED_SOUND, false);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::GAME_OVER);
        SceneManager::getInstance()->Failed();
    }
    
}

void MyTMX::update ( float dt){

    GameLoop(this);

}

void MyTMX::update2 ( float dt){


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





/**
 * Two shapes just started touching for the first time this step.
 *
 *  Return true from the callback to process the collision normally
 *  or false to cause Chipmunk to ignore the collision entirely.
 *
 *  If you return false, the preSolve() and postSolve() callbacks will
 *  never be run, but you will still recieve a separate event when the
 *  shapes stop overlapping.
 */
bool MyTMX::onContactBegin(cocos2d::PhysicsContact& contact){

    //return true;
    bool isContinueOnToNoramlProcessing = true;
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    log("Tag-1: %i Tag-2: %i", nodeA->getTag(), nodeB->getTag());

    Sprite* go1 = dynamic_cast<Sprite*>(nodeA);
    dsj::Tile* tile1 =  (dsj::Tile*) go1->getUserData();
    Sprite* go2 = dynamic_cast<Sprite*>(nodeB);
    dsj::Tile* tile2 =  (dsj::Tile*) go2->getUserData();

    PhysicsBody* phyBody1 = go1->getPhysicsBody();
    PhysicsBody* phyBody2 = go1->getPhysicsBody();

    LunarModule* player = nullptr;
    if (
          (phyBody1->getCategoryBitmask() & phyBody2->getCollisionBitmask())
                                    ||
          (phyBody2->getCategoryBitmask() &phyBody1->getCollisionBitmask())
       )
    {

        if ( go1->getTag() == GameAssets::TAGS::PLAYER) {

            player = dynamic_cast<LunarModule*>(go1);

            if (go2->getTag() ==  GameAssets::TAGS::SPIKE){
                auto spike = go2;
                dsj::Tile* spikeTile =  (dsj::Tile*) spike->getUserData();
                int damage = std::stoi( spikeTile->GetProperty("GivesDamage"));
                player->takeDamage(damage);
            }


        }
        if ( go2->getTag() == GameAssets::TAGS::PLAYER)
        {

            player = dynamic_cast<LunarModule*>(go1);

            if (go1->getTag() ==  GameAssets::TAGS::SPIKE){
                auto spike = go1;
                dsj::Tile* spikeTile =  (dsj::Tile*) spike->getUserData();
                int damage = std::stoi( spikeTile->GetProperty("GivesDamage"));
                player->takeDamage(damage);
            }
        }

    }

    return isContinueOnToNoramlProcessing;
}



/*
 * Two shapes are touching during this step.
 *
 * Return false from the callback to make Chipmunk
 * ignore the collision this step or true to process it normally.   *
 */
bool MyTMX::onPreSolve(cocos2d::PhysicsContact& contact){
    bool isContinueOnToNoramlProcessing = true;
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    //    GameObject* go1 = dynamic_cast<GameObject*>(nodeA);
    //    GameObject* go2 = dynamic_cast<GameObject*>(nodeB);
    //
    //    if ( go1 && go2){
    //        // TODO
    //        //        std::string go1name1 = go1->getName();
    //        //        int tagA = go1->getTag();
    //        //        std::string go1name2 = go2->getName();
    //        //        int tagB = go2->getTag();
    //
    //    } else {
    //        return isContinueOnToNoramlProcessing;
    //    }
    return isContinueOnToNoramlProcessing;
}

/*
 Two shapes are touching and their collision response has been processed.
 You can retrieve the collision impulse or kinetic energy at this time
 if you want to use it to calculate sound volumes or damage amounts.
 */
bool MyTMX::onPostSolve(cocos2d::PhysicsContact& contact){
    bool isContinueOnToNoramlProcessing = true;
    //    auto nodeA = contact.getShapeA()->getBody()->getNode();
    //    auto nodeB = contact.getShapeB()->getBody()->getNode();
    //
    //    GameObject* go1 = dynamic_cast<GameObject*>(nodeA);
    //    GameObject* go2 = dynamic_cast<GameObject*>(nodeB);
    //
    //    if ( go1 && go2){
    //        std::string go1name1 = go1->getName();
    //        std::string go1name2 = go2->getName();
    //    } else {
    //        return isContinueOnToNoramlProcessing;
    //    }
    return isContinueOnToNoramlProcessing;
}

/*
 *Two shapes have just stopped touching for the first time this step.
 * To ensure that begin()/separate() are always called in balanced pairs,
 * it will also be called when removing a shape while its in contact with
 * something or when deallocating the space.
 */
bool MyTMX::onContactSeperate(cocos2d::PhysicsContact& contact){
    bool isContinueOnToNoramlProcessing = true;
    //    auto nodeA = contact.getShapeA()->getBody()->getNode();
    //    auto nodeB = contact.getShapeB()->getBody()->getNode();
    //
    //    GameObject* go1 = dynamic_cast<GameObject*>(nodeA);
    //    GameObject* go2 = dynamic_cast<GameObject*>(nodeB);
    //
    //    if ( go1 && go2){
    //        std::string go1name1 = go1->getName();
    //        std::string go1name2 = go2->getName();
    //
    //    } else {
    //        return isContinueOnToNoramlProcessing;
    //    }
    return isContinueOnToNoramlProcessing;
}
