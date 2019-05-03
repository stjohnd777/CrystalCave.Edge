#include "HostileObject.h"

//#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Utils.h"
 


using namespace cocos2d;

std::vector<HostileObject*>  * HostileObject::m_ActiveTargets = new  std::vector<HostileObject*>();

unsigned int HostileObject::DefalutChipmunkCategoryTarget = 0x02; // 00000000 00000010

int HostileObject::DefalutChipmunkGroupTarget             = 0x02;


HostileObject::HostileObject(): GameObject(){
    
    log("TargetObject::TargetObject()");
    
    m_ChipmunkCategoryMask =DefalutChipmunkCategoryTarget;
    
    m_ChipmunkGroup = DefalutChipmunkGroupTarget;

    m_ActiveTargets->push_back(this);
}


void HostileObject::collision(float dt){
    
    if (Utils::isInterscting(this, getPlayer()))
    {
        getPlayer()->takeDamage(getWeight());
        takeDamage(100);
    }
}

HostileObject::~HostileObject() {
    log("~TargetObject()");
    auto j = find(m_ActiveTargets->begin(),m_ActiveTargets->end(),this);
    if (j!=(HostileObject::m_ActiveTargets->end()) )
    {
        log("TargetObject::m_ActiveTargets-erase(this)");
        m_ActiveTargets->erase(j);
        
    }
}




