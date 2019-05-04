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

/*
 <layer id="1" name="L0" width="30" height="16">
 <properties>
 <property name="Description">Example Tile Map</property>
 <property name="UsePhysicGroup" value="PHY0"/>
 </properties>
 <data encoding="csv">
 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
 ...
 25,25,25,25,25,25,25,25,25,25,5,5,5,5,5,5,5,5,5,5,25,25,25,25,25,25,25,25,25,25,
 ...
 5,5,5,5,5,5,5,5,5,16,16,16,16,16,16,16,16,16,16,16,16,5,5,5,5,5,5,5,5,5
 </data>
 </layer>
 */
class TileLayer : public Element {

    
    GETTERSETTER(int,id,Id)
    GETTERSETTER(std::string,name,Name)
    GETTERSETTER(int,width,Width)
    GETTERSETTER(int,height,Height)
    GETTERSETTER(std::string,data,Data)

public:

    TileLayer();

    TileLayer(tinyxml2::XMLElement* elementLayer);

    TileLayer( const TileLayer &obj);

    void forEach(std::function<void( Tile tile)> );

    void render(cocos2d::Node* target);

    ~TileLayer();
protected:

    std::map<Cell,int> mapTiles;

};

}
