//
//  TileLayer.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "TileLayer.h"

using namespace tinyxml2;

namespace dsj {

//    std::vector<std::string> split(const char *str,  char c = ' ')
//    {
//        std::vector<std::string> result;
//        do {
//            const char *begin = str;
//            while(*str != c && *str) str++;
//            result.push_back(std::string(begin, str));
//        } while (0 != *str++);
//        return result;
//    }

    TileLayer::TileLayer(){}

    TileLayer::TileLayer( XMLElement* elementLayer) :  Element(elementLayer){

        this-> id = std::stoi ( elementLayer->Attribute("id") );
        this-> name = elementLayer->Attribute("name");

        this-> width  = std::stoi ( elementLayer->Attribute("width") );
        this-> height = std::stoi (elementLayer->Attribute("height") );

        XMLElement* dataElement = elementLayer->FirstChildElement(Elements::DATA);

        this->data = dataElement->GetText();

        cocos2d::log(this->data.c_str());

//        int data[width][height];
//        //this->_data = (int**)data;
//        int r = 0;
//        int c = 0;
//        auto rows = dsj::split(this->data.c_str(),'/n');
//        for( auto row : rows){
//            auto cols = dsj::split(row.c_str(),',');
//            for ( auto col : cols){
//                int tileID = std::stoi(col);
//                data[r][c] = tileID;
//                //_data[r][c] = tileID;
//                dsj::Cell cell(r,c);
//                this->mapTiles[cell] =tileID;
//                c++;
//            }
//            r++;
//        }

    }

    TileLayer::TileLayer( const TileLayer &obj) : Element(obj){

         this->id = obj.id;

         this->id = obj.id;
         this->name = obj.name;
         this->width = obj.width;
         this->height = obj.height;
         this->data = obj.data;
         this->mapTiles = obj.mapTiles;
    }
    void TileLayer::forEach(std::function<void( Tile tile)>  func ) {

        for (auto p : mapTiles) {
            Cell c = p.first;
            int tileId = p.second;
            //func(t);
        }
    }

    void TileLayer::render(cocos2d::Node* target){

        for (auto p : mapTiles) {

            Cell c = p.first;
            int tileId = p.second;

//            parent.forEachTileSet( [&]( TileSet tileset){
//
//                auto tile = tileset.GetById(tileId);
//            });

            //auto props = t.getProperties();
//
//
//            std::string source = t.getImageSource();
//
//            auto sprite = cocos2d::Sprite::create(source);
//            sprite->setAnchorPoint(cocos2d::Vec2(0,0));
//            float x = c.getRow() * this->width;
//            float y = c.getCol() * this->height;
//            cocos2d::Vec2 pos(x,y);
//            sprite->setPosition(pos);
//
//            target-> addChild(sprite);



        }

    }

    TileLayer::~TileLayer(){}
}
