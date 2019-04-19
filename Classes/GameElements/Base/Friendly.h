#pragma once

#include "cocos2d.h"
#include "GameObject.h"


class Friendly : public GameObject {
public:
    
    static unsigned int DefalutChipmunkCategoryTarget;
    
    static int DefalutChipmunkGroupTarget ;
    
    Friendly(): GameObject(){};
    
    virtual ~Friendly()  {}
};
