//
//  TileSet.hpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#pragma once


//#include "Element.h"
#include "Tile.h"

namespace dsj {

    class TileSet : public Element {

        GETTERSETTER(std::string, name, Name);

        GETTERSETTER(std::string , orientation,Orientation);
        GETTERSETTER(int, tilecount, TileCount);
        GETTERSETTER(int,firstgid, FirstGrid);
        GETTERSETTER(int, tilewidth, TileWidht);
        GETTERSETTER(int, tileheight, TileHeight);
        GETTERSETTER(int, columns , Columns);

    public:

        TileSet();

        TileSet(tinyxml2::XMLElement* elementTileset);

        TileSet( const TileSet &obj);

        void operator = (const TileSet &obj );

        virtual~TileSet() ;

        Tile GetById(int id);

    protected:
        
        std::vector<Tile> tiles;
    };
}
