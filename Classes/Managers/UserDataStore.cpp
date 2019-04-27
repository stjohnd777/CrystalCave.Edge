//
//  UserData.cpp
//  AsteroidTrouble.c2dx.3.5.x86cpu
//
//  Created by Daniel St. John on 10/6/15.
//
//
#include <string>
#include <sstream>
using namespace std;

#include "UserDataStore.h"

using namespace cocos2d;

namespace dsj {
    
    UserData* UserData::INSTANCE = nullptr;
    
    const std::string UserData::KEY_ISPLAYBGMUSIC ="ISPLAYINGBGMUSIC";

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
        int persistedHighScore = UserDefault::getInstance()->getIntegerForKey(key.c_str(),10000);
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


}
//NS_DSJ_END
