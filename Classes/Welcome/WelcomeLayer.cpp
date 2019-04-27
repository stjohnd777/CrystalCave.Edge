

#include "MyMacros.h"
#include "GameAssets.h"

#include "WelcomeLayer.h"
#include "OptionLayer.h"
#include "GameLayer.h"
#include "Utils.h"
#include "SceneManager.h"

#include "GLVertFence.h"
#include "Mine.h"
#include "Ligthning.h"

using namespace cocos2d;

#include <sstream>
#include <string>
using namespace std;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


Scene*WelcomeLayer::scene() {
    
    Scene *scene = Scene::create();

    string  background(GameAssets::WELCOME_BACKGROUND);
    string title ("Crystal Cave");

    WelcomeLayer *layer = WelcomeLayer::create(background,title);

    scene->addChild(layer);
    return scene;
}

WelcomeLayer *WelcomeLayer::create(std::string bg,std::string title) {

    WelcomeLayer * layer = new WelcomeLayer();
    if ( layer && layer->init(bg,title))
    {
        layer->autorelease();
    }else{
        delete layer;
        layer = nullptr;
    }
    return layer;
}


bool WelcomeLayer::init(std::string bg,std::string title) {

    if ( ! Layer::init() ) {
        return false;
    }

    setTag(GameAssets::Layer::TAG_WELCOME_LAYER);
    this->titleLabelString = title;
    this->backGroundImage = bg;

    strechBackgroundToScreen(this->backGroundImage, 0);
    //AddLighting(4);
    CreateCrystalCeilingFloor();


   this->play = [&](Ref* sender){
        SceneManager::getInstance()->Game(GameLayer::level);
    };

   this->settings = [&](Ref* sender){
       SceneManager::getInstance()->Options();
    };

    this->exit = [&](Ref* sender){
        SceneManager::getInstance()->Exit();
    };

#if IS_DESKTOP
    keyListener();
#endif


    SimpleAudioEngine::getInstance()->playBackgroundMusic(GameAssets::Sound::GAME_BACKGROUND_SOUND, true);

    initLabels();

    initMenu();
    
    return true;
}


int titleLableFontSize = 64;
float titleLablePercentHeight = .67;
int titleLableZOdered = 1;

void WelcomeLayer::initLabels() {

    const char* font1 = GameAssets::Fonts::TTF::MarkerFelt;
    //GameAssets::Fonts::TTF::ABDUCTION;
    // create title in center layer and
    auto title = titleLabelString + std::string(" by SillyMutts");
    auto* pLabel = Label::createWithTTF(title, font1, 78);
    //auto* pLabel = Label::createWithBMFont(font1, title);
    //pLabel->enableGlow(Color4B::GREEN);
    pLabel->enableShadow();
    pLabel->enableOutline(Color4B::RED);

    //auto* pLabel = Label::createWithSystemFont(titleLabelString,"System",titleLableFontSize);
    Size size = Director::getInstance()->getWinSize();
    pLabel->setPosition( Vec2(size.width / 2,  titleLablePercentHeight *size.height  ) );
    this->addChild(pLabel, titleLableZOdered);

    string font =  GameAssets::Fonts::BMF::ALPHA_NUM::FUTURA_48;
    string co = "SillyMutts Game Studios";
    auto* pTitleCO = Label::createWithBMFont( font,co);
    pTitleCO->enableShadow();
    pTitleCO->setScale(2);
    pTitleCO->setPosition( Vec2(size.width / 2, size.height / 3) );
    this->addChild(pTitleCO, 99);


    string logo = "Making You Smile!";
    auto* pLogo = Label::createWithBMFont( font,logo);
    pLogo->enableShadow();
    pLogo->setScale(1.5);
    pLogo->setPosition( Vec2(size.width / 2, size.height / 3 -25) );
    this->addChild(pLogo, 99);

    string s = "St.John System LLC";
    auto* ss = Label::createWithBMFont( font,s);
    ss->enableShadow();
    ss->setScale(.75);
    ss->setPosition( Vec2(size.width / 2, size.height / 3 - 50) );
    this->addChild(ss, 99);
    
}

