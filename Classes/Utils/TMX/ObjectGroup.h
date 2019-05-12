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
        

        // default constructor
        ObjectGroup();

        // constructor
        ObjectGroup(tinyxml2::XMLElement* elementObjectGroup);

        // copy construtor
        ObjectGroup( const ObjectGroup &obj);

        virtual ~ObjectGroup();

        void forEach( std::function<void( Object* tileObject)> fnc );

    protected:
        std::vector<Object*> m_objects;

    public:
        
        const std::string to_string();

    private:
        friend std::ostream& operator<<(std::ostream&, const ObjectGroup&);
    };
}
