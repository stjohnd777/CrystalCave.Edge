//
//  TileSet.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "TileSet.h"

using namespace tinyxml2;

namespace dsj {

    TileSet::TileSet(){ }

    TileSet::TileSet( XMLElement* elementTileset) : Element(elementTileset){

        cocos2d::log("TileSet::TileSet Enter");

        int counter = 0;
        assert(elementTileset);

        this->name =elementTileset->Attribute("name");
        assert(this->name.c_str());
        cocos2d::log(this->name.c_str());

        auto tilecount = elementTileset->Attribute("tilecount");
        assert(tilecount);
        this->tilecount = std::stoi(tilecount);
        cocos2d::log(tilecount);

        auto tilewidth = elementTileset->Attribute("tilewidth");
        assert(tilewidth);
        this->tilewidth =std::stoi(tilewidth);

        auto tileheight = elementTileset->Attribute("tileheight");
        assert(tileheight);
        this->tileheight =std::stoi(tileheight);

        auto elementGrid = elementTileset->FirstChildElement("grid");
        assert(elementGrid);
        this->orientation = elementGrid->Attribute("orientation");
        assert(orientation.c_str());

         cocos2d::log("TileSet name %s",this->name.c_str());

        auto elementTile = elementTileset->FirstChildElement(Elements::TILE);
        while (elementTile) {
            counter ++;
            cocos2d::log("TileSet %s : %i" , this->name.c_str() , counter);
            try{
                Tile tile(elementTile);
                //tile.setParentTileSet(this)
            }catch(...){
                std::exception_ptr p = std::current_exception();
                cocos2d::log("Error TileSet:");
                //cocos2d::log("Error TileSet: %s" , p.what());
            }
            tiles.push_back(elementTile);
            elementTile = elementTile->NextSiblingElement(Elements::TILE);
        }

        cocos2d::log("TileSet::TileSet Exit");
    }


    TileSet::TileSet( const TileSet &obj) : Element(obj){

        this->name = obj.name;
        this->orientation = obj.orientation;
        this->tilecount = obj.tilecount;
        this->firstgid = obj.firstgid;
        this->name = obj.tilewidth;
        this->orientation = obj.tileheight;
        this->columns = obj.columns;

        this->tiles = obj.tiles;
    }

    void TileSet::operator = (const TileSet &obj ){

        // TODO examin this 
        this->name = obj.name;
        this->orientation = obj.orientation;
        this->tilecount = obj.tilecount;
        this->firstgid = obj.firstgid;
        this->name = obj.tilewidth;
        this->orientation = obj.tileheight;
        this->columns = obj.columns;

        this->tiles = obj.tiles;

    }


    Tile TileSet::GetById(int id){

        for (auto tile : tiles){
            if ( tile.getId() == id ){
                return tile;
            }
        }
        return nullptr;
    }
    
    TileSet::~TileSet() {

    }

}
