//
//  Tile.hpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#pragma once

#include "Element.h"




namespace dsj {

    class TileSet;
    
    class Tile : public Element {

        GETTERSETTER(TileSet*, parent, ParentTileSet);
        
        GETTERSETTER(int, id, Id);
        GETTERSETTER(std::string, type, Type);
        GETTERSETTER(std::string ,imageSource,ImageSource);
        GETTERSETTER(int, height,Height);
        GETTERSETTER(int, width,Width);


    public:

        std::vector<std::function<void( Tile* sender)>> vistors ;

        void executeVisitor(){
            
        };

        Tile();

        Tile(tinyxml2::XMLElement* elementTile);

        Tile ( const Tile& obj);

        void render(cocos2d::Node* node,int row, int col, int z );

        virtual ~Tile();

        const std::string to_string();

    private:
        friend std::ostream& operator<<(std::ostream&, const Tile&);
    };
}
