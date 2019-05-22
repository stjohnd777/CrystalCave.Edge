//
//  ObjectGroup.hpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/3/19.
//
#pragma once

#include "SillyMutts.h"
#include <vector>

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

        std::vector<Object*> getObjectByName(std::string name);
        std::vector<Object*> getObjectByType(std::string value);
        std::vector<Object*> getObjectByProperty(std::string key, std::string value);

    protected:
        std::vector<Object*> m_objects;

    public:

        void render(cocos2d::Node* node );
        
        const std::string to_string();

    private:
        friend std::ostream& operator<<(std::ostream&, const ObjectGroup&);
    };
}
