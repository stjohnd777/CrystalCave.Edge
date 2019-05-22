//
//  Ligthning.cpp
//  AsteroidTrouble.cocos2dx.3.2
//
//  Created by Daniel St. John on 3/29/15.
//
//
#include "Lightning.h"

using namespace cocos2d;


static Lightning* createWithParameters(
                                       cocos2d::Point a,
                                       cocos2d::Point b,
                                       float displacement,
                                       float detail,
                                       int numberBolts,
                                       int thickness){
    
    Lightning * ligthning = Lightning::create();
    
    ligthning->setPointA(a);
    ligthning->setPointB(b);
    ligthning->setDisplacement(displacement);
    ligthning->setDetail(detail);
    ligthning->setNumberBolts(numberBolts);
    ligthning->setThickness(thickness);
    
    return ligthning;
}

Lightning::Lightning() :HostileObject(){
    init();
}

bool  Lightning::init(){

    m_GameLayer = nullptr;
    
    m_IsRandomColor = false;
    m_MyColor =   Color4F(1,1,1,.5);
    displacement = 200;
    detail = 20;
    numberBolts = 25;
    thickness = 1;
    drawNode = nullptr;
    return true;
}

void  Lightning::start( float dt ){
    scheduleUpdate();
}



void Lightning::update(float dt) {
    
    drawOpenGL();
}

void Lightning::drawLightning(Point p,Point q,float displacement)
{
    if ( displacement < detail) {
        
        // set the color of the bolt
        Color4F color = m_MyColor;
        if (getIsRandomColor()){
            color = Color4F(CCRANDOM_0_1(),CCRANDOM_0_1(),1,.8);
        }
        
        // draw line
        drawNode->drawSegment(p, q, thickness, color);
        
        //drawNode->drawPoint(p,1,Color4F::RED);
        //drawNode->drawPoint(p,1,Color4F::RED);
        
  
    }
    else {
        
        // divide
        float mid_x = (p.x+q.x)/2;
        
        float mid_y = (p.y+q.y)/2;
        
        // perturbation
        mid_x += (CCRANDOM_0_1()-.5)*displacement;
        
        // perturbation
        mid_y += (CCRANDOM_0_1()-.5)*displacement;
        
        /// mid
        Vec2 mid(mid_x,mid_y);
       
        drawLightning(mid,q,displacement/2);
        
        drawLightning(p,mid,displacement/2);
    }
}

void Lightning::drawOpenGL()
{
    // do not crash, check is we have
    // game layer
    if ( getParent() == nullptr){
        return;
    }
    
    // draw node is node for drawinf open gl
    // primitives, we draw a new node each frame
    // so remove this one
    if ( drawNode != nullptr){
        drawNode->removeFromParentAndCleanup(true);
        drawNode = nullptr;
    }
    drawNode = DrawNode::create();

    
    getGameLayer() -> addChild(drawNode);
    
    // draw bolts
    for (int i =0 ; i <numberBolts; i++) {
        drawLightning(a,b,displacement);
    }
} 


Lightning::~Lightning(){
    
    //delete color;
};
