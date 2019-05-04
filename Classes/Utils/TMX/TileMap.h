//
//  dsjTMXMap.cpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 4/29/19.
//
#pragma once

#include "cocos2d.h"

#include <string>
#include <vector>
#include <map>
#include "external/tinyxml2/tinyxml2.h"


#include "Element.h"
#include "ObjectGroup.h"
#include "Object.h"
#include "TileLayer.h"
#include "TileSet.h"
#include "Tile.h"



namespace dsj {
    
    class TileMap : public Element {

        GETTERSETTER(std::string,version,Version)
        GETTERSETTER(std::string,tiledversion,TiledVersion)

        GETTERSETTER(std::string,orientation,Orientation)
        GETTERSETTER(int,width,Width)
        GETTERSETTER(int,height,Height)
        GETTERSETTER(int,tileWidth,TileWidth)
        GETTERSETTER(int,tileHieght,TileHeight)
        GETTERSETTER(std::string,renderorder,Renderorder)
        GETTERSETTER(std::string,infinite,Infinite)
        GETTERSETTER(std::string,extlayerid,Extlayerid)
        GETTERSETTER(std::string,nextobjectid,NextObjectId)

    public:

        TileMap(std::string pathTmx);

    public:

        TileLayer getLayerByName(std::string name);

        TileSet  getTilesetByName(std::string name);

        ObjectGroup getObjectGroupByName(std::string name);

        std::vector<TileLayer> getLayers();

        std::vector<TileSet> getTilesets();

        std::vector<ObjectGroup> getObjectGroups();

        Tile getTile(int row , int col);

        cocos2d::Vec2 GetPixelCoordinates(int row,int col);

        void forEachLayer(std::function<void( TileLayer tileLayer)> );

        void forEachObjectGroup(std::function<void( ObjectGroup objectGroup)> func);
        
        void forEachTileSet(std::function<void( TileSet tile)> func);

        void render(cocos2d::Node* target);

    protected:

        std::map<std::string,TileSet> m_tilesets;

        std::map<std::string,TileLayer> m_layers;

        std::map<std::string,ObjectGroup> m_objectGroups;

    public:

        virtual ~TileMap();

    };
}

