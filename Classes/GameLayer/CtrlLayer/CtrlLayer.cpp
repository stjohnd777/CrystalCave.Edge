//
//  CtrlLayer.cpp
//  CrystalCave.c2dx.2.8
//
//  Created by Daniel St. John on 9/29/15.
//                                4/19/19
//
//

#include "CtrlLayer.h"
#include "FailedLayer.h"

#include "GameAssets.h"
#include "SimpleAudioEngine.h"

#include "Utils.h"

#include <string>

using namespace cocos2d;
using namespace CocosDenshion;

Scene* CtrlLayer::scene() {
    Scene *scene = Scene::create();
    FailedLayer *layer = FailedLayer::create();
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
    setTag(GameAssets::TAGS::CTRL_LAYER);
    setName("CTRL");
    initControlLayer();
    return true;
}

int CtrlLayer::getThrust() {
    return   m_ThrusterIntPercentage  ;
}

void CtrlLayer::setThrust(int num) {
    m_ThrusterIntPercentage = num;
    m_slider->setPercent(m_ThrusterIntPercentage)  ;
    std::string m =  std::to_string(m_ThrusterIntPercentage) + "%";
    m_LabelThrust->setString( m);
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

    
    float scale = 1;
    
    sprite = Sprite::create(GameAssets::Sprite::BTN_NORTH);
    // North and South
   

    // North
    auto imiThrustNorth = MenuItemImage::create(
        GameAssets::Sprite::BTN_NORTH,
        GameAssets::Sprite::BTN_NORTH_SEL,
        [&](Ref* sender){
            m_ship->applyThrush(Vec2(0,1), getThrustPercentage());
        });
    imiThrustNorth->setAnchorPoint(Vec2(1,0));
    imiThrustNorth->setScale(scale);
    
    Vector<MenuItem*> vMeniItemsN;
    vMeniItemsN.pushBack(imiThrustNorth);
    
    auto menuN = Menu::createWithArray(vMeniItemsN);
    menuN->setColor(Color3B::WHITE);
    Vec2 posN= Vec2(Director::getInstance()->getWinSize().width ,  sprite->getContentSize().height);
    menuN->setPosition(posN);
    ctrlNode->addChild(menuN);
    // End North
    
    
    
    // South
    auto imiThrustSouth = MenuItemImage::create(
        GameAssets::Sprite::BTN_SOUTH,
        GameAssets::Sprite::BTN_SOUTH_SEL,
        [&](Ref* sender){
            m_ship->applyThrush(Vec2(0,-1), getThrustPercentage());
        });
    imiThrustSouth->setScale(scale);
    imiThrustSouth->setAnchorPoint(Vec2(0,0));
    imiThrustSouth->setOpacity(128);
    
    Vector<MenuItem*> vMeniItemsS;
    vMeniItemsS.pushBack(imiThrustSouth);
    
    auto menuS = Menu::createWithArray(vMeniItemsS);
    menuS->setColor(Color3B::WHITE);
    Vec2 posS = Vec2(0   ,  sprite->getContentSize().height);
    menuS->setPosition(posS);
    ctrlNode->addChild(menuS);
    // End South
    
//    auto menuNS = Menu::createWithArray(vMeniItemsNS);
//    menuNS->setColor(Color3B::WHITE);
//    menuNS->alignItemsVerticallyWithPadding(32);
//    //Vec2 posNS= Vec2(Director::getInstance()->getWinSize().width - 2 * sprite->getContentSize().width, Director::getInstance()->getWinSize().height /2);
//     Vec2 posNS= Vec2(Director::getInstance()->getWinSize().width - sprite->getContentSize().width /2 , Director::getInstance()->getWinSize().height /2);
//
//    menuNS->setPosition(posNS);
//    ctrlNode->addChild(menuNS);
    
    
    // East
    Vector<MenuItem*> vMenuIemsE;
    auto imiThrustEast = MenuItemImage::create(GameAssets::Sprite::BTN_EAST ,GameAssets::Sprite::BTN_EAST_SEL,
        [&](Ref* sender){
            m_ship->applyThrush(Vec2(1,0),  getThrustPercentage());
        });
    imiThrustEast->setAnchorPoint(Vec2(1,0));
    imiThrustEast->setScale(scale);
    vMenuIemsE.pushBack(imiThrustEast);
    
    auto menuEast = Menu::createWithArray(vMenuIemsE);
    //Vec2 posEast = Vec2( Director::getInstance()->getWinSize().width - 2 * sprite->getContentSize().width, 4* sprite->getContentSize().height );
    Vec2 posEast = Vec2( Director::getInstance()->getWinSize().width , 0);
    menuEast->setPosition(posEast);
    ctrlNode->addChild(menuEast);
    // End East

    // West
    Vector<MenuItem*> vMenuItemW;
    auto imiThrustWest = MenuItemImage::create(
                                               GameAssets::Sprite::BTN_WEST,
                                               GameAssets::Sprite::BTN_WEST_SEL,
         [&](Ref* sender){
             m_ship->applyThrush(Vec2(-1,0),  getThrustPercentage());
         });
    imiThrustWest->setAnchorPoint(Vec2(0,0));
    //imiThrustWest->setScale(scale);
    vMenuItemW.pushBack(imiThrustWest);
    auto pMenuThrustWest = Menu::createWithArray(vMenuItemW);
    //Vec2 posWest =  Vec2(2 * sprite->getContentSize().width, 4* sprite->getContentSize().height);
    Vec2 posWest =  Vec2(0, 0);
    pMenuThrustWest->setPosition(posWest);
    ctrlNode->addChild(pMenuThrustWest);
    // End West
    
    
#endif

    // thruster slider
    m_slider = ui::Slider::create();

    m_slider->loadBarTexture("SIFI_GUI/Misc/LoadingBarBackground.png" );
    m_slider->loadSlidBallTextures("box.red.64.64.png", "box.red.64.64.png", "");

    m_slider->loadProgressBarTexture("SIFI_GUI/Misc/LoadingBarFill.png");
    Utils::setSize(m_slider, 600 , 100);

    Point pointSliderThrust = Vec2(100,Utils::getMidPoint().y);
    m_slider->setPosition(pointSliderThrust);
    m_slider->setPercent(50);
    m_slider->setOpacity(200);


    m_slider->addEventListener( [&](Ref* sender,ui::Slider::EventType percentChanged){
        ui::Slider* slider = dynamic_cast<ui::Slider * >(sender);
        m_ThrusterIntPercentage = slider->getPercent();
        std::string m =  std::to_string(m_ThrusterIntPercentage) + "%";
        m_LabelThrust->setString( m);

    });


    ctrlNode->addChild(m_slider);

    RotateBy* rot = RotateBy::create(.1, -90);
    m_slider->runAction(rot);

    // thruster slider lable
    const char* msg= "50%";
    sprintf(buffer,"%s",msg);

    auto font = GameAssets::Fonts::BMF::ALPHA_NUM::FUTURA_48;
    m_LabelThrust = Label::createWithBMFont(font,buffer);
    m_LabelThrust->setWidth(100);
    m_LabelThrust->setColor(Color3B::RED);
    m_LabelThrust->setAnchorPoint(Point(0.5,0.5));

    Point pLabelThrust =Point(100,Utils::getMidPoint().y);
    m_LabelThrust->setPosition(pLabelThrust);
    m_LabelThrust->setTag(GameAssets::TAGS::TEMP_LABEL);
    ctrlNode->addChild(m_LabelThrust);


    addChild(ctrlNode);
}
