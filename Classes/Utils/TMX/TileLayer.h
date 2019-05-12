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

    GETTERSETTER(int,zOder,Z)

public:

    std::vector<std::function<void( TileLayer* sender)>> vistors ;

    void executeVisitor(){
        
    };

    TileLayer();

    TileLayer(tinyxml2::XMLElement* elementLayer,int z);

    TileLayer( const TileLayer &obj);

    TileLayer& operator = (const TileLayer &t);

    int getTileId(int row, int col) ;


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
