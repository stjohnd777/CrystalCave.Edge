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

//#include "MyMacros.h"
//#include "GameAssets.h"
//#include "GLVertFence.h"
//#include "GLHorzFence.h"
//#include "Mine.h"
//#include "Ligthning.h"
//#include "Utils.h"


using namespace std;
using namespace cocos2d;




class GameElementsFactory {

    GETTERSETTER(Node*,m_GameLayer, GameLayer)
    GETTERSETTER(GameObject*,m_Player, Player)

public:

    static const char* MINE;
    static const char* VER_ELECTRIC_FENCE;
    static const char* HOR_ELECTRIC_FENCE;
    static const char* LIGHTNING;
    static const char* SCAN_BEAM;
    static const char* HUNTER_SEEKER;

    static const char* TRANS;


    static  GameElementsFactory * getInstance(){
        if ( INSTANCE == nullptr){
            INSTANCE = new GameElementsFactory();
        }
        return INSTANCE;
    }

    static void HandleObjectRequest(cocos2d::Node* target, dsj::Object* obj) {

        auto size = Director::getInstance()->getWinSize();

        std::string name = obj->getName();
        std::string type = obj->GetAttribute(dsj::ATTTIBUTE::TYPE);

         if (type.compare (TRANS) == 0 ){

             /*
              <object id="32" name="TRANS" type="TRANS" x="1610" y="586" width="46" height="174">
              <properties>
              <property name="transitionTo" value="simplest.tmx"/>
              </properties>
              </object>
              */
             int X =  obj->GetAttributeInt("x");
             int Y =  size.height - obj->GetAttributeInt("y");
             int width = obj->GetAttributeInt("width");
             int height = obj->GetAttributeInt("height");

//             auto body = PhysicsBody::createBox(Size(width,height));
//             body->setDynamic(false);
//             body->setContactTestBitmask(1);

             auto sprite = Sprite::create("box.red.hollow.64.64.png");
             sprite->setAnchorPoint(Vec2(0,1));
             //sprite->setPhysicsBody(body);
             sprite->setTag(12345);
             sprite->setPosition(Vec2(X,Y));
             sprite->setScale(width/64, height/64);
             sprite->setColor(Color3B::GREEN);

             getInstance()->getGameLayer()->addChild(sprite,0);

         }

        if (type.compare (LIGHTNING) == 0 ){

        }

       if (type.compare (VER_ELECTRIC_FENCE) == 0 ){

           /*
            <object id="10" name="VEF" type="VEF" x="1222" y="196" width="64" height="320">
            <properties>
            <property name="beamColor" type="int" value="0"/>
            <property name="blinkRateInSeconds" type="int" value="2"/>
            <property name="increasing" type="int" value="0"/>
            <property name="isBlinkling" type="int" value="1"/>
            <property name="isMoving" type="int" value="0"/>
            <property name="isRandomColor" type="int" value="1"/>
            <property name="minXPixel" type="int" value="0"/>
            <property name="showBeamBookEnd" type="int" value="0"/>
            <property name="showBeamBoundry" type="int" value="0"/>
            <property name="speedPixelPerSecond" type="int" value="0"/>
            <property name="steps" type="int" value="7"/>
            </properties>
            */


           int X =  obj->GetAttributeInt("x");
           int Y =  size.height - obj->GetAttributeInt("y");
           int width = obj->GetAttributeInt("width");
           int height = obj->GetAttributeInt("height");

           int posLine = X + width/2  ;
           int initXPixel = posLine;
           int minXPixel = posLine + width/2;
           int maxXPixel = posLine - width/2;

           int steps = obj->GetPropertyInt("steps");
           int beamWidthInPixels =width;
           int beamBottomYPixel = Y - height;
           int beamTopYPixel = Y;


           bool isBlinkling = obj->GetPropertyBool("isBlinkling");
           float blinkRateInSeconds = obj->GetPropertyInt("blinkRateInSeconds");
           //Utils::getRandomIntBetweenTopBottom(1, 4);

           bool isMoving = obj->GetPropertyBool("isMoving");
           float speedPixelPerSecond =  obj->GetPropertyInt("speedPixelPerSecond");
           //Utils::getRandomIntBetweenTopBottom(100, 1024) : 0;
           bool increasing =obj->GetPropertyBool("increasing");
           //Utils::FlipCoin();

           bool showBeamBookEnd = obj->GetPropertyBool("showBeamBookEnd");
           bool showBeamBoundry = obj->GetPropertyBool("showBeamBoundry");
           bool isRandomColor = obj->GetPropertyBool("isRandomColor");;

           cocos2d::Color4F beamColor = cocos2d::Color4F::BLUE;

           GLVertFence * vFence = GLVertFence::create( initXPixel,  minXPixel,  maxXPixel,
                                                      steps,
                                                      beamWidthInPixels,
                                                      beamBottomYPixel,  beamTopYPixel,
                                                      isBlinkling, blinkRateInSeconds,
                                                      isMoving, speedPixelPerSecond,  increasing,
                                                      showBeamBookEnd,
                                                      showBeamBoundry,
                                                      isRandomColor ,
                                                      beamColor);


           vFence->setPlayer( getInstance()->getPlayer());

           vFence->start( getInstance()->getGameLayer(),0);

       }

       if (type.compare (HOR_ELECTRIC_FENCE) == 0 ){

           /*
            <object id="10" name="HEF" type="VEF" x="1222" y="196" width="64" height="320">
            <properties>
            <property name="beamColor" type="int" value="0"/>
            <property name="blinkRateInSeconds" type="int" value="2"/>
            <property name="increasing" type="int" value="0"/>
            <property name="isBlinkling" type="int" value="1"/>
            <property name="isMoving" type="int" value="0"/>
            <property name="isRandomColor" type="int" value="1"/>
            <property name="minXPixel" type="int" value="0"/>
            <property name="showBeamBookEnd" type="int" value="0"/>
            <property name="showBeamBoundry" type="int" value="0"/>
            <property name="speedPixelPerSecond" type="int" value="0"/>
            <property name="steps" type="int" value="7"/>
            </properties>
            */

           auto size = Director::getInstance()->getWinSize();

           int X =  obj->GetAttributeInt("x");
           int Y =  size.height - obj->GetAttributeInt("y");
           int width = obj->GetAttributeInt("width");
           int height = obj->GetAttributeInt("height");

           int posLine = Y - height/2  ;
           int initYPixel = posLine;
           int minYPixel = posLine + height/2;
           int maxYPixel = posLine - height/2;

           int steps = obj->GetPropertyInt("steps");
           int beamWidthInPixels = 64;
           int beamBottomXPixel = X;
           int beamTopXPixel = X+width;

           bool isBlinkling = obj->GetPropertyBool("isBlinkling");
           float blinkRateInSeconds = obj->GetPropertyInt("blinkRateInSeconds");

           bool isMoving = obj->GetPropertyBool("isMoving");
           float speedPixelPerSecond =  obj->GetPropertyInt("speedPixelPerSecond");
           bool increasing =obj->GetPropertyBool("increasing");

           bool showBeamBookEnd = obj->GetPropertyBool("showBeamBookEnd");
           bool showBeamBoundry = obj->GetPropertyBool("showBeamBoundry");
           bool isRandomColor = obj->GetPropertyBool("isRandomColor");;

           cocos2d::Color4F beamColor = cocos2d::Color4F::BLUE;

           auto * hFence = GLHorzFence::create( initYPixel,  minYPixel,  maxYPixel,
                                                      steps,
                                                      beamWidthInPixels,
                                                      beamBottomXPixel,  beamTopXPixel,
                                                      isBlinkling, blinkRateInSeconds,
                                                      isMoving, speedPixelPerSecond,  increasing,
                                                      showBeamBookEnd,
                                                      showBeamBoundry,
                                                      isRandomColor ,
                                                      beamColor);


           hFence->setPlayer( getInstance()->getPlayer());

           hFence->start( getInstance()->getGameLayer(),0);

       }
        if (type.compare (MINE) == 0 ){

            /*
             <object id="12" name="Mine" type="Mine" x="256" y="230" width="58" height="614">
             <properties>
             <property name="IsMoving" type="bool" value="false"/>
             <property name="isUsingOnContact" type="bool" value="false"/>
             <property name="isUsingPhysics" type="bool" value="false"/>
             </properties>
             </object>
             */
            auto size = Director::getInstance()->getWinSize();

            int X =  obj->GetAttributeInt("x");
            int Y =  obj->GetAttributeInt("y");
            int width = obj->GetAttributeInt("width");
            int height = obj->GetAttributeInt("height");


            Point spawnPoint = Vec2(X+width/2,Y) ;
            Point mineLocation = spawnPoint;
            bool IsMoving = obj->GetPropertyBool("IsMoving");
            std::vector<Point> points;
            points.push_back( Vec2(X+width/2,  Y + height));
            points.push_back( Vec2(X+width/2,Y));

            bool isUsingPhysics = obj->GetPropertyBool("isUsingPhysics");
            bool isUsingOnContact = obj->GetPropertyBool("isUsingOnContact");

            auto mine = getInstance()->AddMine( spawnPoint ,
                                                mineLocation,
                                                IsMoving ,
                                                points,
                                                isUsingPhysics,
                                                isUsingOnContact);
            int Z = 0;


            getInstance()->getGameLayer()->addChild(mine,Z);
            mine->start();
        }
    }

