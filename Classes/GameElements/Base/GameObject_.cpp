//
//  GameObject_.cpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 5/14/19.
//

#include "GameObject_.h"


using namespace cocos2d;


GameObject_* GameObject_::create()
{
    GameObject_ *pRet = new(std::nothrow) GameObject_();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

GameObject_::GameObject_(){
    
}

void GameObject_::start() {

    enter();

    m_parent->addChild(m_node);

    startComponents();

    Director::getInstance()->getScheduler()->schedule([&](float dt){
        updateComonents(dt);
    }, this, 0.0f, false, m_name.c_str());

}

void GameObject_::startComponents(){
    for(auto aComponent : m_components){
        if (aComponent->getHasStart()) {
            aComponent->start(0);
        }
    }
}

void GameObject_::updateComonents(float dt){
    for(auto aComponent : m_components){
        if( aComponent->getHasUpdate()){
            aComponent->update(dt);
        }
    }
}

void GameObject_::stopCompoents(){
    Director::getInstance()->getScheduler()->unschedule(m_name.c_str(),this);
}

void GameObject_::addCompoent(GameObjectComponent* aComponent){
    aComponent->setSubject(m_node);
    m_components.push_back(aComponent);
}

void GameObject_::addComponents(std::vector<GameObjectComponent*> components){
    for(auto c : components){
        m_components.push_back(c);
    }
}

void GameObject_::removeComponet(GameObjectComponent* aComponent){
    auto i = find(m_components.begin(),m_components.end(),aComponent);
    if ( i!=m_components.end()){
        m_components.erase(i);
        log("remove compoenent : component removed");
    }else {
        log("remove compoenent : component not found");
    }
}

void GameObject_::removeComponents(std::vector<GameObjectComponent*> components)
{
    for( auto c : components){
        removeComponet(c);
    }
}


GameObjectComponent* GameObject_::getCompoentWithName(std::string compentName){

    GameObjectComponent* theComponent = nullptr;
    auto i = find_if(m_components.begin(),m_components.end(), [&] (GameObjectComponent* c)->bool {
        return ( c->getName() == compentName);
    });

    if( i!= m_components.end() ){
        theComponent= *i;
    }

    return theComponent;

}


bool GameObject_::removeCompoentWithName(std::string compentName){

    auto i = find_if(m_components.begin(),m_components.end(), [&] (GameObjectComponent* c)->bool {
        return ( c->getName() == compentName);
    });

    if( i!= m_components.end() ){
        m_components.erase(i);
        return true;
    }

    return false;
}

bool GameObject_::executeCompoentWithName(std::string compentName){

    GameObjectComponent* theComponent = nullptr;
    auto i = find_if(m_components.begin(),m_components.end(), [&] (GameObjectComponent* c)->bool {
        return ( c->getName() == compentName);
    });

    if( i!= m_components.end() ){
        theComponent= *i;
        theComponent->executeOnce();
        return true;
    }
    return false;
}


bool GameObject_::init(){

    return true;
}

void GameObject_::enter() {

}


void GameObject_::update(float dt){

}

void GameObject_::exit(){

}

void GameObject_::destroy(){

}


GameObject_::~GameObject_(){
    destroy();
}
