 
#include "HudLayer.h"
#include "GameAssets.h"
#include <string>
#include <sstream>
#include <strstream>
#include <vector>

#include "SceneManager.h"
#include  "LabelManager.h"
#include "Utils.h"

using namespace std;
using namespace cocos2d;

#include <time.h>

static inline long millisecondNow() {
    time_t timer;
    timer = time(NULL);  /* get current time; same as: timer = time(NULL)  */
    return timer;
}


HudLayer* HudLayer::create()
{
    HudLayer *pRet = new(std::nothrow) HudLayer();
    if (pRet && pRet->init()) {
        pRet->autorelease();
    }else{
        delete pRet;
        pRet = nullptr;
    }
    return pRet;
}

bool HudLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    int tileSize = 64;
    int Z_HUD = 100;
    
    initBackMenu([](Ref* ref) {
        SceneManager::getInstance()->Welcome();
    }, tileSize);

    setTag(GameAssets::TAGS::HUD_LAYER);

    memset(szHiLevel,        0, LEN_HILEVEL_DISPLAY_BUFFER    *sizeof(char));

    memset(szHiScore,        0, LEN_HISCORE_DISPLAY_BUFFER    *sizeof(char));
    memset(szLevel,          0, LEN_CURLEVEL_DISPLAY_BUFFER*sizeof(char));
    memset(szScore,          0, LEN_SCORE_DISPLAY_BUFFER*sizeof(char));
    memset(szPlayTime,       0, LEN_PLAYTIME_BUFFER           *sizeof(char));
    memset(szHealth,         0, LEN_HEALTH_DISPLAY_BUFFER*sizeof(char));

    Size screenSize = Director::getInstance()->getWinSize();

    string HUD_FONT = GameAssets::Fonts::BMF::ALPHA_NUM::FUTURA_48;
    
    
    Vec2 upperLeft(0.0, 1.0);
    Vec2 loweRight(1.0, 1.0);
    Vec2 loweLeft(0.0, 0.0);
    Vec2 upperRight(1.0, 1.0);
    
    auto containerLevel = Sprite::create();
    containerLevel->initWithFile("SIFI_GUI/Misc/ItemContainer.png");
    containerLevel->setAnchorPoint(upperLeft);
    containerLevel->setPosition(Vec2( 0, screenSize.height ));
    Utils::setSize(containerLevel, 5 * tileSize ,  2 * tileSize);
    containerLevel->setOpacity(176);
    this->addChild(containerLevel,Z_HUD);

    sprintf(szLevel,"Level :  %i", 0);
    setLevelLabel( Label::createWithBMFont(HUD_FONT,szLevel));
    getLevelLabel()->setAnchorPoint(Vec2( .5, .5));
    getLevelLabel()->setPosition(Vec2(  (5 * tileSize)/2  , screenSize.height - (2 * tileSize)/2  ));
    this->addChild( getLevelLabel(),Z_HUD+1);


    // HEALTH
    auto containerHealth = Sprite::create();
    containerHealth->initWithFile("SIFI_GUI/Misc/ItemContainer.png");
    containerHealth->setAnchorPoint(Vec2(.5,1));
    containerHealth->setPosition(Vec2( screenSize.width /2, screenSize.height ));
    Utils::setSize(containerHealth, 6 * tileSize ,  2 * tileSize);
    containerHealth->setOpacity(176);
    this->addChild(containerHealth,Z_HUD);
    setHealthDisplay ( Label::createWithBMFont( HUD_FONT, szHealth) );
    getHealthDisplay()->setAnchorPoint(Vec2(.5,.5));
    getHealthDisplay()->setPosition( Vec2( screenSize.width /2, screenSize.height - (2 * tileSize)/2  ));
    this->addChild(getHealthDisplay(),Z_HUD+1);
    setHealth(100);


    // SCORE
    auto posScoreLabel = Vec2( screenSize.width, screenSize.height );
    auto anchorPointScoreLabel = Vec2(1,1);
    auto containerScore = Sprite::create();
    containerScore->initWithFile("SIFI_GUI/Misc/ItemContainer.png");
    containerScore->setAnchorPoint(anchorPointScoreLabel);
    containerScore->setPosition(posScoreLabel);
    Utils::setSize(containerScore, 5 * tileSize ,  2 * tileSize);
    containerScore->setOpacity(176);
    this->addChild(containerScore,Z_HUD);
    setScoreLabel( Label::createWithBMFont(HUD_FONT,"Score : 10,000"));
    getScoreLabel()->setAnchorPoint( Vec2(.5,.5));
    getScoreLabel()->setPosition(Vec2( screenSize.width - (5 * tileSize)/2  , screenSize.height - (2 * tileSize)/2  ));
    this->addChild( getScoreLabel(),Z_HUD+1);


    // PLayTime
    auto containerTime = Sprite::create();
    containerTime->initWithFile("SIFI_GUI/Misc/ItemContainer.png");
    containerTime->setAnchorPoint(Vec2( .5, 0));
    containerTime->setPosition(Vec2(screenSize.width/2, 0));
    Utils::setSize(containerTime, 6 * tileSize ,  2 * tileSize);
    containerTime->setOpacity(176);
    this->addChild(containerTime,1900);
    startTime = millisecondNow();
    setPlayTimeDisplay (Label::createWithBMFont(HUD_FONT, szPlayTime));
    getPlayTimeDisplay()->setAnchorPoint(Vec2( .5, .5));
    getPlayTimeDisplay()->setPosition(Vec2(screenSize.width/2, (2 * tileSize)/2 ));
    this->addChild(getPlayTimeDisplay(),2000);

    // Pause/Play
    auto pause =  Sprite::create();
    pause->initWithFile(GameAssets::Sprite::BTN_PAUSE);
    Utils::setSize(pause,64,64);
    pause->setAnchorPoint(Vec2(1,1));
    MenuItemSprite* itemPause = MenuItemSprite::create(pause,pause,NULL);
    itemPause->setAnchorPoint(Vec2(1,1));
    auto play = Sprite::create();
    play->initWithFile(GameAssets::Sprite::BTN_PLAY);
    Utils::setSize(play,64,64);
    play->setAnchorPoint(Vec2(1,1));
    MenuItemSprite* itemPlay = MenuItemSprite::create(play,play,NULL);
    itemPlay->setAnchorPoint(Vec2(1,1));

    Vector<MenuItem*> menuItems;
    menuItems.pushBack(itemPause);
    menuItems.pushBack(itemPlay);
    std::function<void(Ref*)> callback = [&](Ref* pSender)
    {
        static bool action = true;
        if ( action)
        {
            Director::getInstance()->pause();
            const char * msg = "Game Paused";
            pausedlabel = (Label*)Label::createWithBMFont (GameAssets::Fonts::BMF::ALPHA_NUM::FUTURA_48,msg) ;
     
            pausedlabel->setPosition(Utils::getMidPoint());
            addChild(pausedlabel);
            action = false;
        }else {
            Director::getInstance()->resume();
            pausedlabel->removeFromParentAndCleanup(true);
            action = true;

        }
        //action = !action;
    };
    itemTogglePlayPause = MenuItemToggle::createWithCallback(callback,menuItems);

    Menu* menu = Menu::create(itemTogglePlayPause, NULL);

    menu->setAnchorPoint(Vec2(1,.5));
    menu->setPosition(Vec2( screenSize.width   , screenSize.height /2) );
    addChild(menu, 2000);

    scheduleUpdate();
    
    return true;
}

