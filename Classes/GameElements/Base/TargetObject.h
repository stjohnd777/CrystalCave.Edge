#pragma once

#include "cocos2d.h"

#include "GameObject.h"
#include <vector>
#include <map>
//#include "Utils.h"

class TargetObject : public GameObject {
    
public:
    
    static std::vector<TargetObject*> * m_ActiveTargets;
    
    static unsigned int DefalutChipmunkCategoryTarget ;
    
    static int DefalutChipmunkGroupTarget  ;

public:

    TargetObject();

public:
    
    /**
     * Take Damage
     */
    virtual void takeDamage(int weight) = 0;
    
    virtual void attack(float dt){}
    
    void collision(float dt);
    
    virtual ~TargetObject();
    

};


