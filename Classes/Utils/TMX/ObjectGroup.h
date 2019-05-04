//
//  ObjectGroup.hpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/3/19.
//
#pragma once

#include "external/tinyxml2/tinyxml2.h"
#include "Element.h"
#include "Object.h"

namespace dsj {

    class ObjectGroup : public Element {

        GETTERSETTER(int,id,Id)
        GETTERSETTER(std::string,name,Name)
        
    public:

        ObjectGroup();

        ObjectGroup(tinyxml2::XMLElement* elementObjectGroup);

        ObjectGroup( const ObjectGroup &obj);

        virtual ~ObjectGroup();

        void forEach( std::function<void( Object tileObject)> fnc );

    protected:
        std::vector<Object> m_objects;
    };
}