void HudLayer::startTracking(){
    stopTracking();
    scheduleUpdate();
}

void HudLayer::stopTracking(){
    unscheduleAllSelectors();
}

void HudLayer::setHiScore(int score){
    memset(szHiScore, 0, sizeof(char)*LEN_HISCORE_DISPLAY_BUFFER);
    sprintf(szHiScore,"High Score: %i ", score );
    m_HiScoreLabel->setString(szHiScore);
}

void HudLayer::setHiLevel(int level){
    memset(szHiLevel, 0, sizeof(char)* LEN_HILEVEL_DISPLAY_BUFFER);
    sprintf(szHiLevel,"High Level: %i ", level );
    getHiLevelLabel()->setString(szHiLevel);
}

void HudLayer::setScore(int value){
    memset(szScore, 0, sizeof(char)*LEN_SCORE_DISPLAY_BUFFER);
    sprintf(szScore,"Game Score : %i",value);
    m_ScoreLabel->setString(szScore);
    
}

void HudLayer::setLevel(int currentLevel){
    memset(szLevel, 0, sizeof(char)*LEN_CURLEVEL_DISPLAY_BUFFER);
    sprintf(szLevel, "Level :  %i", currentLevel);
    m_LevelLabel->setString(szLevel);
}

void HudLayer::setPlayTime(long mill){
    memset(szPlayTime, 0, sizeof(char)*LEN_PLAYTIME_BUFFER);
    sprintf(szPlayTime,"Seconds: %d ", (int) mill );
    m_PlayTimeLabel->setString(szPlayTime);
}


void HudLayer::setHealth(int health){

    memset(szHealth, 0, sizeof(char)*LEN_CURLEVEL_DISPLAY_BUFFER);
    sprintf(szHealth, " Health :  %i", health);
    m_HealthDisplay->setString(szHealth);
}

void HudLayer::update(float dt){

//    int score = 1000 ;//PersistenceManager::getInstance()->getScore();
//    setScore(score);
//
//    int level = 1; //PersistenceManager::getInstance()->getLevel();
//    std::stringstream ss;
//    ss << "Current Level:") << std::to_string(GameLayer::level);
//    GameManager::getInstance()->setLevel(<#int var#>)
//    setLevel(GameLayer::level);

//    int highLevel = 13 ;//PersistenceManager::getInstance()->getHiLevel();
//    setHiLevel(highLevel);

    long delta = millisecondNow() - startTime;
    setPlayTime(delta);

    // TODO
    int health = this->getShip()->getHealth();
    setHealth(health);
}

void HudLayer::reset()
{
    this->unscheduleUpdate();

    startTime = millisecondNow();

    // save data to store, score level, ...
    this->scheduleUpdate();
    
}

//Label * pausedlabel ;
void HudLayer::menuPauseCallback(Ref* pSender)
{
    static bool action = true;
    if ( action)
    {
        Director::getInstance()->pause();
        const char * msg = "Game Paused";
        pausedlabel = (Label*)CCLabelTTF::create(msg, "Arial.fnt", 128);
        pausedlabel->setPosition(Utils::getMidPoint());
        addChild(pausedlabel);
    }else {
        Director::getInstance()->resume();
        pausedlabel->removeFromParentAndCleanup(true);
    }
    action = !action;
}




