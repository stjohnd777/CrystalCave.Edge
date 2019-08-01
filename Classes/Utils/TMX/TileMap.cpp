#include "TileMap.h"

#include <sstream>
#include <array>
#include <vector>
#include <map>

using namespace std;
using namespace cocos2d;
using namespace tinyxml2;

namespace dsj {


//     bool TileMap::isBoundingBox = false;
//     bool TileMap::isDebug= false;
//     bool TileMap::isFollow = false;
//     bool TileMap::isScrollX= false;
//     bool TileMap::isScrollY= false;
    
    TileMap* TileMap::INSTANCE = nullptr;


    TileMap* TileMap::getInstance(){
        return INSTANCE;
    }
    

    /*
     <map
        version="1.2"
        tiledversion="1.2.3"
        orientation="orthogonal"
        renderorder="left-up"
         width="30"
        height="16"
        tilewidth="64"
        tileheight="64"
        infinite="0"
        nextlayerid="7"
        nextobjectid="13">

     <properties>
        <property name="LevelName" value="Hello"/>
        <property name="X" type="int"  value="0"/>
        ...
     </properties>

     <tileset f
        irstgid="1"
        name="Tiles"
        tilewidth="64"
        tileheight="64"
        tilecount="8"
        columns="0">

        <grid orientation="orthogonal" width="1" height="1"/>
        <tile id="1" type="TR-1">
            <properties> ...</properties>
            <image width="64" height="64" source="./Tile2.png"/>
        </tile>
        ...
        </tile
        ...

        <tileset

     */
    TileMap::TileMap(string pathTmx){

        INSTANCE = this;

        this->pathTmx = pathTmx;

        XMLDocument doc;
        
#if IS_MOBILE
        // TODO:: when running the iOS target the tmx file is not found. This if define
        // solves the issue
        std::string fullpath = FileUtils::getInstance()->fullPathForFilename(pathTmx);
#else
        std::string fullpath = pathTmx;
#endif
        
        int retCode = doc.LoadFile( fullpath.c_str());

        // if we have no been able to load the tile map then fail
        assert(retCode == 0);

        auto elementRoot =doc.RootElement();

        this->element = elementRoot;

        // knowing the attribute we just pull them out
        // <map version="1.2"
        //      tiledversion="2019.05.08"
        //      orientation="orthogonal"
        //      renderorder="left-up"
        //      width="26"
        //      height="16"
        //      tilewidth="64"
        //      tileheight="64"
        //      infinite="0"
        //      nextlayerid="10"
        //      nextobjectid="35">
        this->orientation = elementRoot->Attribute("orientation");
        this->width = std::stoi (elementRoot->Attribute("width"));
        this->height = std::stoi(elementRoot->Attribute("height"));
        this->tileWidth =std::stoi(elementRoot->Attribute("tilewidth"));
        this->tileWidth =std::stoi(elementRoot->Attribute("tileheight"));

        // Remark :: The size of the world is  (width * tilewidth) X ( height * tileheight )
        // I have not found a use case yet for a rectangular tile thus in general
        // world = ( width * tilesize) X ( height * tilesize)


        this->m_attributes = ParseAttributes(elementRoot);

        this->m_properties = ParseProperties(elementRoot);//element->FirstChildElement(Elements::PROPERTIES));

        try{
            XMLElement* tilesetElement = elementRoot->FirstChildElement(Elements::TILESET);
            while ( tilesetElement) {
                auto tileset = new TileSet (tilesetElement);
                m_tilesets[tileset->getName()] = tileset;
                tilesetElement = tilesetElement->NextSiblingElement(Elements::TILESET);
            }
        }catch(...){
            log("Tilesets Error");
        }

        // process the layer
        try {
            XMLElement* layerElement = elementRoot->FirstChildElement(Elements::LAYER);
            int layerCounter = 10;
            while ( layerElement) {
                int z = layerCounter + 5;
                auto layer = new TileLayer(layerElement,z);
                std::string name = layer->getName();
                m_layers[name] = layer;
                layerElement = layerElement->NextSiblingElement(Elements::LAYER);
                layerCounter++;
            }
        }catch(...){
            log("TileLayer Error");
        }

        // process the object layers
        try {
            XMLElement* groupElement = elementRoot->FirstChildElement(Elements::OBJECTGROUP);
            while(groupElement) {
                auto objectGroup = new  ObjectGroup (groupElement);
                m_objectGroups[objectGroup->getName()]=objectGroup;
                groupElement = groupElement->NextSiblingElement(Elements::OBJECTGROUP);
            }
        }catch(...){
            log("ObjectGroup Error");
        }

        log("Completed Parsing");

    }



    TileLayer* TileMap::getLayerByName(string name){
        return m_layers[name];
    }

    TileSet*  TileMap::getTilesetByName(string name){
        return m_tilesets[name];
    }

    ObjectGroup*  TileMap::getObjectGroupByName(string name){
        return m_objectGroups[name];
    }

    vector<TileLayer*> TileMap::getLayers(){
        vector<TileLayer*> v;
        for( auto p : m_layers){
            v.push_back(p.second);
        }
        return v;
    }

