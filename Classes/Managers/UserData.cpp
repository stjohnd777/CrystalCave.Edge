//
//  UserData.cpp
//  AsteroidTrouble.c2dx.3.5.x86cpu
//
//  Created by Daniel St. John on 10/6/15.
//
//
#include "UserData.h"

#include <string>
#include <sstream>
using namespace std;



using namespace cocos2d;


    
    UserData* UserData::INSTANCE = nullptr;
    
    const std::string UserData::KEY_ISPLAYBGMUSIC ="ISPLAYINGBGMUSIC";
    const std::string UserData::KEY_RESUME_LEVEL = "KEY_RESUME_LEVEL";

    const std::string UserData::KEY_SCORE = "CURRENT_SCORE";
    const std::string UserData::KEY_LEVEL = "CURRENT_LEVEL";
    const std::string UserData::KEY_HISCORE = "_HI_SCORE";
    const std::string UserData::KEY_HILEVEL = "_HI_LEVEL";


    UserData*  UserData::getInstance(){
        if ( INSTANCE == nullptr){
            INSTANCE = new UserData();
        }
        return INSTANCE;
    }


    UserData::UserData(){
        m_Score = 0;
        m_Level = 1;
    }

    
    void UserData::setIsPlayingBackgoundMusic(bool b){
        UserDefault::getInstance()->setBoolForKey(KEY_ISPLAYBGMUSIC.c_str(),b);
        UserDefault::getInstance()->flush();
    }

    bool UserData::getIsPlayingBackgoundMusic(){
        return UserDefault::getInstance()->getBoolForKey(KEY_ISPLAYBGMUSIC.c_str());
    }
    
    
    int UserData::getResumeLevel(){
        int level = UserDefault::getInstance()->getIntegerForKey(KEY_RESUME_LEVEL.c_str(),0);
        return level;
    }
    
    
    void UserData::setResumeLevel(int level){
        UserDefault::getInstance()->setIntegerForKey(KEY_RESUME_LEVEL.c_str(),level);
    }
    
    
    void  UserData::saveLevelStats(
                        int level,
                        int levelTime,
                        int score,
                        int stars,
                        bool isCompleted
                                   ){
        
        std::stringstream ss;
        ss << "IS_LEVEL_" << level <<  "_OPEN";
        const char* is_open_key = ss.str().c_str();
        UserDefault::getInstance()->setBoolForKey(is_open_key, true);
        ss.clear();
        
    }
    
    
    bool UserData::isLevelOpen(int level) {
        std::stringstream ss;
        ss << "IS_LEVEL_" << level <<  "_OPEN";
        const char* key = ss.str().c_str();
        bool isOpen = UserDefault::getInstance()->getBoolForKey(key,false);
        return isOpen;
    }
    
    
    
    void save(){
        cocos2d::UserDefault::getInstance()->flush();
    }
    
    
    


    void UserData::setScore(int score){
        m_Score = score;
    }

    void UserData::incrementScore(int value){
        m_Score = m_Score+ value;
    }

    int UserData::getScore(){
        return m_Score;
    }

    void UserData::setLevel(int lev){
        m_Level = lev;
    }

    int UserData::getLevel(){
        return m_Level;
    }


    
    
    
    
    
    
    
    void UserData::setHighScore( int highScore)
    {
        std:string key = UserData::KEY_HISCORE;
        UserDefault::getInstance()->setIntegerForKey(key.c_str(), highScore);
        UserDefault::getInstance()->flush();
    }

    int UserData::getHighScore( )
    {
        int ret = 0;
        std:string key = UserData::KEY_HISCORE;
        int persistedHighScore = UserDefault::getInstance()->getIntegerForKey(key.c_str(),0);
        int currentScore = getScore();

        if( currentScore > persistedHighScore){
            setHighScore(currentScore);
            ret = currentScore;
        } else{
            ret = persistedHighScore;
        }
        return ret;
    }


    void UserData::setHighLevel(  int highLevel)
    {
        std::string key =  UserData::KEY_HILEVEL;
        UserDefault::getInstance()->setIntegerForKey(key.c_str(), highLevel);
        UserDefault::getInstance()->flush();
    }

    int UserData::getHighLevel()
    {
        int ret = 0;
        std::string key = UserData::KEY_HILEVEL;
        int persistedHighLevel = UserDefault::getInstance()->getIntegerForKey(key.c_str(),5);

        int level = getLevel();
        if ( level > persistedHighLevel){
            setHighLevel(level);
            ret = level;
        } else {
            ret =persistedHighLevel;
        }
        return ret;
    }


 
