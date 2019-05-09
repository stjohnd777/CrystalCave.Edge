//
//  BaseTiledElement.hpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#pragma once

#include "MyMacros.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "external/tinyxml2/tinyxml2.h"
#include "cocos2d.h"


namespace dsj
{
    namespace PROPERTY_TYPE {
        const char* const INT = "int";
        const char* const BOOL = "bool";
        const char* const FLOAT = "float";
        const char* const STRING = "sting";
        const char* const FILE = "file";
    }

    namespace Elements {
        const char* const PROPERTIES = "properties";
        const char* const PROPERTY = "property";
        const char* const TILESET = "tileset";
        const char* const TILE = "tile";
        const char* const IMAGE = "image";
        const char* const LAYER = "layer";
        const char* const DATA = "data";
        const char* const OBJECTGROUP = "objectgroup";
        const char* const OBJECT = "object";
    }

    class Cell {
        GETTERSETTER(int, row, Row);
        GETTERSETTER(int, col, Col);
    public:
        Cell(){}

        Cell(int row,int col) : row(row), col(col){}

        bool operator < (const Cell& cell) const
        {
            return (row < cell.row);
        }

        std::string to_string(){
            std::stringstream ss;
            ss << "Cell(" << row<<","<<col<<")" ;
            return ss.str();
        }
    };

    class Attribute {
        GETTERSETTER(std::string, name, Name);
        GETTERSETTER(std::string, value, Value);
    public:
        Attribute(){}
        Attribute(std::string name,std::string value) : name(name),value(value) {}

        std::string to_string(){
            std::stringstream ss;
            ss << "Attribute" << name << "=" << value;
            return ss.str();
        }
    };

    class Property {
        GETTERSETTER(std::string, name, Name);
        GETTERSETTER(std::string, type, Type);
        GETTERSETTER(std::string, value, Value);
    public:
        Property(){}

        Property(std::string name,std::string type,std::string value ):
        name(name),type(type),value(value){}

        int getIntValue(){
            return std::stoi( getValue());
        }
        int getFloatValue(){
            return std::stoi( getValue());
        }

        std::string to_string(){
            std::stringstream ss;
            ss << "Property" << name << " = " << value << " type = " << type;
            return ss.str();
        }
    };


    class Element {

        GETTERSETTER(std::vector< Property >,  m_properties, Properties)
        GETTERSETTER(std::vector< Attribute >, m_attributes,Attributes)

    public:

        static std::vector<Property> ParseProperties(tinyxml2::XMLElement * elementProperties);

        static std::vector<Attribute> ParseAttributes(tinyxml2::XMLElement* element) ;
        
    public:

        Element();

        Element(tinyxml2::XMLElement * element);

        Element( const Element &obj);

        void operator = (const Element &obj );

        virtual ~Element();

        std::string GetProperty (std::string key);

        std::string GetAttribute (std::string key) ;

        const std::string to_string();

    protected:

        tinyxml2::XMLElement* element ;


    };
}
