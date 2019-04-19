#pragma once

#define LEN_PLAYTIME_BUFFER             255

#define LEN_DIFFICULTY_DISPLAY_BUFFER   100
#define LEN_HILEVEL_DISPLAY_BUFFER      255
#define LEN_HISCORE_DISPLAY_BUFFER      255
#define LEN_DESC_DISPLAY_BUFFER         255

#define LEN_CURLEVEL_DISPLAY_BUFFER     255
#define LEN_SCORE_DISPLAY_BUFFER        255
#define LEN_HEALTH_DISPLAY_BUFFER       255
#define LEN_SHIELD_DISPLAY_BUFFER       255

#include "cocos2d.h"
#include "BaseLayer.h"
#include "GameLayer.h"

class HudLayer : public BaseLayer {

public:

    static HudLayer* INSTANCE ;
public:
    
    CREATE_FUNC(HudLayer);
    
    bool init();
 
    /*
     * Toggel Play/Pause Game Menu
     */
    CC_SYNTHESIZE(cocos2d::MenuItemToggle*, itemTogglePlayPause,ItemTogglePlayPause);

    // Debug
    char szDebug[512];
    CC_SYNTHESIZE(cocos2d::Label*, debugDisplay,DebugDisplay);

    // Persistent stat : HiScore
    char szHiScore[LEN_HISCORE_DISPLAY_BUFFER];
    CC_SYNTHESIZE(cocos2d::Label*, m_HiScoreLabel, HiScoreLabel);
    void setHiScore(int hiScore);

    // Persistent stat :  Hi Level
    char szHiLevel[LEN_HILEVEL_DISPLAY_BUFFER];
    CC_SYNTHESIZE(cocos2d::Label*, m_HiLevellLabel, HiLevelLabel);
    void setHiLevel(int level);

    // Score
    // Real time stat : Score
    char szScore[255];
    CC_SYNTHESIZE(cocos2d::Label*, m_ScoreLabel, ScoreLabel);
    void setScore(int hit);
    void incrementScore(int hit);
    void decrementScore(int hit);

    // Level
    // Real time stat : Level
    char szLevel[LEN_CURLEVEL_DISPLAY_BUFFER];
    CC_SYNTHESIZE(cocos2d::Label*, m_LevelLabel, LevelLabel);
    void setLevel(int level);

    // Play Time
    // Real time stat :PlayTime
    char szPlayTime[ LEN_PLAYTIME_BUFFER ];
    CC_SYNTHESIZE(cocos2d::Label*, m_PlayTimeLabel, PlayTimeDisplay);
    void setPlayTime(long mill);
    //long getPlayTime();

    // Health Status
    // Real time stat : Health
    char szHealth[LEN_HEALTH_DISPLAY_BUFFER];
    CC_SYNTHESIZE(cocos2d::Label*, m_HealthDisplay, HealthDisplay);
    void setHealth(int health);
    void incrementHealth(int health);
    void decrementHealth(int health);


    void startTracking();
    
    void stopTracking();
    
    void update(float dt);
    
    void reset();
    
    /////////////////////////////////////////////////////////////////////

    void menuPauseCallback(cocos2d::Ref* pSender);
    
private:

    
    long startTime;

};

