//
//  UserData.hpp
//  AsteroidTrouble.c2dx.3.5.x86cpu
//
//  Created by Daniel St. John on 10/6/15.
//
//

#pragma once

#include <string>
#include <map>

#include "MyMacros.h"
#include "cocos2d.h"

namespace dsj {

    class UserData{
        
    public:
        
        static UserData* getInstance();

        static const std::string KEY_ISPLAYBGMUSIC;

        static const std::string KEY_SCORE;
        static const std::string KEY_LEVEL;

        static const std::string KEY_HISCORE;
        static const std::string KEY_HILEVEL;
        
    public:
        
        void setIsPlayingBackgoundMusic(bool b);
        
        bool getIsPlayingBackgoundMusic();

        void setScore(int score);
        
        void incrementScore( int value);
        
        int getScore();

        void setLevel(int lev);
        
        int getLevel();

        void setHighScore( int highScore);

        int getHighScore( );

        void setHighLevel(  int highLevel);

        int getHighLevel ();
        
        void save(){
            cocos2d::UserDefault::getInstance()->flush();
        }

    private:

        int m_Score;
        int m_Level;
        float m_Sensitivity;
        
        static UserData* INSTANCE;
        
        UserData();
        
    };
}
//NS_DSJ_END
