//
//  Object.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#include "Object.h"

using namespace tinyxml2;

namespace dsj {

    Object::Object(){}

    Object::Object( XMLElement* elementObjectGroup) : Element(elementObjectGroup) {

        cocos2d::log("Object::Object Enter");

        auto id = elementObjectGroup->Attribute("id") ;
        assert(id);
        this->id = std::stoi( id );
        cocos2d::log("Object::Object : id : %i",this->id);

        auto name = elementObjectGroup->Attribute("name");
        assert(name);
        this->name = name;
        cocos2d::log("Object::Object : name : %s",this->name.c_str());

        cocos2d::log("Object::Object Exit");
        }

    Object::Object(const Object& obj) :Element(obj){

        this->id = obj.id;
        this->name = obj.name;
    }

    Object::~Object() { }
}
