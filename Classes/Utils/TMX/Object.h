//
//  Object.hpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/2/19.
//

#pragma once

#include "external/tinyxml2/tinyxml2.h"
#include "Element.h"

namespace dsj {

    class ObjectGroup;

    class Object : public  Element {

        GETTERSETTER(ObjectGroup*,parent,ParentObjectGroup)
        GETTERSETTER(int,id,Id)
        GETTERSETTER(std::string,name,Name)
        
    public:

        std::vector<std::function<void( Object* sender)>> vistors ;

        void executeVisitor(){
            
        };

        Object();

        Object(tinyxml2::XMLElement* elementObjectGroup);

        Object(const Object& obj);

        virtual ~Object();

    public:
        const std::string to_string();

    private:
        friend std::ostream& operator<<(std::ostream& strm,   Object& o);
        
    };

}
