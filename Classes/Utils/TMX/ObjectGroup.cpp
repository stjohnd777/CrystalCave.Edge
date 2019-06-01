//
//  ObjectGroup.cpp
//  CrystalCave.Edge-mobile
//
//  Created by Daniel St. John on 5/3/19.
//

#include "ObjectGroup.h"

using namespace tinyxml2;

namespace dsj {

    ObjectGroup::ObjectGroup(): Element() {}

    /*
     <objectgroup id="2" name="PHY0">
     <object id="1" name="TCB" type="static" x="642.667" y="127.333" width="634.667" height="446.667"/>
     <object id="2" name="LB" type="static" x="2.66667" y="841.333" width="570.667" height="181.333"/>
     <object id="4" name="RB" type="static" x="1345.33" y="838.667" width="574.667" height="185.333"/>
     <object id="5" name="Ceeling" type="static" x="1.33333" y="-1.33333" width="1928" height="126.667"/>
     </objectgroup>
     */
    ObjectGroup::ObjectGroup(XMLElement* elementObjectGroup): Element(elementObjectGroup){

        cocos2d::log("ObjectGroup::ObjectGroup Enter");

        int counter = 0;

        auto id = elementObjectGroup->Attribute("id");
        assert(id);
        this->id = std::stoi( id );

        auto name = elementObjectGroup->Attribute("name");
        assert(name);
        this->name = name;

        auto elementObj = elementObjectGroup->FirstChildElement(Elements::OBJECT);
        while(elementObj){
            assert(counter < 100);
            counter++;
            auto o =  new Object (elementObj);
            o->setParentObjectGroup(this);
            this->m_objects.push_back(o);
            cocos2d::log("Add Object %i %s: %i" ,o->getId(), o->getName().c_str(),counter);
            elementObj = elementObj->NextSiblingElement(Elements::OBJECT);
        }

        cocos2d::log("ObjectGroup::ObjectGroup Exit");
    }

    ObjectGroup::ObjectGroup( const ObjectGroup &obj) : Element(obj){
        this->id = obj.id;
        this->name = obj.name;
        
        this->m_objects = obj.m_objects;
    }

    void ObjectGroup::forEach( std::function<void( Object* tileObject)> fnc ){
        for ( auto tileObject : m_objects) {
            fnc(tileObject);
        }
    }


    std::vector<Object*> ObjectGroup::getObjectByName(std::string name){
        std::vector<Object*> objects;
        for (auto o: m_objects){
            if ( name.compare( o->GetAttribute(ATTTIBUTE::NAME)) == 0){
                objects.push_back(o);
            }
        }
        return objects;
    }
    std::vector<Object*> ObjectGroup::getObjectByType(std::string value){
        std::vector<Object*> objects;
        for (auto o: m_objects){
            if ( value.compare( o->GetAttribute(ATTTIBUTE::TYPE)) == 0){
                objects.push_back(o);
            }
        }
        return objects;
    }

    std::vector<Object*> ObjectGroup::getObjectByProperty(std::string key, std::string value){
        std::vector<Object*> objects;
        for (auto o: m_objects){
            if ( value.compare(GetProperty(key))){
                objects.push_back(o);
            }
        }
        return objects;
    }




    ObjectGroup::~ObjectGroup(){
        cocos2d::log("ObjectGroup::~ObjectGroup() Enter");
        for ( auto o : m_objects){
            cocos2d::log("delete object %i", o->getId());
            delete o;
        }
        cocos2d::log("ObjectGroup::~ObjectGroup() Exit");
    }

    const std::string ObjectGroup::to_string(){

        std::stringstream ss ;

        ss << "ObjectGroup : {\n";
        ss << "  " << Element::to_string() ;
        ss << "  " <<   "id:" << id << "\n";
        ss << "  " << "name:" << name << "\n";
        for ( auto o : m_objects){
            ss << "  " <<  o->to_string() << "\n";
        }
        ss << "  " << "}";

        return ss.str();
    }

    void ObjectGroup::render(cocos2d::Node* target) {

        if ( StringUtils::endsWith(getName(),"PHY") ) {

            std::function<void(cocos2d::Node* target,Object*)> lambda =[&](cocos2d::Node* target,Object* o){
                
                auto name = o->GetAttribute("name");
                auto type = o->GetAttribute("type");
                if ( type.compare("static") == 0 ){
                    
                    std::string shape = o->GetProperty("PhysicsBody");
                    if ( shape.compare("BOUNDING_BOX") == 0){
                        
                        int x = o->GetAttributeInt("x");
                        int y0 = Director::getInstance()->getWinSize().height - o->GetAttributeInt("y");
                        
                        int width = o->GetAttributeInt("width");
                        int height = o->GetAttributeInt("height");
                        
//                        auto body = PhysicsBody::createBox(Size(width,height));
//                        body->setContactTestBitmask(1);
//                        body->setDynamic(false);
                        
                        auto s = Sprite::create();
                        s->setAnchorPoint(Vec2(0,1));
                        s->setContentSize(Size(width,height));
                        auto body = PhysicsBody::createBox(Size(width,height));
                        body->setContactTestBitmask(1);
                        body->setDynamic(false);
                        s->setPhysicsBody(body);
              
                       
                        s->setPosition(
                                       Vec2( x , y0 )
                                       );
           
                        target->addChild(s);
                        
                    }
                    
                    if ( shape.compare("PE") == 0)
                    {
                        
                    }
                    
                }
                cocos2d::log("TODO PHY Lanbda");
            };

            for ( auto o : m_objects){
                auto attr = o->getAttributes();
                auto props = o->getProperties();
                o->render(target, lambda);
            }

        }

        if ( StringUtils::endsWith(getName(),"ELEMENTS") ){

            std::function<void(cocos2d::Node* target,Object*)> lambda =&GameElementsFactory::HandleObjectRequest;
            for ( auto o : m_objects){
                auto attr = o->getAttributes();
                auto props = o->getProperties();
                o->render(target, lambda);
            }
        }
    }

    std::ostream& operator<<(std::ostream &strm,  ObjectGroup &t) {
        return strm << t.to_string();
    }
}
