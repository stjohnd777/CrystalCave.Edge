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
    
    class Object : public  Element {

        GETTERSETTER(int,id,Id)
        GETTERSETTER(std::string,name,Name)
        
    public:
        Object();

        Object(tinyxml2::XMLElement* elementObjectGroup);

        Object(const Object& obj);

        virtual ~Object();
    };

}