    Mine* AddMine(
                  Point spawnPoint ,
                  Point mineLocation,
                  bool IsMoving ,
                  std::vector<Point> points,
                  bool isUsingPhysics = false,
                  bool isUsingOnContact = false){

        // Point spawnPoint, Point mineLocation, bool isUsingPhysics, bool isUsingOnContact, bool isStationary
        Mine* mine = Mine::create(spawnPoint ,mineLocation ,isUsingPhysics,isUsingOnContact,!IsMoving);

        mine->setGameLayer(m_GameLayer);
        mine->setPlayer(m_Player);

        auto body =PhysicsBody::createCircle(mine->getContentSize().width / 2);
        body->setTag(Mine::TAG);
        body->setDynamic(false);
        mine->setPhysicsBody(body);

        //if ( IsMoving){

            cocos2d::Vector<FiniteTimeAction *> moves;
            for (auto point : points){
                 MoveTo * move = MoveTo::create(1,point);
                moves.pushBack(move);
            }
            MoveTo * orginal = MoveTo::create(1,spawnPoint);
            moves.pushBack(orginal);

            Sequence * seq = Sequence::create(moves);
            RepeatForever* repeatForEver = RepeatForever::create(seq);
            mine->runAction(repeatForEver);
        //}

        return mine;

    }



