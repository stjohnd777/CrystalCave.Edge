//
//  TileSet.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "TileSet.h"
#include <sstream>

using namespace tinyxml2;

namespace dsj {

    TileSet::TileSet(){ }

    TileSet::TileSet( XMLElement* elementTileset) : Element(elementTileset){

        cocos2d::log("TileSet::TileSet Enter");

        int counter = 0;
        assert(elementTileset);

        this->name =elementTileset->Attribute("name");
        assert(this->name.c_str());
        cocos2d::log("%s", this->name.c_str());

        auto tilecount = elementTileset->Attribute("tilecount");
        assert(tilecount);
        this->tilecount = std::stoi(tilecount);
        cocos2d::log("%s", tilecount);

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
                auto tile = new Tile (elementTile);
                tile->setParentTileSet(this);
                tiles.push_back(tile);
            }catch(...){
                std::exception_ptr p = std::current_exception();
                cocos2d::log("Error TileSet:");
            }

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


    Tile* TileSet::GetById(int id){
        cocos2d::log("TileSet::GetById(%i) Enter", id);
        for (auto tile : tiles){
            if ( tile->getId() == id ){
                cocos2d::log("TileSet::GetById Exit");
                cocos2d::log("TileSet::GetById Found tile\n %s", tile->to_string().c_str());
                return tile;
            }
        }
        cocos2d::log("TileSet::GetById Not Found%i",id);
        cocos2d::log("TileSet::GetById Exit");
        return nullptr;
    }


    const std::string TileSet::to_string(){
        std::stringstream ss ;

        ss << "TileSet : {\n";
        ss << Element::to_string() ;
        ss << "  name:" << name << "\n";
        ss << "  tilecount:" << tilecount << "\n";
        ss << "  firstgid:" << firstgid << "\n";
        ss << "  tilewidth:" << tilewidth << "\n";
        ss << "  tileheight:" << tileheight << "\n";
        ss << "  columns:" << columns << "\n";
        for (auto tile : tiles){
            ss << "  " << tile->to_string() << "\n";
        }
        ss << "}";

        return ss.str();
    }


   std::ostream& operator<<(std::ostream& strm,  TileSet& t){
        return strm << t.to_string();
    }

    TileSet::~TileSet() {
        cocos2d::log("TileSet::~TileSet() Enter");
        for ( auto ptrTile : tiles) {
            cocos2d::log("delete Tile with id %s and type %s ",ptrTile->getId(),ptrTile->getType().c_str());
            delete ptrTile;
        }
        tiles.clear();
        cocos2d::log("TileSet::~TileSet() Exit");
    }

}