void WelcomeLayer::initMenu() {
    
    Size size = Director::getInstance()->getWinSize();

    // Exit
    std::string exitNormal = GameAssets::Sprite::BTN_EXIT;
    std::string exitSelected =  GameAssets::Sprite::BTN_EXIT_SEL;
    auto pCloseItem = MenuItemImage::create(exitNormal, exitSelected,this->exit);
    
    Menu* pCloseMenu = Menu::create(pCloseItem, nullptr);
    Point closePossition = Vec2( pCloseItem->getContentSize().width  +10, Director::getInstance()->getWinSize().height - pCloseItem->getContentSize().height  );
    pCloseMenu->alignItemsVertically();
    pCloseMenu->setPosition(closePossition);
    this->addChild(pCloseMenu,5);


    // Play
    string play =GameAssets::Sprite::BTN_PLAY;
    string play_sel =GameAssets::Sprite::BTN_PLAY_SEL;
    MenuItemImage *pPlayItem = MenuItemImage::create(play,play_sel,this->play );
    pPlayItem->setScale(3);
    Menu* pPlayMenu = Menu::create(pPlayItem, nullptr);
    Point playPossition = Vec2(size.width / 2, size.height /2);
    pPlayMenu->alignItemsHorizontallyWithPadding(32);
    pPlayMenu->setPosition(playPossition);
    addChild(pPlayMenu);

    // Options
    std::string up =  GameAssets::Sprite::BTN_SETTINGS;
    std::string down =   GameAssets::Sprite::BTN_SETTINGS_SEL;
    Sprite* hack = Sprite::create(up);
    Point pos = Vec2( hack->getContentSize().width /2 * 2 , 100);

    MenuItemImage *pConfigItem = MenuItemImage::create(down.c_str(),up.c_str(),[&](Ref* sender){
        auto scene = OptionLayer::scene();
        Director::getInstance()->runWithScene(scene);
    });

    Menu* pOptionsMenu = Menu::create(pConfigItem, NULL);
    pOptionsMenu->alignItemsVerticallyWithPadding(32);
    pOptionsMenu->setPosition(pos);
    this->addChild(pOptionsMenu,5);
    
}

void WelcomeLayer::CreateCrystalCeilingFloor()
{

    int worldWidth = Director::getInstance()->getWinSize().width ;
    int stalactiteWidth = Sprite::create("stalactite.png" )->getContentSize().width;
    int stalactiteSegments = 2 * worldWidth/stalactiteWidth;
    int nx = stalactiteSegments;

    bool flipedX = Utils::FlipCoin();

    for ( int i = 0 ; i < nx ; i ++)
    {
        int choiceFloor = Utils::getRandomIntBetweenTopBottom(1, 4);
        bool flipedX = Utils::FlipCoin();
        Sprite* crystalFloorPart = nullptr;
        switch (choiceFloor) {
            case 1:
                continue;
                break;
            case 2:

                if (flipedX) {
                    crystalFloorPart =  Sprite::create("QuartzCrystalNorthFliped.png");
                } else {
                    crystalFloorPart =  Sprite::create("QuartzCrystalNorth.png");
                }
                break;
            case 3:
                if (flipedX) {
                    crystalFloorPart= Sprite::create("QuartzCrystalNorthFliped3.png");
                } else {
                    crystalFloorPart= Sprite::create("QuartzCrystalNorth3.png");
                }
                break;
            default:

                crystalFloorPart = Sprite::create("geyzer.png");
                break;
        }

        crystalFloorPart->setAnchorPoint(Vec2(.5,0));
        int xcoord = i * crystalFloorPart->getContentSize().width/2;
        Vec2 pos =  Vec2(xcoord,0);
        crystalFloorPart->setPosition(pos);
        // Crystal Floor Part Randomization Size
        float scaleXFloorPart = 4 * Utils::getRandomFloatBetweenTopBottom(.5, 2);
        float scaleYfloorPart = 4 * Utils::getRandomFloatBetweenTopBottom(.5, 2);
        crystalFloorPart->setScale(scaleXFloorPart, scaleYfloorPart);
        addChild(crystalFloorPart);


        // Crystal Ceiling
        Sprite* crystalCiellingPart = Sprite::create("stalactite.png" );
        crystalCiellingPart->setPosition(Point(xcoord,Director::getInstance()->getWinSize().height));
        crystalCiellingPart->setAnchorPoint(Vec2(.5,1));

        float scaleXCeilingPart = 4* Utils::getRandomFloatBetweenTopBottom(1, 3);
        float scaleCeilingPart = 4 * Utils::getRandomFloatBetweenTopBottom(1, 3);

        crystalCiellingPart->setScale(scaleXCeilingPart, scaleCeilingPart);
        if ( Utils::getRandomFloatBetweenTopBottom(0, 1) < .5){
            crystalCiellingPart->setFlippedX(true);
        }

        addChild(crystalCiellingPart);
    }

}


