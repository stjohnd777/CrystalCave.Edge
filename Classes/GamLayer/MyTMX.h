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

class MyTMX : public cocos2d::Layer  {
    
public:

    static cocos2d::Scene* scene(
                                 std::string tmx,
                                 cocos2d::Vec2 g = cocos2d::Vec2(0,-10) );

    static MyTMX* create( std::string tmx);

    bool init(std::string tmx) ;

public:

    MyTMX();

private:

    std::map<std::string , cocos2d::TMXLayer*>       tmxLayersMap;

    std::map<std::string , cocos2d::TMXObjectGroup*> tmxObjectsMap;


    ATTR(std::string, tmxFileName, TmxFileName,"")

    ATTR(int, columns, Columns,0)

    ATTR(int, rows, Rows,0)

    ATTR(int, tileSize, TileSize,64)

    int mapHeightPixels ;

    int mapWidhtPixels ;

    ATTR(cocos2d::Vec2, m_gravity, Gravity, cocos2d::Vec2(0,-10))

    cocos2d::PhysicsWorld* phyWorld;

    cocos2d::TMXTiledMap* tiled_map;


    void handleTMXPhysicsLayer(cocos2d::TMXLayer* base);

    void handleTMXObjectLayer(cocos2d::TMXObjectGroup * objectGroup);

};


