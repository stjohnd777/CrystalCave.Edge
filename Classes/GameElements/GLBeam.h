
#pragma once

#include <iostream>
#include "cocos2d.h"

#include "MyMacros.h"
#include "GameObject.h"


using namespace cocos2d;
class GLBeam : public Node { 
    

public:

    CREATE_FUNC(GLBeam)
    
    static GLBeam* create(
            Point orgin,
            int dispersion,
            int limitLeft,
            int limitRight,
            float velocity =1,
            float offOnRate = -1);
    
    GLBeam();
    
    bool init() override;
    
    
    bool init(Point orgin,
              int dispersion,
              int limitLeft,
              int limitRight,
              float velocity,
              float offOnRate );
    
public:
    
    /**
     * The Game Layer
     */
    ATTR(cocos2d::Node*, m_GameLayer, GameLayer,nullptr);
    /**
     * Player Game Object, Ship in Asteroids
     */
    ATTR(GameObject*, m_player, Player,nullptr);
    
public:

    void collision(float dt);

public:
    
    
    /**
     * Is the beam sweeping left and rigth
     */
    CC_SYNTHESIZE(bool, m_isMoving, IsMoving);
    
    /**
     * Is the beam on
     */
    CC_SYNTHESIZE(float, m_BlinkRate, BlinkRate);
    
    /**
     * Point where the Beam orginates from
     */
    CC_SYNTHESIZE(Point, m_orgin, Orgin);
    
    /**
     * Beam spot light width
     */
    CC_SYNTHESIZE(float, m_dispersion, Dispersion);
    
    /**
     * How fast the beam moves
     */
    CC_SYNTHESIZE(float, m_velocity, Velocity);
    
    /*
     * Scane limit lefy
     */
    CC_SYNTHESIZE(int, m_scanlimitLeft, LimitLeft);
    
    /**
     * Scan limit right
     */
    CC_SYNTHESIZE(int, m_scanlimitRight, LimitRight);



    CC_SYNTHESIZE(bool, m_isParticalEffect, IsParticalEffect);


    ATTR(Color4F , m_Color4FPolygon, Color4BPolygon, Color4F(1, 0, 0, .3));
    
    ATTR(Color4F , m_Color4FCenterLine, Color4BCenterLine,Color4F::WHITE);
    
    ATTR(Color4F , m_Color4FEdgeLines, Color4BEdgeLines, Color4F(1, 0, 0, .3));
    
public:
    
    /**
     * Put beam in play, starts actions, and schedules the update
     * selectors
     */
    void start ();
    
    
public:
    
    /**
     * Graw the primitve open GL
     */
    void drawOpenGL();
    
    /**
     * update selector, caclulate new bean lines then draw
     */
    void update(float dt) override;
    
    
    ~GLBeam();
    
private:
    
    ParticleSystemQuad* particalSystem ;
    /**
     * Is Beam On
     */
    bool m_IsOn = true;
    
    /**
     * Which direction is bean moving, positive x or neg
     */
    bool m_increasing = true;
    
    /**
     * Damage taken on contact
     */
    int WEIGHT_GLBEAM = 10;
    
    /**
     * Which direction is bean moving, positive x or neg
     */
    Vec2* p ;
    
    float deltaX;
    
    /**
     * Beam Center
     */
    Point center_end ;
    /**
     * far  x side
     */
    Point right_end ;
    /**
     * least  x side
     */
    Point left_end ;
    
    /**
     * Open GL node
     */
    cocos2d::DrawNode* drawNode;
 
};
