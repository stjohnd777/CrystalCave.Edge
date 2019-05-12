//
//  TileLayer.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "TileLayer.h"
#include "TileMap.h"

using namespace tinyxml2;

namespace dsj {

    std::vector<std::string> split(const char *str,  char c = ' ')
    {
        std::vector<std::string> result;
        do {
            const char *begin = str;
            while(*str != c && *str) str++;
            result.push_back(std::string(begin, str));
        } while (0 != *str++);
        return result;
    }

    TileLayer::TileLayer(){}

    TileLayer::TileLayer( XMLElement* elementLayer, int z) :  Element(elementLayer){

        cocos2d::log(" TileLayer::TileLayer Enter ");

        zOder = z;
        
        this-> id = std::stoi ( elementLayer->Attribute("id") );
        this-> name = elementLayer->Attribute("name");
        this-> width  = std::stoi ( elementLayer->Attribute("width") );
        this-> height = std::stoi (elementLayer->Attribute("height") );

        XMLElement* dataElement = elementLayer->FirstChildElement(Elements::DATA);

        this->data = dataElement->GetText();

        cocos2d::log("%s", this->data.c_str());


        auto cells = dsj::split(this->data.c_str(),',');
        for ( int index = 0; index < cells.size() ; index++ ){
            vdata.push_back(std::stoi(cells[ index]));
        }
        cocos2d::log(" TileLayer::TileLayer Exit ");
    }

    TileLayer::TileLayer( const TileLayer &obj) : Element(obj){

        this->id = obj.id;
        this->name = obj.name;
        this->width = obj.width;
        this->height = obj.height;
        this->data = obj.data;
        this->vdata = vdata;

    }

    TileLayer& TileLayer::operator = (const TileLayer &obj)
    {
        this->id = obj.id;
        this->name = obj.name;
        this->width = obj.width;
        this->height = obj.height;
        this->data = obj.data;
        this->vdata = vdata;
        return *this;
    }


    // 10 x 5
    //
    // | 00 | 01 | 02 | 03 | ... | 09 |
    // | 10 | 11 | 12 | 13 | ... | 19 |
    // | 20 | 21 | 22 | 23 | ... | 29 |
    // | 30 |   ..               | 39 |
    // | 40 |   ..               | 49 |
    //
    int TileLayer::getTileId(int row, int col) {
        int index = row* width + col;
        return vdata.at(index);
    }

    void TileLayer::render(cocos2d::Node* target, int zz)
    {
       cocos2d::log("TileLayer::render(%i,%s) Enter",id,name.c_str());
        for( int row = 0 ; row < height ; row++) {

            for ( int col  =0 ; col < width ; col++) {

                int tileId = getTileId(row,col);

                if ( tileId == 0 ){
                    // No tile to render, empty space
                    continue;
                }

                // The TMX map produced has the tileId-1 off by one. The CSV export
                // use the tileID proper. So here I am developing against the TMX. There
                // force to use the csv, maily its simplicity. This would require tow files
                // to achive my ends since the properties, attributes and object layers are
                // the dynamic nature of the tile map. thus just hack this in for now
                Tile* tile = TileMap::getInstance()->getTileById (tileId-1);
                tile->render(target ,row, col,zOder);
            }
        }
        cocos2d::log("TileLayer::render(%i,%s) Exit",id,name.c_str());
    }


    const std::string  TileLayer::to_string() {
        std::stringstream ss;

        ss << "TileLayer : {\n";
        ss << Element::to_string() ;
        ss << "  id:" << id << "\n";
        ss << "  name:" << name << "\n";
        ss << "  height:" << height << "\n";
        ss << "  Data:" << data << "\n";

        for(int row=0; row < height; row++)
        {
            for ( int col = 0 ; col < width ; col++)
            {
                ss << "[" << row << "][" <<  col << "]=" << vdata.at(row * width +col) << " ";

            }
            ss << "\n";
        }

        ss << "}";

        return ss.str();
    }


    std::ostream& operator<<(std::ostream& strm ,  TileLayer& o)
    {
         return strm << o.to_string();
    }

    TileLayer::~TileLayer()
    {
        cocos2d::log("TileLayer::~TileLayer() Exit");
    }
}