    vector<TileSet*> TileMap::getTilesets(){
        vector<TileSet*> v;
        for( auto p : m_tilesets){
            v.push_back(p.second);
        }
        return v;
    }

    vector<ObjectGroup*> TileMap::getObjectGroups(){
        vector<ObjectGroup*> v;
        for( auto p : m_objectGroups){
            v.push_back(p.second);
        }
        return v;
    }

    Tile* TileMap::getTileById(int tileId) {

        Tile* theTile = nullptr;
        for( auto pair : m_tilesets){
            auto aTileSet = pair.second;
            theTile = aTileSet->GetById(tileId);
            if ( theTile){
                break;
            }
        }
        return theTile;
    }

    std::vector<Tile*>  TileMap::getTilesAt(int row,int col) {

        std::vector<Tile*> tiles;

        for ( auto pair : m_layers ){
            std::string layerName = pair.first;
            TileLayer* layer = pair.second;
            int tileId = layer->getTileId(row, col);
            if ( tileId ==0){
                continue;
            }
            Tile* aTile = getTileById(tileId);
            tiles.push_back(aTile);
        }
        return tiles;
    }




    Vec2 TileMap::GetPixelCoordinates(int row,int col){
        Vec2 cord( row * tileWidth, col * tileHieght);
        return cord;
    }

    void TileMap::forEachLayer(std::function<void( TileLayer* tileLayer)> f ){
        for ( auto o : m_layers){
            f(o.second);
        }
    }
    void TileMap::forEachObjectGroup(std::function<void( ObjectGroup* objectGroup)> f ){
        for ( auto o : m_objectGroups){
            f(o.second);
        }
    }
    void TileMap::forEachTileSet(std::function<void( TileSet* tile)>  f){
        for ( auto o : m_tilesets){
            f(o.second);
        }
    }



    std::vector<Object*> TileMap::getObjectsByName(std::string name){
        std::vector<Object*> objs;
        for ( auto og : m_objectGroups){
            auto _objs = og.second->getObjectByName(name);
            objs.insert(objs.end(), _objs.begin(), _objs.end());
        }
        return objs;
    }
    std::vector<Object*> TileMap::getObjectsByType(std::string type){
        std::vector<Object*> objs;
        for ( auto og : m_objectGroups){
            auto _objs = og.second->getObjectByType(type);
            objs.insert(objs.end(), _objs.begin(), _objs.end());
        }
        return objs;
    }

    void  TileMap::render(cocos2d::Node* target){

        cocos2d::log(" TileMap::render Enter");

        for (auto p : m_layers) {
            cocos2d::log(" TileMap::render layer %s",p.first.c_str());
            auto name = p.first;
            auto layer = p.second;

            auto props = layer->getProperties();
            auto attrs = layer->getAttributes();

            layer->render(target);
        }

        for (auto p : m_objectGroups) {

            cocos2d::log(" TileMap::render object groups %s",p.first.c_str());
            auto name = p.first;
            auto objectGroup = p.second;

            auto props = objectGroup->getProperties();
            auto attrs = objectGroup->getAttributes();

            objectGroup->render(target);
        }


        cocos2d::log(" TileMap::render Exit");
    }


    std::string TileMap::to_string(){

        std::stringstream ss;
        ss << "TileMap : { " << "\n" ;
        ss << "pathTmx : " << pathTmx  << "\n";
        ss << Element::to_string() ;

        ss << "version " << ":" << version << "\n";
        ss << "tiledversion " << ":" << tiledversion << "\n";
        ss << "orientation " << ":" << orientation << "\n";
        ss << "width " << ":" << width << "\n";
        ss << "height " << ":" << height << "\n";

        ss << "tileWidth " << ":" << tileWidth << "\n";
        ss << "tileHieght " << ":" << tileHieght << "\n";
        ss << "renderorder " << ":" << renderorder << "\n";
        ss << "infinite " << ":" << infinite << "\n";
        ss << "extlayerid " << ":" << extlayerid << "\n";
        ss << "nextobjectid " << ":" << nextobjectid << "\n";

        forEachLayer(
            [&](TileLayer* layer){
                ss << layer->to_string();
            }
        );

        forEachObjectGroup([&](ObjectGroup* group){
            ss << group->to_string() ;
        });

        forEachTileSet([&](TileSet* tileSet){
            ss << tileSet->to_string() ;
        });

        ss << "}\n" ;

        return ss.str();

    }

    TileMap::~TileMap(){

        cocos2d::log("TileMap::~TileMap() Enter");
        for ( auto p : m_tilesets){
             cocos2d::log("TileMap::~TileMap() delete TileSet %s", p.second->getName().c_str());
            delete p.second;
        }
        for ( auto p : m_layers){
            cocos2d::log("TileMap::~TileMap() delete Layer %s", p.second->getName().c_str());
            delete p.second;
        }
        for ( auto p : m_objectGroups){
            cocos2d::log("TileMap::~TileMap() delete Group %s", p.second->getName().c_str());
            delete p.second;
        }
         cocos2d::log("TileMap::~TileMap() Exit");

    }


}