    Lightning* AddLigthning(Point a,
                          Point b,
                                 int numberBolts,
                                 int thickness,
                                 int displacement,
                                 int detail,
                                 Color4F myColor ,
                                 bool isRandomColor){

        Lightning* ligthning =  Lightning::create();
        ligthning->setGameLayer(m_GameLayer);
        ligthning->setPointA(a);
        ligthning->setPointB(b);
        ligthning->setNumberBolts(numberBolts);
        ligthning->setThickness(thickness);
        ligthning->setDisplacement(displacement);
        ligthning->setDetail(detail);
        ligthning->setMyColor(myColor);
        ligthning->setIsRandomColor(isRandomColor);


        return ligthning;
    }

//    GLVertFence * AddHorizontalElectricFence(
//                                           int posLine,
//                                           float percentLen,
//                                           float blinkRate,
//                                           float percentageRun,
//                                           float speedRun ) {
//
//
//
//    }

//    GLVertFence * AddVerticalElectricFence(
//                                             int posLine,
//                                             float percentLen,
//                                             float blinkRate,
//                                             float percentageRun,
//                                             float speedRun )
//    {
//
//        int initXPixel = posLine;
//        int minXPixel = posLine + 0;
//        int maxXPixel = posLine + 0;
//
//        int steps = 7;
//        int beamWidthInPixels = 64;
//        int beamBottomYPixel = 128;
//        int beamTopYPixel = Director::getInstance()->getWinSize().height - 128;
//
//        bool isBlinkling = true;
//        float blinkRateInSeconds = Utils::getRandomIntBetweenTopBottom(1, 4);
//
//        bool isMoving = false ; //Utils::FlipCoin();
//        float speedPixelPerSecond =  0; //isMoving ? Utils::getRandomIntBetweenTopBottom(100, 1024) : 0;
//        bool increasing = Utils::FlipCoin();
//
//        bool showBeamBookEnd = true;
//        bool showBeamBoundry = false;
//        bool isRandomColor = true;
//
//        cocos2d::Color4F beamColor = cocos2d::Color4F::BLUE;
//
//        GLVertFence * vFence = GLVertFence::create( initXPixel,  minXPixel,  maxXPixel,
//                                                   steps,
//                                                   beamWidthInPixels,
//                                                   beamBottomYPixel,  beamTopYPixel,
//                                                   isBlinkling, blinkRateInSeconds,
//                                                   isMoving, speedPixelPerSecond,  increasing,
//                                                   showBeamBookEnd,
//                                                   showBeamBoundry,
//                                                   isRandomColor ,
//                                                   beamColor);
//        vFence->setPlayer(m_Player);
//        vFence->setGameLayer(m_GameLayer);
//
//       return vFence;
//    }

private:

    static GameElementsFactory * INSTANCE;

    
};
