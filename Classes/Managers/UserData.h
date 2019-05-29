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

#include "cocos2d.h"



    class UserData{
        
    public:
        
        static UserData* getInstance();

        static const std::string KEY_ISPLAYBGMUSIC;
        static const std::string KEY_RESUME_LEVEL;


        static const std::string KEY_SCORE;
        static const std::string KEY_LEVEL;

        static const std::string KEY_HISCORE;
        static const std::string KEY_HILEVEL;
        
    public:
        
        void setIsPlayingBackgoundMusic(bool b);
        
        bool getIsPlayingBackgoundMusic();

        /**
         * Get the last level the player was playing
         * when exiint the game, the default is to
         * pisk up were you left off from. This may be
         * different from the hightest level. In some sense
         * if the game is exploration there is not hightest
         * level.
         */
        int getResumeLevel();

        /**
         * Last level played
         */
        void setResumeLevel(int level);


        void saveLevelStats(
                int level,
                int levelTime,
                int score,
                int stars,
                bool isCompleted
                );
        
        bool isLevelOpen(int level);


        void save();


        void setScore(int score);
        void incrementScore( int value);
        int getScore();

        void setLevel(int lev);
        int getLevel();

        void setHighScore( int highScore);
        int getHighScore( );

        void setHighLevel(  int highLevel);
        int getHighLevel ();
        

    private:

        int m_Score;
        
        int m_Level;
        
        float m_Sensitivity;
        
        static UserData* INSTANCE;
        
        UserData();
        
    };
 
