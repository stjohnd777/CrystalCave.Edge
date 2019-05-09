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


        auto cells = dsj::split(this->data.c_str(),',');
        for ( int index = 0; index < cells.size() ; index++ ){
            vdata.push_back(std::stoi(cells[ index]));
        }


//        _data = new int*[height];
//        for(int i = 0; i < height; ++i){
//            _data[i] = new int[width];
//        }
//
//
//        for(int row=0; row < height; row++)
//        {
//            for ( int col = 0 ; col < width ; col++)
//            {
//                int index = row * width + col;
//                int tileID = std::stoi(cells[ index]);
//                _data[row][col] = tileID;
//            }
//        }

        cocos2d::log(" TileLayer::TileLayer Exit ");
    }

    TileLayer::TileLayer( const TileLayer &obj) : Element(obj){

        this->id = obj.id;
        this->name = obj.name;
        this->width = obj.width;
        this->height = obj.height;
        this->data = obj.data;
        this->vdata = vdata;
        //this->_data = new int*[width];
//        for(int i = 0; i < width; ++i){
//            this->_data[i] = new int[height];
//        }

//        for( int r = 0 ; r < height ; r++){
//            for ( int c  =0 ; c < width ; c++){
//                this->_data[r][c] = obj._data[r][c];
//            }
//        }

    }

    TileLayer& TileLayer::operator = (const TileLayer &obj)
    {
        this->id = obj.id;
        this->name = obj.name;
        this->width = obj.width;
        this->height = obj.height;
        this->data = obj.data;
        this->vdata = vdata;

//        this->_data = new int*[width];
//
//        for(int i = 0; i < width; ++i)
//        {
//            this->_data[i] = new int[height];
//        }
//
//        for( int r = 0 ; r < height ; r++)
//        {
//            for ( int c  =0 ; c < width ; c++)
//            {
//                this->_data[r][c] = obj._data[r][c];
//            }
//        }
        return *this;
    }

    Tile* GetTileById(int tileId){

        for ( int z = 0 ; z < TileMap::getInstance()->getTilesets().size(); z++)
        {
            TileSet* tileset =TileMap::getInstance()->getTilesets().at(z);
            auto tile = tileset->GetById(tileId);
            if (tile)
            {
                return tile;
            }else {
                cocos2d::log("miss");
            }
        }
    }

    void TileLayer::render(cocos2d::Node* target, int zz)
    {
       cocos2d::log("TileLayer::render() Enter");

        for( int row = 0 ; row < height ; row++)
        {
            std::stringstream ss;
            for ( int col  =0 ; col < width ; col++)
            {

                int index = row * width + col;
                int tileId = vdata.at(index); //_data[row][col];

                if ( tileId == 0 ){
                    continue;
                }

                ss << vdata.at(row*width +col)  << " ";

                Tile* tile = GetTileById (tileId);

                auto size = cocos2d::Director::getInstance()->getWinSize();

//                int x = size.width * col;
//                int y = size.height / height * row;

                tile->render(target ,row, col,zz);

//                for ( int z = 0 ; z < TileMap::getInstance()->getTilesets().size(); z++)
//                {
//                    TileSet* tileset =TileMap::getInstance()->getTilesets().at(z);
//                    auto tile = tileset->GetById(tileId);
//                    if (tile)
//                    {
//                        auto props = tileset->getProperties();
//                        auto attrs = tileset->getAttributes();
//                        tile->render(target ,height - row, col,zz);
//                        break;
//                    }
//                }
            }
            ss << "\n";
            cocos2d::log("%s", ss.str().c_str());
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
                //ss << "(" << row << ", " <<  col << "," << _data[row][col] << ")" << " ";
                ss << "(" << row << ", " <<  col << "," << vdata.at(row * width +col) << ")" << " ";

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
//        cocos2d::log("TileLayer::~TileLayer() Enter");
//        for(int i = 0; i < width; ++i)
//        {
//            cocos2d::log("TileLayer::~TileLayer() delete data[%i]", i);
//            delete _data[i] ;
//        }
//        cocos2d::log("TileLayer::~TileLayer() delete _data");
//        delete _data;

        cocos2d::log("TileLayer::~TileLayer() Exit");
    }
}
