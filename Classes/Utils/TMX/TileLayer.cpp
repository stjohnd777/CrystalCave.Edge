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

    TileLayer::TileLayer( XMLElement* elementLayer) :  Element(elementLayer){

        cocos2d::log(" TileLayer::TileLayer Enter ");

        this-> id = std::stoi ( elementLayer->Attribute("id") );
        this-> name = elementLayer->Attribute("name");

        this-> width  = std::stoi ( elementLayer->Attribute("width") );
        this-> height = std::stoi (elementLayer->Attribute("height") );

        XMLElement* dataElement = elementLayer->FirstChildElement(Elements::DATA);

        this->data = dataElement->GetText();

        cocos2d::log("%s", this->data.c_str());

        _data = new int*[height];
        for(int i = 0; i < height; ++i){
            _data[i] = new int[width];
        }

        auto cells = dsj::split(this->data.c_str(),',');

        for(int row=0; row < height; row++)
        {
            for ( int col = 0 ; col < width ; col++)
            {
                int tileID = std::stoi(cells[row*height+col]);
                int r = (height-1)-row;
                int c = col;
                _data[r][c] = tileID;
            }
        }

        cocos2d::log(" TileLayer::TileLayer Exit ");
    }

    TileLayer::TileLayer( const TileLayer &obj) : Element(obj){

         this->id = obj.id;
         this->name = obj.name;
         this->width = obj.width;
         this->height = obj.height;
         this->data = obj.data;
        this->_data = new int*[width];
        for(int i = 0; i < width; ++i){
            this->_data[i] = new int[height];
        }

        for( int r = 0 ; r < height ; r++){
            for ( int c  =0 ; c < width ; c++){
                this->_data[r][c] = obj._data[r][c];
            }
        }

    }

    TileLayer& TileLayer::operator = (const TileLayer &obj){
        this->_data = new int*[width];
        for(int i = 0; i < width; ++i){
            this->_data[i] = new int[height];
        }

        for( int r = 0 ; r < height ; r++){
            for ( int c  =0 ; c < width ; c++){
                this->_data[r][c] = obj._data[r][c];
            }
        }


    }

    void TileLayer::render(cocos2d::Node* target, int z){

        cocos2d::log("TileLayer::render() Enter");

        for( int r = 0 ; r < height ; r++){
            for ( int c  =0 ; c < width ; c++){

                int tileId = _data[r][c];

                TileMap::getInstance()->forEachTileSet( [&]( TileSet* tileset){

                    cocos2d::log("TileSet Name = %s ",tileset->getName().c_str());

                    auto props = tileset->getProperties();
                    auto attrs = tileset->getAttributes();

                    auto tile = tileset->GetById(tileId);

                    if (tile) {
                        int z = 0; // TODO
                        tile->render(target,r,c,z);
                    }else {
                        cocos2d::log("TileSet Name = %s ","Miss");
                    }
                });

            }
        }
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
                ss << "(" << row << ", " <<  col << "," << _data[row][col] << ")" << " ";
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
        cocos2d::log("TileLayer::~TileLayer() Enter");
        for(int i = 0; i < width; ++i)
        {
            cocos2d::log("TileLayer::~TileLayer() delete data[%i]", i);
            delete _data[i] ;
        }
        cocos2d::log("TileLayer::~TileLayer() delete _data");
        delete _data;

        cocos2d::log("TileLayer::~TileLayer() Exit");
    }
}
