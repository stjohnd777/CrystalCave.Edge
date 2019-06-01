//
//  LevelSelectLayer.hpp
//  CrystalCave.Edge-mobile
//
//  Created by St John, Daniel J on 5/28/19.
//

#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "cocos2d.h"
#include "Utils.h"
#include "BaseLayer.h"
#include "GameManager.h"
#include "SoundManager.h"

class LevelSelectLayer : public BaseLayer {
    
//    ATTR(int, m_ROW, Rows,3)
//    ATTR(int, m_COL, Cols,3)
    
public:
    
    //static cocos2d::Scene* scene();
    static Scene*  scene() {
        
        Scene *scene = Scene::create();
        
        auto *layer = LevelSelectLayer::create();
        
        scene->addChild(layer);
        
        return scene;
    }
    
    //static LevelSelectLayer* create();
    static LevelSelectLayer* create()
    {
        LevelSelectLayer *pRet = new(std::nothrow) LevelSelectLayer();
       
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    
    LevelSelectLayer() {
        
    }
    
    bool init(){
        
        using namespace cocos2d;
        
        auto f = [](Ref* ref){
            SceneManager::getInstance()->Welcome();
        };
        
        // Back Menu
        initBackMenu(f);
        
        auto size = Director::getInstance()->getWinSize();
        
        //int divisionX = 256; //size.width /3;//m_ROW;
        //int divisionY = 256;//size.width /3;//m_Col;
        
        int x = size.width / 256;
        int y = size.height / 256;
        
        auto layer = Layer::create();
        
        int level = 0;
        
        for ( int row = 0 ; row < y ; row ++){
            
            for ( int col = 1 ; col < x ; col ++){
                
                Point p ( col * 256 , size.height -  row * 256 );
                auto levelSprite = Sprite::create(GameAssets::Sprite::LEVEL_BG);
                auto sizeLevelSprite = levelSprite->getContentSize();
                levelSprite->setAnchorPoint(Vec2(0,1));
                levelSprite->setPosition(p);
              
                stringstream ss;
                std::string tmx = GameManager::getInstance()->getTmx(level);
                ss << "Order " << level << ":" <<  tmx << std::endl << "Name" <<   std::endl << "Deccription:  " << std::endl << "Score : 10000" <<  std::endl << "Time: 12345 sec" << std::endl;
                string font =  GameAssets::Fonts::BMF::ALPHA_NUM::FUTURA_48;
                string co =  ss.str();
                auto* levelLabel = Label::createWithBMFont( font,co);
                levelLabel->setAnchorPoint(Vec2(.5,1));
                levelLabel->setPosition( Vec2(sizeLevelSprite.width/2, sizeLevelSprite.height/2 ) );
                levelSprite->addChild(levelLabel, 99);
                

                bool isLevelOpen = GameManager::getInstance()->isLevelOpen(level);
                
                if ( isLevelOpen) {
                    
                    auto star0 = Sprite::create(GameAssets::Sprite::STAR_ON);
                    auto startSize =star0->getContentSize();
                    
                    auto star1 = Sprite::create(GameAssets::Sprite::STAR_ON);
                    star1->setPosition( Vec2(sizeLevelSprite.width/2 - startSize.width ,   sizeLevelSprite.height - startSize.height) );
                    auto star2 = Sprite::create(GameAssets::Sprite::STAR_ON);
                    star2->setPosition( Vec2( sizeLevelSprite.width/2 , sizeLevelSprite.height - startSize.height) );
                    auto star3 = Sprite::create(GameAssets::Sprite::STAR_OFF);
                    star3->setPosition( Vec2( sizeLevelSprite.width/2+ + startSize.width ,sizeLevelSprite.height - startSize.height)  );
                    
                    levelSprite->addChild(star1,99);
                    levelSprite->addChild(star2,99);
                    levelSprite->addChild(star3,99);
                    
                    
                    // if open
                    MenuItemImage *miOpenLevel = MenuItemImage::create(
                                 GameAssets::Sprite::BTN_PLAY,
                                 GameAssets::Sprite::BTN_PLAY_SEL,
                                 [level](Ref*) {
                                     static int s_level = level;
                                     GameManager::getInstance()->LoadLevel(s_level);
                                 } );
                    miOpenLevel->setPosition(Vec2( 256/2 -80 , 256/2 -80 ));
                    Menu* mOpenLevel = Menu::create(miOpenLevel, nullptr);
                    levelSprite->addChild(mOpenLevel);
                
                } else {
                     // if locked
                    MenuItemImage *miLockedLevel = MenuItemImage::create(
                                  GameAssets::Sprite::BTN_LOCKED,
                                  GameAssets::Sprite::BTN_LOCKED_SEL,
                                  [&](Ref*) {
                                      SoundManager::bell();
                                  } );
                    miLockedLevel->setPosition(Vec2( 256/2 -80 , 256/2 -80 ));
                    Menu* mLockedLevel = Menu::create(miLockedLevel, nullptr);
                    levelSprite->addChild(mLockedLevel);
                }
            
                Utils::setSize(levelSprite,256,256);
                layer -> addChild(levelSprite);
                
                level++;
            }
            
        }
        layer->setAnchorPoint(Vec2( 0,0));
        //layer->setScale(.5);
        layer->setPosition(Vec2(0,0)); // Utils::getMidPoint() );
        addChild(layer);
        return true;
    }
    
protected:
    
    void NextPage();
    
    void PreviosPage();
    
};
