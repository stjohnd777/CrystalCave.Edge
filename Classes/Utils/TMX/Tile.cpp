//
//  Tile.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "Tile.h"

 using namespace tinyxml2;

namespace dsj {

    Tile::Tile(){}

    /**
     * Typical example below of the <tile> element, was have
     * two known attributes id and type, and the list of custom
     * properties that can be anything. The image source path and
     * the images pixel height and width
     *
     * <image width="120" height="125" source="LavaCave/png1x/objects/door-1.png"/>

     <tile id="4" type="TR-0">
     <properties>
     <property name="Dynamic" type="bool" value="false"/>
     <property name="HitPoint" type="int" value="0"/>
     <property name="Hostile" type="bool" value="false"/>
     <property name="PE_Key" value="NA"/>
     <property name="PhysicsBodyShape" value="BB"/>
     </properties>
     <image width="64" height="64" source=".//Tile5.png"/>
     </tile>

     */
    Tile::Tile( XMLElement* elementTile): Element(elementTile){

        cocos2d::log("Tile::Tile Enter");

        assert(elementTile);

        // known attributes
        auto id = elementTile->Attribute("id");
        assert(id);
        this->id  = std::stoi(id );

        auto type = elementTile->Attribute("type");
        if (! type) {
            type = "NOT SPECIFIED";
        }
        this->type = type;


        // <image width="64" height="64" source="./TMX-Cave/Tile2.png"/>
        XMLElement* elementImage =  elementTile->FirstChildElement("image");
        assert(elementImage);

        auto imageSource = elementImage->Attribute("source");
        assert(imageSource);
        this->imageSource = imageSource;

        auto width = elementImage->Attribute("width");
        assert(width);
        this-> width = std::stoi( width );

        auto height =  elementImage->Attribute("height");
        assert(height);
        this-> height = std::stoi( height );

        cocos2d::log("Tile::Tile Exit");

    }

    Tile::Tile ( const Tile& obj) : Element(obj){

        this->id = obj.id;
        this->type = obj.type;
        this->imageSource = obj.imageSource;
        this->height = obj.height;
        this->width = obj.width;
    }

    void Tile::render(cocos2d::Node* node,cocos2d::Vec2 pos, int z){

    }

    Tile::~Tile(){}
}
