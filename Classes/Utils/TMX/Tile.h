//
//  Tile.hpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#pragma once

#include "Element.h"
//#include "TileSet.h"

namespace dsj {

    class Tile : public Element {

        //GETTERSETTER(TileSet, parentTileSet, ParentTileSet);
        
        GETTERSETTER(int, id, Id);
        GETTERSETTER(std::string, type, Type);
        GETTERSETTER(std::string ,imageSource,ImageSource);
        GETTERSETTER(int, height,Height);
        GETTERSETTER(int, width,Width);

    public:

        Tile();

        Tile(tinyxml2::XMLElement* elementTile);

        Tile ( const Tile& obj);

        void render(cocos2d::Node* node,cocos2d::Vec2 pos, int z);

        virtual ~Tile();
    };
}
