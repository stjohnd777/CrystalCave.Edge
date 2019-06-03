//
//  GameManager.cpp
//  CrystalCave.Edge-mobile
//
//  Created by St John, Daniel J on 5/26/19.
//

#include "GameManager.h"


#include <iostream>
#include <chrono>
#include <ctime>

#include "UserData.h"
#include "SceneManager.h"

//GameManager *GameManager::INSTANCE = NULL;


//static GameManager::GameManager* getInstance()
//{
//    static GameManager *INSTANCE = new GameManager();
//    
//    return INSTANCE;
//}

//std::string GameManager::getTmx(int level){
//    assert(levels[level]);
//    return levels[level];
//}

//bool GameManager::isLevelOpen(int level){
//    return UserData::getInstance()->isLevelOpen(level);
//}


//int GameManager::getResumeLevel(){
//    int level = UserData::getInstance()->getResumeLevel();
//    return level;
//}



//void GameManager::LevelComplete() {
//    int level = m_level;
//    int levelTime = 0; // TODO
//    int score = 0; // TODO
//    int stars = 0; // TODO
//    bool isCompleted = true;
//    UserData::getInstance()->saveLevelStats(level, levelTime, score, stars, isCompleted);
//    UserData::getInstance()->setResumeLevel(level+1);
//}


//void GameManager::LoadLevel(int level) {
//    m_level = level;
//    UserData::getInstance()->setResumeLevel(m_level);
//    UserData::getInstance()->saveLevelStats(m_level, 0, 0, 0, 0);
//    SceneManager::getInstance()->Game(m_level);
//
//}


//void GameManager::LoadNextLevel() {
//    m_level ++;
//    UserData::getInstance()->setResumeLevel(m_level);
//    UserData::getInstance()->saveLevelStats(m_level, 0, 0, 0, 0);
//    SceneManager::getInstance()->Game(m_level);
//}


//GameManager::GameManager(){
//    levels.push_back("TMX-Cave/simplest.tmx");
//    levels.push_back("TMX-Cave/templates.tmx");
//    levels.push_back("TMX-Cave/simplest_long.tmx");
//    levels.push_back("TMX-Cave/simplest_full.tmx");
//}



