#include "TargetObject.h"

//#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Utils.h"
 


using namespace cocos2d;

std::vector<TargetObject*>  * TargetObject::m_ActiveTargets = new  std::vector<TargetObject*>();



unsigned int TargetObject::DefalutChipmunkCategoryTarget = 0x02; // 00000000 00000010

int TargetObject::DefalutChipmunkGroupTarget             = 0x02;


TargetObject::TargetObject(): GameObject(){
    
    log("TargetObject::TargetObject()");
    
    m_ChipmunkCategoryMask =DefalutChipmunkCategoryTarget;
    
    m_ChipmunkGroup = DefalutChipmunkGroupTarget;

    m_ActiveTargets->push_back(this);
    
}


void TargetObject::collision(float dt){
    
    if (Utils::isInterscting(this, getPlayer()))
    {
        getPlayer()->takeDamage(getWeight());
        takeDamage(100);
    }

}

TargetObject::~TargetObject() {
    log("~TargetObject()");
    auto j = find(m_ActiveTargets->begin(),m_ActiveTargets->end(),this);
    if (j!=(TargetObject::m_ActiveTargets->end()) )
    {
        log("TargetObject::m_ActiveTargets-erase(this)");
        m_ActiveTargets->erase(j);
        
    }
}




