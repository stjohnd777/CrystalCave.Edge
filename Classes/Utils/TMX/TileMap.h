//
//  dsjTMXMap.cpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 4/29/19.
//
#pragma once

#include "cocos2d.h"
//#include "Sillymutts.h"

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


    public :

        static TileMap* getInstance() ;

   private :

        cocos2d::DrawNode* drawNode;

        static TileMap* INSTANCE;

        GETTERSETTER(std::string,pathTmx,PathTmx)

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


//        std::vector<Object*> getObjectsByProperties(std::vector<Property> matchProps){
//            std::vector<Object*> objs;
//            return objs;
//        }
//        std::vector<Object*> getObjectsByAttributes(std::vector<Attribute> matchMatchAttry){
//            std::vector<Object*> objs;
//            return objs;
//        }
//
//
//        std::vector<Tile*> getTileByName(std::string name){
//            std::vector<Tile*> objs;
//            return objs;
//        }
//        std::vector<Tile*> gettileByType(std::string type){
//            std::vector<Tile*> objs;
//            return objs;
//        }
//        std::vector<Tile*> getTileByProperties(std::vector<Property> matchProps){
//            std::vector<Tile*> objs;
//            return objs;
//        }
//        std::vector<Tile*> getTileByAttributes(std::vector<Attribute> matchMatchAttry){
//            std::vector<Tile*> objs;
//            return objs;
//        }




        TileLayer* getLayerByName(std::string name);

        TileSet*  getTilesetByName(std::string name);

        ObjectGroup* getObjectGroupByName(std::string name);

        std::vector<TileLayer*> getLayers();

        std::vector<TileSet*> getTilesets();

        std::vector<ObjectGroup*> getObjectGroups();

        Tile* getTileById(int tileId);

        std::vector<Tile*> getTilesAt(int row,int col);

        cocos2d::Vec2 GetPixelCoordinates(int row,int col);

        void forEachLayer(std::function<void( TileLayer* tileLayer)> );
        void forEachObjectGroup(std::function<void( ObjectGroup* objectGroup)> func);
        void forEachTileSet( std::function<void( TileSet* tileSet)> func);


        std::vector<Object*> getObjectsByName(std::string name);
        std::vector<Object*> getObjectsByType(std::string type);

        void render(cocos2d::Node* target);

        std::string to_string();

    protected:


        std::map<std::string,TileSet*> m_tilesets;

        std::map<std::string,TileLayer*> m_layers;

        std::map<std::string,ObjectGroup*> m_objectGroups;


    public:

        virtual ~TileMap();

    };
}

