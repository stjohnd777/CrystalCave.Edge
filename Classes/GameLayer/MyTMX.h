//
//  TMX.hpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 4/17/19.
//

#pragma once

#include <string>
#include <map>

#include "cocos2d.h"

#include "MyMacros.h"
#include "LunarModule.h"
#include "HudLayer.h"
#include "CtrlLayer.h"


class MyTMX : public cocos2d::Layer  {
    
public:

    static cocos2d::Scene* scene(
                                 std::string tmx,
                                 cocos2d::Vec2 g = cocos2d::Vec2(0,-10) );

    static MyTMX* create( std::string tmx);

    bool init(std::string tmx) ;

    MyTMX();

private:

    cocos2d::DrawNode * drawNode;

    bool isKeyDown;
    bool m_IsTouching;
    LunarModule* ship;
    HudLayer* m_HudLayer;
    CtrlLayer* m_CtrlLayer;
    cocos2d::EventKeyboard::KeyCode gkeyCode ;


    ATTR(std::string, tmxFileName, TmxFileName,"")
    ATTR(int, columns, Columns,0)
    ATTR(int, rows, Rows,0)
    ATTR(int, tileSize, TileSize,64)
    int mapHeightPixels ;
    int mapWidhtPixels ;

    ATTR(cocos2d::Vec2, m_gravity, Gravity, cocos2d::Vec2(0,-10))
    cocos2d::PhysicsWorld* phyWorld;

    cocos2d::TMXTiledMap* tiled_map;


    #if IS_DESKTOP
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    #endif
};


