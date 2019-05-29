//
//  Tile.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

//
#include "GameAssets.h"
#include "Tile.h"
#include "TileSet.h"
#include "PhysicsShapeCache.h"
#include "Spike.h"

#include <sstream>

using namespace tinyxml2;

namespace dsj {


    bool stob(std::string s, bool throw_on_error = true)
    {
        auto result = false;    // failure to assert is false

        std::istringstream is(s);
        // first try simple integer conversion
        is >> result;

        if (is.fail())
        {
            // simple integer failed; try boolean
            is.clear();
            is >> std::boolalpha >> result;
        }

        if (is.fail() && throw_on_error)
        {
            throw std::invalid_argument(s.append(" is not convertable to bool"));
        }

        return result;
    }


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

        // use the TileMap properties to add this append field
        ss << "TMX-Cave/" << imageSource;

        // first pass we do not optimize this the SpriteFrame and
        // FrameCach, but will add this optimization and sprite sheet
        // next pass
        auto image = ss.str();

//        std::string type = GetAttribute("type");
//        if ( type.compare("SpikeWest" ) == 0
//            ||type.compare("SpikeEast") == 0
//            ||type.compare("SpikeNorth" ) == 0
//            || type.compare("SpikeSouth") == 0)
//        {
//            sprite = Spike::create(image);
//        } else {
//            sprite = Sprite::create(image);
//        }

        sprite = Sprite::create(image);
        
        // set anchore to be lower left corner
        sprite->setAnchorPoint(cocos2d::Vec2(0,0));

        // TAG
        int TAG = std::stoi(GetProperty("TAG"));
        sprite->setTag(TAG);

        // Add Tile* for future reference
        sprite->setUserData(this);

        auto size = cocos2d::Director::getInstance()->getWinSize();
        int x = 64* col;
        int y = size.height -  64 * row - 64;
        cocos2d::Vec2 pos(x,y);

        auto sprtieSize = sprite->getContentSize();

        // TODO :: compute the scale using the intedned tile size
        // then compute the scale factor.

        //sprite->setScale(GameAssets::MY_CONTENT_SCALE);

        // Handle the physics and body shapes
        auto isUsePhysics  = GetProperty(CUSTOM_PROPERTIES::IS_USE_PHYSICS );

        if (stob(isUsePhysics)){

            cocos2d::PhysicsBody*  body ;

            std::string shape = GetProperty(CUSTOM_PROPERTIES::PHY_BODY );

            if ( shape.compare("BOUNDING_BOX") == 0){
                auto spriteSize = sprite->getContentSize();
                body = PhysicsBody::createBox(spriteSize);
                body->setContactTestBitmask(1);
                sprite->setPhysicsBody(body);

            }else if (shape.compare("PE")== 0){

                std::string keyPhysicsBody  = GetProperty(CUSTOM_PROPERTIES::PE_KEY);
                body =  PhysicsShapeCache::getInstance()->createBodyWithName(keyPhysicsBody);

                auto spriteSize = sprite->getContentSize();
                auto hack = PhysicsBody::createBox(sprtieSize);
                body->setContactTestBitmask(hack->getContactTestBitmask());
                body->setCollisionBitmask(hack->getCollisionBitmask());
                body->setCategoryBitmask(hack->getCategoryBitmask());
                body->setContactTestBitmask(1);

                sprite->setPhysicsBody(body);


            } else {

            }

            auto isDynamic  = GetProperty(CUSTOM_PROPERTIES::IS_DYNAMIC);
            if ( stob(isDynamic)){

                body->setDynamic(true);

            }else {
                body->setDynamic(false);
            }

        }


        sprite->setPosition(pos);



        cocos2d::log("render tile %s  (%i,%i)", image.c_str(),row,col);

        node-> addChild(sprite,z);

    }


    Tile::~Tile(){}


}
