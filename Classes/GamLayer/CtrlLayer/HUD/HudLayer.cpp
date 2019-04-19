 
#include "HudLayer.h"
#include "Constants.h"
#include <string>
#include <strstream>
#include "FontManager.h"
#include "GameSceneManager.h"
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

bool HudLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    initBackMenu([](Ref* ref) {
        GameSceneManager::getInstance()->Welcome();
    });

    setTag(GameAssets::Layer::TAG_HUD_LAYER);

    memset(szHiLevel,        0, LEN_HILEVEL_DISPLAY_BUFFER    *sizeof(char));
    memset(szHiScore,        0, LEN_HISCORE_DISPLAY_BUFFER    *sizeof(char));
    memset(szLevel,          0, LEN_CURLEVEL_DISPLAY_BUFFER*sizeof(char));
    memset(szScore,          0, LEN_SCORE_DISPLAY_BUFFER*sizeof(char));
    memset(szPlayTime,       0, LEN_PLAYTIME_BUFFER           *sizeof(char));
    memset(szHealth,         0, LEN_HEALTH_DISPLAY_BUFFER*sizeof(char));

    Size screenSize = Director::getInstance()->getWinSize();
    string HUD_FONT = FontManager::FONT_MSG_DEFAULT;

    // GAME SCORE

    // HI SCORE
    auto positionHiScoreLabel = Vec2( (screenSize.width/2), screenSize.height * 0.92f);
    auto colorHiScoreLabel = Color3B::RED;
    int  scaleHiScoreLabel = 10;

    setHiScoreLabel( Label::createWithBMFont(HUD_FONT,szHiScore));
    getHiScoreLabel()->setScale(10);
    getHiScoreLabel()->setPosition(positionHiScoreLabel);
    getHiScoreLabel()->setScale(scaleHiScoreLabel);
    this->addChild(m_HiScoreLabel);
    //setHiScore(PersistenceManager::getInstance()->getHiScore());

    // HI LEVEL
    auto secondCenter = Vec2( screenSize.width * .25, screenSize.height * 0.92f);
    sprintf(szHiLevel,"High Level: %i ", -99);
    setHiLevelLabel( Label::createWithBMFont( HUD_FONT,szHiLevel));
    getHiLevelLabel()->setAnchorPoint(Vec2(1,0.5));
    getHiLevelLabel()->setPosition(secondCenter) ;
    getHiLevelLabel()->setScale(2);
    getHiLevelLabel()->setColor(Color3B::YELLOW);
    this->addChild(getHiLevelLabel());

    // SCORE
    auto positionScoreLabel = Vec2(screenSize.width/2, screenSize.height * 0.96f);
    auto colorScoreLabel = Color3B::GREEN;
    int scaleScoreLabel = 2;
    auto anchorPointScoreLabel = Vec2(.5,.5);
    setScoreLabel( Label::createWithBMFont(HUD_FONT,"Score : 0"));
    getScoreLabel()->setAnchorPoint(anchorPointScoreLabel);
    getScoreLabel()->setPosition(positionScoreLabel);
    getScoreLabel()->setColor(colorScoreLabel);
    getScoreLabel()->setScale(scaleScoreLabel);
    this->addChild( getScoreLabel());

    // HEALTH
    Point thirdCenter = Vec2( (screenSize.width -128), screenSize.height * 0.96f);
    auto colorHealthLabel = Color3B::GREEN;
    int  scaleHealthLabel = 2;
    setHealthDisplay ( Label::createWithBMFont( HUD_FONT, szHealth) );
    getHealthDisplay()->setScale(scaleHealthLabel);
    getHealthDisplay()->setAnchorPoint(Vec2(1,.5));
    getHealthDisplay()->setPosition(thirdCenter);
    getHealthDisplay()->setColor(colorHealthLabel);
    this->addChild(getHealthDisplay());
    setHealth(100);
    
    // CURRENT LEVEL
    auto possitionLevelLabel = Vec2( screenSize.width * .25, screenSize.height * 0.96f);
    auto anchorLevelLabel = Vec2(1,0.5);
    auto scaleLevelLabel = 2;
    auto colorLevelLabel =Color3B::GREEN;
    int startWithThisLevel = 1;
    sprintf(szLevel,"Level :  %i", startWithThisLevel);
    setLevelLabel( Label::createWithBMFont(HUD_FONT,szLevel));
    getLevelLabel()->setAnchorPoint(anchorLevelLabel);
    getLevelLabel()->setPosition(possitionLevelLabel);
    getLevelLabel()->setScale(scaleLevelLabel);
    getLevelLabel()->setColor(colorLevelLabel);
    this->addChild( getLevelLabel());

    // PLayTime
    startTime = millisecondNow();
    setPlayTimeDisplay (Label::createWithBMFont(HUD_FONT, szPlayTime));
    getPlayTimeDisplay()->setAnchorPoint(Vec2(.5,.5));
    getPlayTimeDisplay()->setPosition(Vec2(screenSize.width *.80f, screenSize.height * 0.86f));
    getPlayTimeDisplay()->setColor(Color3B::WHITE);
    this->addChild(getPlayTimeDisplay());

    // Pause/Play
    MenuItemSprite* item0 = MenuItemSprite::create(
                            Sprite::create("pause.png"),
                            Sprite::create("pause.png"),
                            NULL);
    MenuItemSprite* item1 = MenuItemSprite::create(
                            Sprite::create("play_sel.png"),
                            Sprite::create("play_sel.png"),
                            NULL);

    itemTogglePlayPause = MenuItemToggle::createWithTarget(this,menu_selector(HudLayer::menuPauseCallback)  , item0,item1, NULL);
    
    Menu* menu = Menu::create(itemTogglePlayPause, NULL);
    menu->alignItemsVerticallyWithPadding(32);
    menu->setPosition(Vec2( Utils::getWindowSize().width -128 /2, Utils::getWindowSize().height -128 /2 ) );
    menu->setTag(GameAssets::Layer::TAG_HUD_LAYER);
    this->addChild(menu, 1);

//    PersistenceManager::getInstance()->setScore(0);
//    PersistenceManager::getInstance()->setLevel(1);

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
    sprintf(szHealth, "Health :  %i", health);
    m_HealthDisplay->setString(szHealth);
}

void HudLayer::update(float dt){

    int score = 1000 ;//PersistenceManager::getInstance()->getScore();
    setScore(score);

    int level = 1; //PersistenceManager::getInstance()->getLevel();
    setLevel(level);

    int highLevel = 13 ;//PersistenceManager::getInstance()->getHiLevel();
    setHiLevel(highLevel);

    long delta = millisecondNow() - startTime;
    setPlayTime(delta);

    int health = 100;//Ship::getInstance()->getHealthLevel();
    setHealth(health);
}

void HudLayer::reset()
{
    this->unscheduleUpdate();

    startTime = millisecondNow();

    // save data to store, score level, ...
    this->scheduleUpdate();
    
}

Label * pausedlabel ;
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




