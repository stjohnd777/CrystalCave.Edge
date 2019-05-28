//
//  GameElementFactory.hpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 5/18/19.
//

#pragma once

#include <vector>


#include "cocos2d.h"
#include "Sillymutts.h"




using namespace std;
using namespace cocos2d;


class GameElementsFactory {

GETTERSETTER(Node*, m_GameLayer, GameLayer)

GETTERSETTER(GameObject*, m_Player, Player)

public:

    static const char *MINE;
    static const char *VER_ELECTRIC_FENCE;
    static const char *HOR_ELECTRIC_FENCE;
    static const char *LIGHTNING;
    static const char *SCAN_BEAM;
    static const char *HUNTER_SEEKER;

    static const char *TRANS;


    static GameElementsFactory *getInstance();


    static void HandleObjectRequest(cocos2d::Node *target, dsj::Object *obj);


    Mine *AddMine(
            Point spawnPoint,
            Point mineLocation,
            bool IsMoving,
            float dt,
            std::vector<Point> points,
            bool isUsingPhysics = false,
            bool isUsingOnContact = false);
    
    
    GLBeam* AddGLBeam(Point orgin, Point terminate,
                           int dispersion,
                           int leftLimit, int rightLmit,
                           int velcoityInPixelsPerSec,
                           int  toggelOnOFFDurationSec,
                           bool isParticleEffect){
        
        
        auto glBeam = GLBeam::create(orgin, terminate,
                                     dispersion, leftLimit, rightLmit,
                                     velcoityInPixelsPerSec,
                                     toggelOnOFFDurationSec);
        
        
        glBeam->setPlayer( getInstance()->getPlayer());
        glBeam->setGameLayer( getInstance()->getGameLayer());
        glBeam->setIsParticalEffect(true);
        
        return glBeam;
        
    }


    Lightning *AddLigthning(Point a,
            Point b,
            int numberBolts,
            int thickness,
            int displacement,
            int detail,
            Color4F myColor,
            bool isRandomColor);




private:

    static GameElementsFactory *INSTANCE;


};
