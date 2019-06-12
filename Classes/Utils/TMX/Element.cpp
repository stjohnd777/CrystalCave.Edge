//
//  BaseTiledElement.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "Element.h"
#include <sstream>
#include "StringUtils.h"

using namespace tinyxml2;

namespace dsj
{

    std::vector<Property> Element::ParseProperties(tinyxml2::XMLElement * element){

        cocos2d::log("Element::ParseProperties Enter" );

        assert(element);

        std::vector<Property> v_properties;

        XMLElement* elementProperties = element->FirstChildElement(Elements::PROPERTIES);

        if (elementProperties) {

            cocos2d::log("Element::ParseProperties Exists" );

            XMLElement* prop = elementProperties->FirstChildElement(Elements::PROPERTY);

            while (prop) {

                cocos2d::log("Element::ParseProperties Property Exists" );

                const XMLAttribute* attr= prop->FirstAttribute();

                std::string name;
                std::string type = "string";
                std::string value;
 
                while (attr) {

                    std::string attr_name = attr->Name();
                    if ( attr_name == "name"){
                        name = attr->Value();
                    }
                    if ( attr_name == "type"){
                        type = attr->Value();
                    }
                    if ( attr_name == "value"){
                        value =attr->Value();
                    }

                    attr=attr->Next();

                }
                Property p(name,type,value);
                v_properties.push_back(p);

                prop = prop->NextSiblingElement(Elements::PROPERTY);
            }
        } else {
             cocos2d::log("Element::ParseProperties Not Properties Element" );
        }

        cocos2d::log("Element::ParseProperties Exit");

        return v_properties;
    }

    std::vector<Attribute> Element::ParseAttributes(tinyxml2::XMLElement* element) {

        cocos2d::log("Element::ParseAttributes Enter");

        std::vector<Attribute> attrs;
        const XMLAttribute* pAttrib= element->FirstAttribute();
        while (pAttrib)
        {
            const std::string name = pAttrib->Name();
            const std::string value = pAttrib->Value();
            Attribute attr(name,value);
            attrs.push_back(attr);
            pAttrib=pAttrib->Next();
        }

        cocos2d::log("Element::ParseAttributes Exit");

        return attrs;
    }

    Element::Element(){

    }

    Element::Element(tinyxml2::XMLElement * element) : element(element){

        cocos2d::log("Element::Element Enter");

        assert(element);
        
        m_attributes = ParseAttributes(element);

        m_properties = ParseProperties(element);

        cocos2d::log("Element::Element Exit");
    }

    Element::Element( const Element &obj){

        this->element = obj.element;
        this->m_properties = obj.m_properties;
        this->m_attributes = obj.m_attributes;

    }

    void Element::operator = (const Element &obj ){

        this->element = obj.element;
        this->m_properties = obj.m_properties;
        this->m_attributes = obj.m_attributes;
    }


    Element::~Element() {

    }

    std::string Element::GetProperty (std::string key) {
        std::string value;
        for(auto p : m_properties) {
            if ( p.getName().compare(key) == 0){
                value = p.getValue();
                break;
            }else {
                cocos2d::log("%s no value",key.c_str());
            }
        }
        return value;
    }
    
    bool Element::GetPropertyBool (std::string key) {
        auto v = GetProperty(key);
        return v.empty() ? false : StringUtils::stob(v);
    }
    int Element::GetPropertyInt (std::string key) {
        auto value = GetProperty(key);
        return value.empty() ? 0 : std::stoi(value);
    }
    float Element::GetPropertyFloat (std::string key) {
        return std::stof(GetProperty(key));
    }

    std::string Element::GetAttribute (std::string key) {
        std::string value;
        for(auto p : m_attributes) {
            if ( p.getName() == key){
                value = p.getValue();
                break;
            }
        }
        return value;
    }

    bool Element::GetAttributeBool (std::string key) {
        return StringUtils::stob(GetAttribute(key));
    }
    int Element::GetAttributeInt (std::string key) {
        return std::stoi(GetAttribute(key));
    }
    float Element::GetAttributeFloat (std::string key) {
        return std::stof(GetAttribute(key));
    }

    const std::string Element::to_string() {

        std::stringstream ss;
        ss << "Element : {" << "\n";
            ss << "  attributes : {\n";
            for ( auto p : m_attributes){
                ss << "    " << "{" << "name:" << p.getName() << " ,value :" << p.getValue()  << "}" << "\n";
            }
            ss << "  }\n";

            ss << "  properties : {\n";
            for ( auto p : m_properties){
                ss << "    " << "{" << "name: " << p.getName() << " ,type: " << p.getType() << " ,value: " << p.getValue()  << "}" << "\n";
            }
            ss << "  " << "}" << "\n";
        ss<< "}\n" ;


        return ss.str();
    }
}