void WelcomeLayer::AddLighting(int numberBoltsOnThisLenght)
{
    int numberBolts = 1;
    int thickness = 2;
    int displacement = 100;
    int detail = 2;
    Color4F lightingColor(.5,  .5, .5, .8);

    Size size = Director::getInstance()->getWinSize();

    for ( int i = 0; i < numberBoltsOnThisLenght ; i++){

        Point r = Utils::getRandomPointOnScene();
     
        AddLigthning(
                     Point(r.x,size.height),
                     Point(r.x, 0),
                     numberBolts,// numberBolts
                     thickness,// thickness
                     displacement,// displacement
                     detail , // detail
                     lightingColor,
                      Utils::FlipCoin());
    }

}

void WelcomeLayer::AddLigthning(Point a,
                             Point b,
                             int numberBolts,
                             int thickness,
                             int displacement,
                             int detail,
                             Color4F myColor ,
                             bool isRandomColor){

    Ligthning* ligthning =  Ligthning::create();
    ligthning->setGameLayer(this);
    ligthning->setPointA(a);
    ligthning->setPointB(b);
    ligthning->setNumberBolts(numberBolts);
    ligthning->setThickness(thickness);
    ligthning->setDisplacement(displacement);
    ligthning->setDetail(detail);
    ligthning->setMyColor(myColor);
    ligthning->setIsRandomColor(isRandomColor);
    ligthning->start(0);

    this->addChild(ligthning);
}

#if IS_DESKTOP

void WelcomeLayer::keyListener(){

    setKeypadEnabled(true);

    auto listenerKey = EventListenerKeyboard::create();
    listenerKey->onKeyPressed = CC_CALLBACK_2(WelcomeLayer::onKeyPressed, this);
    listenerKey->onKeyReleased = CC_CALLBACK_2(WelcomeLayer::onKeyReleased , this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);


    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(WelcomeLayer::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(WelcomeLayer::onMouseUp, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(WelcomeLayer::onMouseDown, this);
    mouseListener->onMouseScroll = CC_CALLBACK_1(WelcomeLayer::onMouseScroll, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void WelcomeLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
 
    bool play = false;
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
            Director::getInstance()->end();
            break;
        case EventKeyboard::KeyCode::KEY_ENTER:
            play = true;
            break;
        case EventKeyboard::KeyCode::KEY_X:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
            Director::getInstance()->end();
            break;
        default:
            break;

    }
    
    if ( play){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
        Scene* scene = GameLayer::scene();
        TransitionCrossFade *animation = TransitionCrossFade::create(.5,  scene);
        Director::getInstance()->replaceScene(animation);
    }
}

void WelcomeLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
 
}

void WelcomeLayer::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    Point p = Point(e->getCursorX(),e->getCursorY());
    
}

void WelcomeLayer::onMouseUp(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "Mouse Up detected, Key: ";
}

void WelcomeLayer::onMouseMove(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "MousePosition X:";
}

void WelcomeLayer::onMouseScroll(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "Mouse Scroll detected, X: ";
}

#endif

