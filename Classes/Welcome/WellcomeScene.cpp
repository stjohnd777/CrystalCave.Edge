#include "MyMacros.h"
#include "Constants.h"
#include "WellcomeScene.h"
#include "OptionLayer.h"
#include "GameLayer.h"

using namespace cocos2d;

#include <sstream>
#include <string>
using namespace std;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


Scene* WellcomeScene::scene() {
    
    Scene *scene = Scene::create();

    WellcomeScene *layer = WellcomeScene::create(
                  GameAssets::Backgrounds::WELCOME_BACKGROUND,
                  "Crystal Cave"
                  );

    scene->addChild(layer);
    return scene;
}

WellcomeScene* WellcomeScene::create(std::string bg,std::string title) {

    WellcomeScene* layer = new WellcomeScene();
    if ( layer && layer->init(bg,title))
    {
        layer->autorelease();
    }else{
        delete layer;
        layer = nullptr;
    }
    return layer;
}


bool WellcomeScene::init(std::string bg,std::string title) {

    if ( ! Layer::init() ) {
        return false;
    }

    setTag(GameAssets::Layer::TAG_WELCOME_LAYER);
    this->titleLabelString = title;
    this->backGroundImage = bg;

    strechBackgroundToScreen(this->backGroundImage, 0);


   this->play = [&](Ref* sender){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
        auto scene = GameLayer::scene();
        Director::getInstance()->replaceScene(scene);
    };

   this->settings = [&](Ref* sender){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
        auto scene = OptionLayer::scene();
        Director::getInstance()->runWithScene(scene);
    };

    this->exit = [&](Ref* sender){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
        Director::getInstance()->end();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
        #endif
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

void WellcomeScene::initLabels() {

    // create title in center layer and
    auto* pLabel = Label::createWithSystemFont(titleLabelString,"System",titleLableFontSize);
    Size size = Director::getInstance()->getWinSize();
    pLabel->setPosition( Vec2(size.width / 2,  titleLablePercentHeight *size.height  ) );
    this->addChild(pLabel, titleLableZOdered);
    
}

void WellcomeScene::initMenu() {
    
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
    std::string down =  "setting.png";
    std::string up =  "setting_sel.png";
    Sprite* hack = Sprite::create("setting.png");
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



#if IS_DESKTOP

void WellcomeScene::keyListener(){

    setKeypadEnabled(true);

    auto listenerKey = EventListenerKeyboard::create();
    listenerKey->onKeyPressed = CC_CALLBACK_2(WellcomeScene::onKeyPressed, this);
    listenerKey->onKeyReleased = CC_CALLBACK_2(WellcomeScene::onKeyReleased , this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);


    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(WellcomeScene::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(WellcomeScene::onMouseUp, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(WellcomeScene::onMouseDown, this);
    mouseListener->onMouseScroll = CC_CALLBACK_1(WellcomeScene::onMouseScroll, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void WellcomeScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
 
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

void WellcomeScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
 
}

void WellcomeScene::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    Point p = Point(e->getCursorX(),e->getCursorY());
    
}

void WellcomeScene::onMouseUp(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "Mouse Up detected, Key: ";
}

void WellcomeScene::onMouseMove(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "MousePosition X:";
}

void WellcomeScene::onMouseScroll(Event *event)
{
//    EventMouse* e = (EventMouse*)event;
//    string str = "Mouse Scroll detected, X: ";
}
#endif

