#include "OptionLayer.h"
#include "WelcomeLayer.h"
#include "Utils.h"

#include "GameAssets.h"

Scene* OptionLayer::scene()
{
    Scene *scene = Scene::create();
    OptionLayer *layer = OptionLayer::create();
    scene->addChild(layer);
    return scene;
}

bool OptionLayer::init() {
    
    setTag(GameAssets::Layer::TAG_OPTIONS_LAYER);
    
    if ( ! Layer::init() )
    {
        return false;
    }
 

    initBackGround();
    

    Size size = Director::getInstance()->getWinSize();

    //initBackMenu(1);

//    /////////////////////////////////////////////////////////////////////////////////////////////
//    // Background Sound On Off
//    /////////////////////////////////////////////////////////////////////////////////////////////
//    MenuItemFont* pSoundText = MenuItemFont::create("Music");
//    itemOn = MenuItemImage::create("sound.png", "sound.png", this, NULL);
//    itemOff = MenuItemImage::create("mute.png", "mute.png", this, NULL);
//    itemToggleMusic = MenuItemToggle::createWithTarget(
//            this, menu_selector(OptionLayer::menuBackgroundMusicCallback), itemOn,itemOff, NULL);
//
//
//    Menu* menu = Menu::create(pSoundText,itemToggleMusic, NULL);
//    menu->alignItemsVerticallyWithPadding(32);
//    menu->setPosition( ccp(Utils::getMidPoint().x, Utils::getWindowSize().height /2) );
//    addChild(menu, 1);

    setData();
    return true;
}

#include "SceneManager.h"
OptionLayer::OptionLayer(){

    auto f = [](Ref* ref){
        SceneManager::getInstance()->Welcome();
    };
    
    // Back Menu
    initBackMenu(f);

}


void OptionLayer::setData(){

    bool isPlayingMusic = true ; // pull data
    // music
    if (isPlayingMusic)
    {
        itemToggleMusic->setSelectedIndex(0);
    } else {
        itemToggleMusic->setSelectedIndex(1);
    }
}

void OptionLayer::controls(Ref* pSender) {
    
}


void OptionLayer::initBackGround() {
    
    strechBackgroundToScreen(GameAssets::OPTIONS_BACKGROUND, 0);
    
}

void OptionLayer::menuBackgroundMusicCallback(Ref* pSender)
{
    
    MenuItemToggle *toggleItem = (MenuItemToggle *)pSender;
    if (toggleItem->selectedItem() == itemOn) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(GameAssets::Sound::GAME_BACKGROUND_SOUND, true);
        //PersistenceManager::getInstance()->setPlayingBackGroundMusic(true );
    } else if (toggleItem->selectedItem() == itemOff) {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        //PersistenceManager::getInstance()->setPlayingBackGroundMusic(false );
    }
    
}


void OptionLayer::menuCloseCallback(Ref* pSender)
{
    //PersistenceManager::getInstance()->saveGameData();
    unscheduleAllCallbacks();
    SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto scene = WelcomeLayer::scene();
    Director::getInstance()->replaceScene(scene);
    //runWithScene(scene);
 
}



void OptionLayer::nillCallback(Ref* pSender)
{
    
}

