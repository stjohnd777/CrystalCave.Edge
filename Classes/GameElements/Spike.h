//
//  Spike.hpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 5/11/19.
//

#pragma once

#include <string>

#include "GameAssets.h"
#include "GameObject.h"
#include "HostileObject.h"
#include "LunarModule.h"

class Spike : public HostileObject {

public:

    static Spike* create(std::string fileName)
    {
        Spike *pRet = new(std::nothrow) Spike();
        if (pRet && pRet->init(fileName))
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

public :

    bool init(std::string fileName ) {

        setTag(GameAssets::TAGS::SPIKE);

        setWeight(100);

        setPlayer(LunarModule::getInstance());

        initWithFile(fileName);

        return true;

    };

    void start() {

        scheduleUpdate();

    }

    void update ( float dt) {

        collision(dt);
    }

    virtual void takeDamage(int weight) {
        
    }

    virtual void attack(int weight) {

    }

};
