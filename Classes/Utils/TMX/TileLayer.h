//
//  TileLayer.hpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#pragma once

#include "Element.h"
#include "Tile.h"

namespace dsj {

 
class TileLayer : public Element {

    GETTERSETTER(int,id,Id)
    GETTERSETTER(std::string,name,Name)
    GETTERSETTER(int,width,Width)
    GETTERSETTER(int,height,Height)
    GETTERSETTER(std::string,data,Data)
    GETTERSETTER(int,z,Z)

public:

    TileLayer();

    TileLayer(tinyxml2::XMLElement* elementLayer);

    TileLayer( const TileLayer &obj);

    TileLayer& operator = (const TileLayer &t);

    //void forEach(std::function<void( Tile tile)> );

    int getTileId(int row, int col) {
        int index = row* width + col;
        return vdata.at(index);
        //return _data[row][col];
    }


    void render(cocos2d::Node* target,int z = 0);

    ~TileLayer();

protected:

    //int** _data;

    std::vector<int> vdata;

public:
    const std::string to_string();

private:
    friend std::ostream& operator<<(std::ostream& strm,  TileLayer& o);
};

}
