#include "GLBeam.h"

#include "GameLayer.h"
#include <string>
#include  "Utils.h"
#include "LabelManager.h"



using namespace cocos2d;
using namespace std;


//GLBeam* GLBeam::create(){
//    GLBeam *pRet = new GLBeam();
//    if (pRet && pRet->init())
//    {
//        pRet->autorelease();
//        return pRet;
//    }
//    else
//    {
//        delete pRet;
//        pRet = NULL;
//        return NULL;
//    }
// 
//}

GLBeam::GLBeam() :  m_velocity(1),  drawNode(nullptr){
    setTag(1000);
    p = new Vect[3];

}


GLBeam* GLBeam::create(
        Point orgin,
        int dispersion,
        int limitLeft,
        int limitRight,
        float velocity,
        float offOnRate ){

    GLBeam *pRet = new GLBeam();
    if (pRet && pRet->init(orgin, dispersion,limitLeft,limitRight,velocity,offOnRate ))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
}


bool GLBeam::init() {

    if( !Node::init()){
        return false;
    }
 
    p = new Vect[3];
    setDispersion(10);
    deltaX = 0;
    Size winSize = Director::getInstance()->getWinSize();
    Point orgin = Vec2(winSize.width / 2, winSize.height /2 );
    setOrgin(orgin);
    
    m_isParticalEffect = true;
    m_scanlimitLeft =   winSize.width /3 ;
    m_scanlimitRight =  2* winSize.width/3 ;

    return true;
}

bool GLBeam::init(
               Point orgin,
               int dispersion,
               int limitLeft,
               int limitRight,
               float velocity,
               float offOnRate ){

    if( !Node::init()){
        return false;
    }

    p = new Vect[3];
    setOrgin(orgin);
    setDispersion(dispersion);
    setLimitLeft(limitLeft);
    setLimitRight(limitRight);
    setVelocity(velocity);
    setBlinkRate(offOnRate);
    
    
    return true;
}


void GLBeam::start(){

    Sprite * orginSource = Sprite::create("top.elecfence.32x32.png");
    orginSource->setScale(2, 2);
    orginSource->setPosition(m_orgin.x ,m_orgin.y );
    addChild(orginSource, 101);
    
    center_end = Vec2(m_orgin.x  + deltaX, 0);
    particalSystem =ParticleFire::create();
    particalSystem->setDuration(-1);
    particalSystem->setScale(1);
    particalSystem->setPosition(Vec2(center_end.x, 5));
    addChild(particalSystem);
    
    if (m_BlinkRate > 0) {
 
        DelayTime*  delayTimeAction  = DelayTime::create(m_BlinkRate);
        CallFunc*   offOn = CallFunc::create( [&]{
            m_IsOn = ! m_IsOn;
        });
        Sequence*   seq = Sequence::create(delayTimeAction,offOn,NULL);
        RepeatForever* repeate = RepeatForever::create(seq);
        this->runAction(repeate);
    }
    
    //scheduleUpdate();
    
    schedule( schedule_selector(GLBeam::update), 1.0f/15.0f);
}




void GLBeam::drawOpenGL()
{
 
    Size winSize = Director::getInstance()->getWinSize();
    
    if ( drawNode != nullptr){
        drawNode->removeFromParentAndCleanup(true);
        drawNode = nullptr;
    }
    
    if (!m_IsOn) {
        return;
    }
    
    drawNode = DrawNode::create();
    
    addChild(drawNode);
    
    // sweaping beam

    center_end  = Vec2(m_orgin.x  + deltaX,               0);
    right_end   = Vec2(m_orgin.x + deltaX + m_dispersion, 0);
    left_end    = Vec2(m_orgin.x + deltaX - m_dispersion, 0);


    //Color4F color(1,CCRANDOM_0_1(),CCRANDOM_0_1(),CCRANDOM_0_1());
    
    drawNode->drawSegment(m_orgin, right_end, 1, m_Color4FEdgeLines);
    drawNode->drawSegment(m_orgin, center_end,1, m_Color4FCenterLine);
    drawNode->drawSegment(m_orgin, left_end,1, m_Color4FEdgeLines);

//    void DrawNode::drawPolygon(
//            const Vec2 *verts,
//            int count,
//            const Color4F &fillColor,
//            float borderWidth,
//            const Color4F &borderColor)

    p[0] =m_orgin;
    p[1]=right_end;
    p[2] =left_end;
    drawNode->drawPolygon(p, 3, m_Color4FPolygon, 2, m_Color4FEdgeLines);
    
 
    particalSystem->setPosition(Vec2(center_end.x, 5));
 
    
} 


/*
 * This method will be called periodically, gives oportunity for
 * collection detection and shutdown conditions on the level
 */

void GLBeam::collision(float dt){
    
    
    if ( getPlayer())
    {
        Rect rect = getPlayer()->getBoundingBox();
        for( float t = 0; t <= 1 ; t=t+.01){
            
            Point linelead   = (1-t) * m_orgin    +  t * right_end;
            Point lineend    = (1-t) * m_orgin    +  t * left_end;
            Point linecenter = (1-t) * m_orgin    +  t * center_end;
            
            if ( rect.containsPoint(lineend)  ||
                rect.containsPoint(linelead) ||
                rect.containsPoint(linecenter) ) {
                
                getPlayer()->takeDamage(WEIGHT_GLBEAM);
            }
        }
    }
}

void GLBeam::update(float dt)
{
    if( getPlayer() != nullptr && getPlayer()->getHealth() <=0){
        
    }
    if( !m_IsOn) {
        if (drawNode ){
            drawNode->removeFromParentAndCleanup(true);
            drawNode = nullptr;
        }
        return;
    }
    
    drawOpenGL();
    
    if ( m_increasing) {
        deltaX = deltaX + m_velocity ; // TODO
    } else {
        deltaX = deltaX - m_velocity ;
    }
    
    if ( center_end.x > m_scanlimitRight){
        m_increasing = false;
    } else if ( center_end.x < m_scanlimitLeft )
    {
        m_increasing = true;
    }

    collision(dt);
}




GLBeam::~GLBeam()
{
    delete p;
}


