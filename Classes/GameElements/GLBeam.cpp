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
    setTag(GameAssets::TAGS::SCANBEAM);

}


GLBeam* GLBeam::create(
        Point orgin,Point termination,
        int dispersion,
        int limitLeft,
        int limitRight,
        float velocity,
        float offOnRate ){

    GLBeam *pRet = new GLBeam();
    if (pRet && pRet->init(orgin, termination,dispersion,limitLeft,limitRight,velocity,offOnRate ))
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


//bool GLBeam::init() {
//
//    if( !Node::init()){
//        return false;
//    }
//
//    p = new Vect[3];
//    setDispersion(10);
//    deltaX = 0;
//    Size winSize = Director::getInstance()->getWinSize();
//    Point orgin = Vec2(winSize.width / 2, winSize.height /2 );
//    setOrgin(orgin);
//
//    m_isParticalEffect = true;
//    m_scanlimitLeft =   winSize.width /3 ;
//    m_scanlimitRight =  2* winSize.width/3 ;
//
//    return true;
//}

bool GLBeam::init(
               Point orgin,
               Point termination,
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
    setTermination(termination);
    setDispersion(dispersion);
    setLimitLeft(limitLeft);
    setLimitRight(limitRight);
    setVelocity(velocity);
    setBlinkRate(offOnRate);
    
    
    return true;
}


void GLBeam::start(){

    if ( m_SourceBeam != nullptr ) {
        Sprite * orginSource = Sprite::create(m_SourceBeam);
        orginSource->setPosition(m_orgin.x ,m_orgin.y );
        addChild(orginSource);
    }
    
    center_end = Vec2(m_orgin.x  + deltaX, m_termination.y);
    
    if ( m_isParticalEffect){
        particalSystem =ParticleFire::create();
        particalSystem->setDuration(-1);
        particalSystem->setPosition(Vec2(center_end.x, 5));
        addChild(particalSystem);
    }
    
    
    // Handle the on/off bean toggel
    if (m_BlinkRate > 0) {
 
        DelayTime*  delayTimeAction  = DelayTime::create(m_BlinkRate);
        CallFunc*   offOn = CallFunc::create( [&]{
            m_IsOn = ! m_IsOn;
        });
        Sequence*   seq = Sequence::create(delayTimeAction,offOn,NULL);
        RepeatForever* repeate = RepeatForever::create(seq);
        this->runAction(repeate);
    }
    
    scheduleUpdate();
    //schedule( schedule_selector(GLBeam::update), 1.0f/15.0f);
}



void GLBeam::update(float dt)
{
    if( getPlayer() != nullptr && getPlayer()->getHealth() <=0){
        
    }
    
    if( !m_IsOn) {
        
        if (drawNode ){
            drawNode->clear();
        }
        return;
    }
    
    drawOpenGL();
    
    if ( m_increasing) {
        deltaX = deltaX + (m_velocity * dt );
    } else {
        deltaX = deltaX - (m_velocity *dt);
    }
    
    if ( center_end.x > m_scanlimitRight){
        m_increasing = false;
    } else if ( center_end.x < m_scanlimitLeft )
    {
        m_increasing = true;
    }
    

    collision(dt);
}

void GLBeam::drawOpenGL()
{
    
    Size winSize = Director::getInstance()->getWinSize();
    
    if ( drawNode != nullptr){
        drawNode->clear();
    }
    
    // do not draw when off
    if (!m_IsOn) {
        return;
    }
    
    if ( drawNode == nullptr){
        drawNode = DrawNode::create();
        addChild(drawNode);
    }
    
    
    
    // sweaping beam
    
    center_end  = Vec2(m_orgin.x  + deltaX,               m_termination.y);
    right_end   = Vec2(m_orgin.x + deltaX + m_dispersion, m_termination.y);
    left_end    = Vec2(m_orgin.x + deltaX - m_dispersion, m_termination.y);
    
    
    //Color4F color(1,CCRANDOM_0_1(),CCRANDOM_0_1(),CCRANDOM_0_1());
    
    drawNode->drawSegment(m_orgin, right_end,   1 , m_Color4FEdgeLines);
    drawNode->drawSegment(m_orgin, center_end,  1 , m_Color4FCenterLine);
    drawNode->drawSegment(m_orgin, left_end  ,  1 , m_Color4FEdgeLines);
    
    
    p[0] = m_orgin;
    p[1] = right_end;
    p[2] = left_end;
    drawNode->drawPolygon(p, 3, m_Color4FPolygon, 2, m_Color4FEdgeLines);
    
    if ( m_isParticalEffect){
        particalSystem->setPosition(Vec2(center_end.x, center_end.y));
    }
    
}


/*
 * This method will be called periodically, gives oportunity for
 * collection detection and shutdown conditions on the level
 */

void GLBeam::collision(float dt){
    
    // another possiblity for collision is raycasting
    // getScene()->getPhysicsWorld()->rayCast(CC_CALLBACK_3(GLBeam::rayfunc, this), origin, getPlayer(), nullptr);

    
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
                break;
            }
        }
    }
}



GLBeam::~GLBeam()
{
    //delete p;
}


