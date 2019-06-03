
#include <string>
#include <sstream>

#include "GameAssets.h"
#include "SuccessLayer.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "GameManager.h"


using namespace cocos2d;
using namespace CocosDenshion;

Scene* SuccessLayer::scene() {
    Scene *scene = Scene::create();
    SuccessLayer *layer = SuccessLayer::create();
    scene->addChild(layer);
    return scene;
}


bool SuccessLayer::init() {
    
    if ( ! Layer::init() ){
        return false;
    }

    Size size = Director::getInstance()->getWinSize();

    //strechBackgroundToScreen("SIFI_GUI/Window/WindowMedium.png", 0, 1);
    strechBackgroundToScreen(GameAssets::SUCCESS_BACKGROUND, 1);

    auto window = strechBackgroundToScreen(GameAssets::Sprite::WINDOW_TALL, 2, .9);

    std::stringstream ss;
    ss << "Level " << GameManager::getInstance()->getLevel() <<  " Completed !! ";
    
    

    
    
    auto sizeWindowTall = window->getContentSize();
 
    const char* font = GameAssets::Fonts::BMF::ALPHA_NUM::FUTURA_48; //GameAssets::Fonts::TTF::MarkerFelt;
    auto title = std::string(ss.str());
    auto* pLabel = Label::createWithBMFont(font,title);
    pLabel->setPosition( Vec2(size.width / 2,  .68 *size.height  ) );
    this->addChild(pLabel,5);
    
    
    auto star0 = Sprite::create(GameAssets::Sprite::STAR_ON);
    auto startSize =star0->getContentSize();
    
    auto star1 = Sprite::create(GameAssets::Sprite::STAR_ON);
    star1->setPosition( Vec2(size.width/2 - startSize.width ,   .60 * size.height ) );
    auto star2 = Sprite::create(GameAssets::Sprite::STAR_ON);
    star2->setPosition( Vec2( size.width/2 ,                    .60 * size.height ) );
    auto star3 = Sprite::create(GameAssets::Sprite::STAR_OFF);
    star3->setPosition( Vec2( size.width/2+ + startSize.width , .60 * size.height )  );
    
    this->addChild(star1,99);
    this->addChild(star2,99);
    this->addChild(star3,99);
    
    
    
    
    
    // Replay
    MenuItemImage *pRePlayItem = MenuItemImage::create(
                                                         GameAssets::Sprite::BTN_RELOAD,
                                                         GameAssets::Sprite::BTN_RELOAD_SEL,
                                                         [&](Ref*){
                                                             GameManager::getInstance()-> ResumeLevel();
                                                         });
    
    
    Menu* pRePlayMenu = Menu::create(pRePlayItem, nullptr);
    pRePlayMenu->alignItemsHorizontallyWithPadding(32);
    pRePlayMenu->setPosition(Vec2(size.width / 2 - 128 - 32, size.height /3));
    //window->
    addChild(pRePlayMenu,10);
    
    // Play
    MenuItemImage *pPlayNextItem = MenuItemImage::create(
                                                     GameAssets::Sprite::BTN_PLAY,
                                                     GameAssets::Sprite::BTN_PLAY_SEL,
                                                     [&](Ref*){
                                                         GameManager::getInstance()-> LoadNextLevel();
                                                     });
    
    
    Menu* pPlayMenu = Menu::create(pPlayNextItem, nullptr);
    pPlayMenu->alignItemsHorizontallyWithPadding(32);
    pPlayMenu->setPosition(Vec2(size.width / 2 , size.height / 3));
    //window->
    addChild(pPlayMenu,10);
    
    
    // Level Select
    MenuItemImage *pSelectItem = MenuItemImage::create(
                                                       GameAssets::Sprite::BTN_MENU,
                                                       GameAssets::Sprite::BTN_MENU_SEL,
                                                       [&](Ref*){
                                                           SceneManager::getInstance()->LevelSelect();
                                                       } );
    
    Menu* pSelectMenu = Menu::create(pSelectItem, nullptr);
    pSelectMenu->setPosition(Vec2(size.width / 2  + 128 + 32, size.height /3));
    //window->
    addChild(pSelectMenu,10);
    
    


//    auto* pTime = Label::createWithTTF("Tap to Continue to next Level", font, 42);
//    pTime->enableShadow();
//    pTime->enableOutline(Color4B::RED);
//    pTime->setPosition( Vec2(size.width / 2,  size.height/2  ) );
//    this->addChild(pTime,5);
//
//
//    auto singleTouchListener = EventListenerTouchOneByOne::create();
//    singleTouchListener->setSwallowTouches(true);
//    singleTouchListener->onTouchBegan = CC_CALLBACK_2(SuccessLayer::onTouchBegan, this);
//    getEventDispatcher()->addEventListenerWithSceneGraphPriority(singleTouchListener, this);
    
    GameManager::getInstance()->LevelComplete();

    return true;
}



bool SuccessLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    //int lastLEvel = GameManager::getInstance()->getLevel();
    //GameManager::getInstance()->setLevel(lastLEvel +1);
    //SceneManager::getInstance()->Game(GameManager::getInstance()->getLevel());
    
    GameManager::getInstance()->LoadNextLevel();
    return true;
}
