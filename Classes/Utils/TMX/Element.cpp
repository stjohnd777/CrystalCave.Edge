//
//  BaseTiledElement.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "Element.h"

using namespace tinyxml2;

namespace dsj
{

    std::vector<Property> Element::ParseProperties(tinyxml2::XMLElement * element){

        cocos2d::log("Element::ParseProperties Enter" );

        assert(element);

        std::vector<Property> properties;

        XMLElement* elementProperties = element->FirstChildElement(Elements::PROPERTIES);

        if (elementProperties) {

            cocos2d::log("Element::ParseProperties Exists" );

            XMLElement* prop = elementProperties->FirstChildElement(Elements::PROPERTY);

            while (prop) {

                cocos2d::log("Element::ParseProperties Property Exists" );

                const XMLAttribute* pAttrib= prop->FirstAttribute();
                while (pAttrib) {
                    const std::string name = pAttrib->Name();
                    const std::string value = pAttrib->Value();
                    Property p(name,"",value);
                    properties.push_back(p);
                    pAttrib=pAttrib->Next();
                }
                prop = prop->NextSiblingElement(Elements::PROPERTY);
            }
        } else {
             cocos2d::log("Element::ParseProperties Not Properties Element" );
        }

        cocos2d::log("Element::ParseProperties Exit");

        return properties;
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
            if ( p.getName() == key){
                value = p.getValue();
                break;
            }
        }
        return value;
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
}
