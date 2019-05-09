//
//  Tile.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "Tile.h"
#include "TileSet.h"

#include <sstream>

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

    const std::string Tile::to_string(){

        std::stringstream ss ;

        ss << "Tile : {\n";
        ss << Element::to_string() ;
        ss << "  parent: " << parent->getName();
        ss << "  id:" << id << "\n";
        ss << "  type:" << type << "\n";
        ss << "  imageSource:" << imageSource << "\n";
        ss << "  height:" << height << "\n";
        ss << "  width:" << width << "\n";
        ss << "}";

        return ss.str();
    }

    std::ostream& operator<<(std::ostream &strm,  Tile &t) {
        return strm << t.to_string();
    }

    void Tile::render(cocos2d::Node* node,int row, int col, int z){

        using namespace cocos2d;

        Sprite* sprite;
        std::stringstream ss;
        ss << "TMX-Cave/" << imageSource;
        auto image = ss.str();
        SpriteFrame * spriteFrame= SpriteFrameCache::getInstance()->getSpriteFrameByName(image);
        if ( !spriteFrame) {
            sprite = Sprite::create(image);
            SpriteFrameCache::getInstance()->addSpriteFrame(sprite->getSpriteFrame(), imageSource);
        }else {
            sprite = cocos2d::Sprite::createWithSpriteFrame(spriteFrame);
        }

        sprite->setAnchorPoint(cocos2d::Vec2(0,0));
        float x = row * this->width;
        float y = col * this->height;
        //cocos2d::Vec2 pos(x,y);
        cocos2d::Vec2 pos(y,x);
        sprite->setPosition(pos);

        node-> addChild(sprite,z);

    }


    Tile::~Tile(){}


}
