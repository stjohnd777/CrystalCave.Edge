//
//  GameManager.hpp
//  CrystalCave.Edge-mobile
//
//  Created by St John, Daniel J on 5/26/19.
//

#pragma once

#include <string>
#include <vector>

#include "MyMacros.h"

class GameManager {

    ATTR(int, m_level, Level,0);
    
public:

    
    static GameManager* getInstance()
    {
        static GameManager *INSTANCE = new GameManager();
    
        return INSTANCE;
    }
    
    
    std::string  getTmx(int level){
        
        return levels[level];
    }
    
    bool isLevelOpen(int level){
        return false;
    }
    
    
   GameManager(){
        
        levels.push_back("TMX-Cave/simplest.tmx");
        levels.push_back("TMX-Cave/simplest_long.tmx");
        levels.push_back("TMX-Cave/simplest_full.tmx");
    }
    
private :
    
    
    std::vector<std::string> levels ;
};
