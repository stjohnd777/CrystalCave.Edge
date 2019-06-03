//
//  GameManager.hpp
//  CrystalCave.Edge-mobile
//
//  Created by St John, Daniel J on 5/26/19.
//

#pragma once

#include <string>
#include <vector>
#include <map>


#include "MyMacros.h"
#include "UserData.h"
#include "SceneManager.h"

#include "external/tinyxml2/tinyxml2.h"


class LevelInfo {
    
    public :
    
    LevelInfo(int pos, std::string name,std::string type, std::string desc, std::string tmx):
    m_pos(pos) , m_name(name) , m_type(type),  m_desc(desc), m_tmx(tmx)
    {
        
    }
    
    GETTERSETTER(int, m_pos, Order)
    GETTERSETTER(std::string, m_name, Name)
    GETTERSETTER(std::string, m_type, Type)
    GETTERSETTER(std::string, m_desc, Desc)
    GETTERSETTER(std::string, m_tmx, PathTMX)
};


class LevalStats {
    GETTERSETTER(std::string, m_name, Name)
    GETTERSETTER(bool, m_isLocked, IsLocked)
    GETTERSETTER(std::time_t, m_completedOn, CompletedOn)
    GETTERSETTER(int , m_levelScore, LevelScore)
    GETTERSETTER(int, m_starts, Stars)
};

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
        
        std::string tmx = "Not Defined";
        if ( level < levels.size() ) {
            tmx = levels[level];
        }
        return tmx;
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
    
    
    LevelInfo*  GetLevelInfo(int pos) {
        return level_info[pos];
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
        
        using namespace tinyxml2;
        
        XMLDocument doc;
        int retCode = doc.LoadFile( "TMX-Cave/GameLevelInfo.xml");
        assert(retCode == 0);
        auto elementRoot =doc.RootElement();
        
        auto levelElement = elementRoot->FirstChildElement("level");
        while(levelElement){
            
            int pos = levelElement->IntAttribute("pos");
            std::string name = levelElement->Attribute("name");
            std::string type = levelElement->Attribute("type");
            
            auto desc = levelElement->FirstChildElement("desc")->GetText();
            auto tmx = levelElement->FirstChildElement("tmx")->GetText();
            
            auto levelInof = new LevelInfo(pos,name,type,desc,tmx);
            level_info[pos] =levelInof;
            
            levels.push_back(tmx);
            //log("pso=%d name=%s type=%s  tmx=%s",pos,name.c_str(),type.c_str(),tmx.c_str());
            
            levelElement = levelElement->NextSiblingElement("level");
        }
        
//        levels.push_back("TMX-Cave/test_phy.tmx");//0
//        levels.push_back("TMX-Cave/simplest.tmx");
//        levels.push_back("TMX-Cave/simplest_vert.tmx");
//        levels.push_back("TMX-Cave/template.tmx");
//        levels.push_back("TMX-Cave/level001.tmx");
//        levels.push_back("TMX-Cave/simplest_long.tmx");
//        levels.push_back("TMX-Cave/simplest_full.tmx"); //5
    }
    
    std::vector<std::string> levels ;
    std::map<int,LevelInfo*>  level_info;
};





