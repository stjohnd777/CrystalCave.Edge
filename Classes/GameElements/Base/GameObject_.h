//
//  GameObject_.hpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 5/14/19.
//

#pragma once


#include <string>
#include <vector>

#include "cocos2d.h"

#include "GameObjectComponent.h"

class GameObject_ : public cocos2d::Ref {

    GETTERSETTER(std::string, m_name, Name)
    GETTERSETTER(cocos2d::Node*, m_parent, Parent)
    GETTERSETTER(cocos2d::Node*, m_node, Node)

public:

    static GameObject_* create();

    bool init();

    GameObject_();

public:

    void addCompoent(GameObjectComponent* aComponent);
    void addComponents(std::vector<GameObjectComponent*> components);

    void removeComponet(GameObjectComponent* aComponent);
    void removeComponents(std::vector<GameObjectComponent*> components);

    GameObjectComponent* getCompoentWithName(std::string compentName);
    bool removeCompoentWithName(std::string compentName);

    bool executeCompoentWithName(std::string compentName);

\
    void startComponents();
    void updateComonents(float dt);
    void stopCompoents();


    virtual ~GameObject_();

private:

    void enter();

    void start();

    void update(float dt);

    void exit();

    void destroy();

    std::vector<GameObjectComponent*> m_components;

};
