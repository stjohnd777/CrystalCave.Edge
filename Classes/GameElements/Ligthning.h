//
//  Ligthning.h
//  AsteroidTrouble.cocos2dx.3.2
//
//  Created by Daniel St. John on 3/29/15.
//
//
#pragma once

#include "cocos2d.h"

#include "HostileObject.h"

/**
 *
 */
class Ligthning : public HostileObject{
    
public:
    
    static Ligthning* createWithParameters(
                                 cocos2d::Point a,
                                 cocos2d::Point b,
                                 float displacement,
                                 float detail,
                                 int numberBolts,
                                 int thickness);
    
    CREATE_FUNC(Ligthning);
    
    bool  init() override;
    
    
    /// Endpoint A Orgin ligthing beam
    CC_SYNTHESIZE(cocos2d::Point, a, PointA);
    
    /// Endpoint B Endpoint ligthning beam
    CC_SYNTHESIZE(cocos2d::Point, b, PointB);
    
    /// How far to displace randomly off the line between seqments
    /// A larger value will produce a wider sweep of the lighthning beams
    // width
    CC_SYNTHESIZE(float, displacement, Displacement);
    
    /// the numer of line segements, larger valuse create a more
    // line segement betwee a and b
    CC_SYNTHESIZE(float, detail, Detail);
    
    /// number bolts, self explainitory
    CC_SYNTHESIZE(int, numberBolts, NumberBolts);
    
    /// How thick is the lines
    CC_SYNTHESIZE(int, thickness, Thickness);
    
    /// the color of the beam
    CC_SYNTHESIZE(cocos2d:: Color4F, m_MyColor, MyColor);
    
    /// apply random colors to the bolts
     CC_SYNTHESIZE(bool, m_IsRandomColor, IsRandomColor);


public:
    
    // defined virtual in GameObject
    virtual void move(cocos2d::Point p,float dt){
        this->runAction( cocos2d::MoveTo::create(dt, p) );
    }
    
    
    // defined virtual in GameObject
    virtual void takeDamage(int weight) {
        
    }// take damange
    
    // defined virtual in GameObject
    virtual void injured() {
    }
    
    virtual void die(){};

    

    
public:
    
    virtual void usePhysics() {
        auto body = cocos2d::PhysicsBody::createCircle(getContentSize().width / 2);
        body->setContactTestBitmask(true);
        body->setTag(getTag());
        body->setDynamic(true);
        setPhysicsBody(body);
    }
    
    
    virtual void useOnContact() {
        setIsUsingOnContact(true);
        auto contactListener = cocos2d::EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(Ligthning::onContactBegin, this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    }
    
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact)
    {
        return true;
    }
    
    
    void collision(float dt){}
    
public:
    
    void start(float dt );
    
    void drawOpenGL();
    
    void drawLightning(cocos2d::Point p,cocos2d::Point q,float displacement);
    
    void update(float dt) override;
    
    ~Ligthning();
    
private:
    
    Ligthning();
    
    //cocos2d::Color4F* color;
    
    cocos2d::DrawNode* drawNode;
};
