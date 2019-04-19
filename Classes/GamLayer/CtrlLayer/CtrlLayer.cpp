//
//  CtrlLayer.cpp
//  CrystalCave.c2dx.2.8
//
//  Created by Daniel St. John on 9/29/15.
//                                4/19/19
//
//

#include "CtrlLayer.h"
#include "FailedScene.h"

#include "Constants.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "Utils.h"

#include <string>

using namespace cocos2d;
using namespace CocosDenshion;

Scene* CtrlLayer::scene() {
    Scene *scene = Scene::create();
    FailedScene *layer = FailedScene::create();
    scene->addChild(layer);
    return scene;
}

CtrlLayer* CtrlLayer::create( )
{
    CtrlLayer *pRet = new(std::nothrow) CtrlLayer();
    if ( pRet && pRet->init() ) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}


bool CtrlLayer::init() {
    if ( ! Layer::init() ){
        return false;
    }
    setTag(GameAssets::Layer::TAG_CTRL_LAYER);
    setName("CTRL");
    initControlLayer();
    return true;
}

int CtrlLayer::getThrust() {
    return   m_ThrusterIntPercentage  ;
}

void CtrlLayer::setThrust(int num) {
    m_ThrusterIntPercentage = num;
    m_slider->setPercent(num)  ;
}

float CtrlLayer::getThrustPercentage() {
    return   (float)m_ThrusterIntPercentage / 100.00 ;
}

void CtrlLayer::initControlLayer(){
    
    Sprite*  ctrlNode = Sprite::create();
    ctrlNode->setAnchorPoint(Vec2(0,0));
    ctrlNode->setPosition(0, 0);
    
    Size size = Director::getInstance()->getWinSize();

#if IS_MOBILE

    float scale = 3;
    sprite = Sprite::create("north.png");
    // North and South
    Vector<MenuItem*> vMeniItemsNS;

    // North
    auto imiThrustNorth = MenuItemImage::create("north.png","north.png",[&](Ref* sender){
        ship->applyThrush(Vec2(0,-1),ship->MAX_THRUST * (float)slider->getPercent() / 100.0);
        //ship->applyThrush(Vec2(0,-1),ship->MAX_THRUST * 50 / 100.0);
    });
    imiThrustNorth->setScale(scale);
    vMeniItemsNS.pushBack(imiThrustNorth);
    
    // South
    auto imiThrustSouth = MenuItemImage::create("south.png","south.png",[&](Ref* sender){
        ship->applyThrush(Vec2(0,1), ship->MAX_THRUST * (float)slider->getPercent() / 100.0);
        //ship->applyThrush(Vec2(0,1), ship->MAX_THRUST * 50 / 100.0);
    });
    imiThrustSouth->setScale(scale);
    vMeniItemsNS.pushBack(imiThrustSouth);
    
    auto menuNS = Menu::createWithArray(vMeniItemsNS);
    menuNS->setColor(Color3B::WHITE);
    menuNS->alignItemsVerticallyWithPadding(32);
    Vec2 posNS= Vec2(Director::getInstance()->getWinSize().width - 2 * sprite->getContentSize().width, Director::getInstance()->getWinSize().height /2);
    menuNS->setPosition(posNS);
    ctrlNode->addChild(menuNS);
    
    
    // East
    Vector<MenuItem*> vMenuIemsE;
    auto imiThrustEast = MenuItemImage::create("east.png","east.png",[&](Ref* sender){
        ship->applyThrush(Vec2(1,0),ship->MAX_THRUST * (float)slider->getPercent() / 100.0);
        //ship->applyThrush(Vec2(1,0),ship->MAX_THRUST * 50 / 100.0);
    });
    imiThrustEast->setScale(scale);
    vMenuIemsE.pushBack(imiThrustEast);
    auto menuEast = Menu::createWithArray(vMenuIemsE);
    Vec2 posEast = Vec2( Director::getInstance()->getWinSize().width - 2 * sprite->getContentSize().width, 4* sprite->getContentSize().height );
    menuEast->setPosition(posEast);
    ctrlNode->addChild(menuEast);

    // West
    Vector<MenuItem*> vMenuItemW;
    auto imiThrustWest = MenuItemImage::create("west.png","west.png",[&](Ref* sender){
        ship->applyThrush(Vec2(-1,0),ship->MAX_THRUST * (float)slider->getPercent() / 100.0);
        //ship->applyThrush(Vec2(-1,0),ship->MAX_THRUST * 50 / 100.0);
    });
    imiThrustWest->setScale(scale);
    vMenuItemW.pushBack(imiThrustWest);
    auto pMenuThrustWest = Menu::createWithArray(vMenuItemW);
    Vec2 posWest =  Vec2(2 * sprite->getContentSize().width, 4* sprite->getContentSize().height);
    pMenuThrustWest->setPosition(posWest);
    ctrlNode->addChild(pMenuThrustWest);
    
#endif
    
    m_slider = ui::Slider::create();
        m_slider->loadBarTexture("slider.64.256.png");
        m_slider->loadSlidBallTextures("box.red.64.64.png", "box.red.64.64.png", "");
        m_slider->loadProgressBarTexture("slider.64.256.png");
        Point pointSliderThrust =Vec2(100,Utils::getMidPoint().y);
        m_slider->setPosition(pointSliderThrust);
        m_slider->setPercent(50);
        //slider->setScale(3);
        m_slider->setScale(4, 7);

        m_slider->addEventListener( [&](Ref* sender,ui::Slider::EventType percentChanged){
            ui::Slider* slider = dynamic_cast<ui::Slider * >(sender);
            m_ThrusterIntPercentage = slider->getPercent();
            std::string m =  std::to_string(m_ThrusterIntPercentage) + "%";
            m_LabelThrust->setString( m);

        });

        ctrlNode->addChild(m_slider);

        RotateBy* rot = RotateBy::create(.1, -90);
        m_slider->runAction(rot);

        const char* msg= "50%";
        sprintf(buffer,"%s",msg);

        m_LabelThrust = Label::createWithBMFont("teletype_messages.fnt",buffer);
        m_LabelThrust->setWidth(100);
        m_LabelThrust->setColor(Color3B::RED);
        m_LabelThrust->setAnchorPoint(Point(0.5,0.5));

        Point pLabelThrust =Point(100,Utils::getMidPoint().y);
        m_LabelThrust->setPosition(pLabelThrust);
        m_LabelThrust->setTag(GameAssets::Sprite::TEMP_LABEL);
        ctrlNode->addChild(m_LabelThrust,LayerLevel::kCtrl);


    addChild(ctrlNode);
}
