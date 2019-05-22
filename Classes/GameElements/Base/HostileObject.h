#pragma once

#include "cocos2d.h"

#include "GameObject.h"
#include <vector>
#include <map>
//#include "Utils.h"

class HostileObject : public GameObject {
    
public:
    
    static std::vector<HostileObject*> * m_ActiveTargets;
    
    static unsigned int DefalutChipmunkCategoryTarget ;
    
    static int DefalutChipmunkGroupTarget  ;

public:

    HostileObject();

public:
    
    /**
     * Take Damage
     */
    virtual void takeDamage(int weight) = 0;
    
    virtual void attack(float dt) {};
    
    void collision(float dt) ;
    
    virtual ~HostileObject();
    

};


