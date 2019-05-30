//
//  GameManager.hpp
//  CrystalCave.Edge-mobile
//
//  Created by St John, Daniel J on 5/26/19.
//

#pragma once

#include <string>
#include <vector>

#include "UserData.h"
#include "SceneManager.h"
class GameManager {

    
public:
    
    //static GameManager* getInstance();
    static GameManager* getInstance()
    {
        static GameManager *INSTANCE = new GameManager();
        
        return INSTANCE;
    }
    
    //std::string  getTmx(int level);
    std::string  getTmx(int level){
        return levels[level];
    }
    
    //bool isLevelOpen(int level);
    /**
     * Level N is open if and only if level (N-1)
     * has been completed.
     *
     * Or the level has been entered if the mode is
     * open world discovery
    */
    bool isLevelOpen(int level){
        
        bool isOpen = false;
        
        if ( level > 0){
            
            bool prevoisLevelComplete= UserData::getInstance()->isLevelOpen(level-1);
            
            bool hasBeenHere = UserData::getInstance()->isLevelOpen(level);
            
            isOpen = hasBeenHere || prevoisLevelComplete;
        }else {
            isOpen = true;
        }
      
        return isOpen;
    }

    
    //int getResumeLevel();
    int  getResumeLevel(){
        int level = UserData::getInstance()->getResumeLevel();
        return level;
    }
    
    //void LevelComplete() ;
    void  LevelComplete() {
        int level = m_level;
        int levelTime = 0; // TODO
        int score = 0; // TODO
        int stars = 0; // TODO
        bool isCompleted = true;
        UserData::getInstance()->saveLevelStats(level, levelTime, score, stars, isCompleted);
        UserData::getInstance()->setResumeLevel(level+1);
    }
    
    
    
    
    //void LoadNextLevel() ;
    void  LoadFirstLevel() {
        m_level = 0;
        std::string tmx = levels[0];
        SceneManager::getInstance()->Game(tmx);
    }
    
    
    //void LoadNextLevel() ;
    void  ResumeLevel() {
        std::string tmx = levels[m_level];
        SceneManager::getInstance()->Game(tmx);
    }
    
    //void LoadNextLevel() ;
    /**
     *
     */
    void  LoadNextLevel() {
        m_level ++;
        UserData::getInstance()->setResumeLevel(m_level);
        UserData::getInstance()->saveLevelStats(m_level, 0, 0, 0, 0);
        std::string tmx = levels[m_level];
        SceneManager::getInstance()->Game(tmx);
    }
    
    //void LoadLevel(int level) ;
    void  LoadLevel(int level) {
        m_level = level;
        std::string tmx = levels[m_level];
        SceneManager::getInstance()->Game(tmx);
        
    }
    
    int getLevel() {
        return m_level;
    }
    
    void setLevel(int level) {
         m_level = level;
    }
  

private :

    
    
    int  m_level  = 0;
    
    //GameManager();
    GameManager (){
        levels.push_back("TMX-Cave/test_phy.tmx");
        levels.push_back("TMX-Cave/simplest.tmx");
        levels.push_back("TMX-Cave/template.tmx");
        levels.push_back("TMX-Cave/level001.tmx");
        levels.push_back("TMX-Cave/simplest_long.tmx");
        levels.push_back("TMX-Cave/simplest_full.tmx");
    }
    
    std::vector<std::string> levels ;
};



//class LevalInfo {
//
//    GETTERSETTER(int, m_order, Order)
//    GETTERSETTER(std::string, m_desc, Desc)
//    GETTERSETTER(std::string, m_tmx, PathTMX)
//    GETTERSETTER(bool, m_isLocked, IsLocked)
//    GETTERSETTER(std::time_t, m_completedOn, CompletedOn)
//    GETTERSETTER(int , m_levelScore, LevelScore)
//    GETTERSETTER(int, m_starts, Stars)
//
//};
//
//
//class LevalStats {
//    GETTERSETTER(std::string, m_name, Name)
//    GETTERSETTER(bool, m_isLocked, IsLocked)
//    GETTERSETTER(std::time_t, m_completedOn, CompletedOn)
//    GETTERSETTER(int , m_levelScore, LevelScore)
//    GETTERSETTER(int, m_starts, Stars)
//};
