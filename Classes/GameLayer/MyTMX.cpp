//
//  TMX.cpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 4/17/19.
//

#include "MyTMX.h"


using namespace cocos2d;

cocos2d::Scene* MyTMX::scene(std::string tmx, Vec2 g){

    auto scene = Scene::createWithPhysics();

    auto myTmxLayer =  MyTMX::create(tmx);

    myTmxLayer -> phyWorld = scene->getPhysicsWorld();

    myTmxLayer -> m_gravity = g;

    myTmxLayer->phyWorld ->setGravity(myTmxLayer -> m_gravity);

    myTmxLayer->phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    scene->addChild(myTmxLayer);

    //LabelManager::getInstance()->setTarget(layer);

    return scene;
}

MyTMX* MyTMX::create(std::string tmx)
{
    MyTMX *pRet = new(std::nothrow) MyTMX();

    if (pRet && pRet->init(tmx))
    {
        pRet -> tmxFileName = tmx;

        pRet->autorelease();

    }
    else
    {
        delete pRet;
        pRet = nullptr;

    }
    return pRet;
}

bool MyTMX::init(std::string tmx) {

    bool ret = false;

    try {

        this->tmxFileName = tmx;

        this->tiled_map = TMXTiledMap::create(this->tmxFileName);

        assert(tiled_map!=nullptr);

        this-> columns   = static_cast<int>(tiled_map->getMapSize().width);

        this-> rows      = static_cast<int>(tiled_map->getMapSize().height);

        this-> mapHeightPixels = tileSize * rows;
        this-> mapWidhtPixels = tileSize * columns;

        for (auto& child : tiled_map->getChildren())
        {
            TMXLayer* layer = dynamic_cast<TMXLayer*>(child);
            if(layer)
            {
                std::string layerName = layer->getLayerName();
                tmxLayersMap[layerName] = layer;
            }

            TMXObjectGroup* objGroup = dynamic_cast<TMXObjectGroup*>(child);
            if(objGroup)
            {
                std::string groupName = objGroup->getGroupName();
                tmxObjectsMap[groupName] = objGroup;

            }
        }

        ret = true;

    }catch (...){

        ret = false;
    }

    return ret;
}

MyTMX::MyTMX(){

}



void MyTMX::handleTMXPhysicsLayer(TMXLayer* base){

    Size s = base->getLayerSize();

    for (int x = 0; x < s.width; ++x)
    {
        for (int y = 0; y < s.height; ++y)
        {

            int id = base->getTileGIDAt(Vec2(x, y));


            auto properties = tiled_map->getPropertiesForGID(id);
            if (properties.isNull() || properties.getType() != Value::Type::MAP) {
                continue;
            }

            ValueMap vm = properties.asValueMap();

            Sprite* sprite = base->getTileAt(Vec2(x, y));

            Value vPhysics = vm["physics"];

            PhysicsBody* body = nullptr;

            if ( vPhysics.asBool()){

                Value nName = vm["name"];
                Value vBody = vm["physics_body"];
                Value vDynamic = vm["physics_type"];
                Value vCategory = vm["category"];

                if ( strcmp(vBody.asString().c_str(),"floor") == 0){
                    Rect r= sprite->getBoundingBox();
                    Size s = r.size;
                    s.height = 5;
                    body = PhysicsBody::createBox(s);
                    body->setPositionOffset(Vec2(0,-32));
                }
                if ( strcmp(vBody.asString().c_str(),"bounding_box") == 0){
                    Rect r= sprite->getBoundingBox();
                    Size s = r.size;
                    body = PhysicsBody::createBox(s);

                }

                sprite->setPhysicsBody(body);

                if ( strcmp(vDynamic.asString().c_str(),"dynamic") == 0 ){
                    body->setDynamic(true);
                }else {
                    body->setDynamic(false);
                }
            }

        }
    }

}

void MyTMX::handleTMXObjectLayer(TMXObjectGroup * objectGroup){

    // std::unordered_map<std::string, Value> ValueMap;
    ValueVector valueVectorObjects = objectGroup->getObjects();
    for( Value v : valueVectorObjects){

        ValueMap vm = v.asValueMap();

        log("----");
        for ( std::pair<std::string, Value> pair : vm){

            std::string key = pair.first;
            Value value = pair.second;
            std::string svalue = value.asString();
            log("%s:%s",key.c_str(),svalue.c_str());
        }

        Value vname = vm["name"];
        Value vX = vm["x"];
        Value vY = vm["y"];
        Value vWidth = vm["width"];
        Value vHeight = vm["height"];

        std::string name = vname.asString();
        //        int x = vX.asInt();
        //        int y = vY.asInt();
        //        int width = vWidth.asInt();
        int height = vHeight.asInt();
        int tileCordX = vX.asInt() / 64;
        int tileCordY = vY.asInt() / 64;
        int cordX = tileCordX * 64;
        int cordY = tileCordY * 64;


        // horizontal electirc fence
        if( name == "HEF"){
//            log("--->HEF");
//
//
//            int initYPixel = Director::getInstance()->getWinSize().height -  cordY;
//            int minYPixel = initYPixel - height;
//            int maxYPixel = Director::getInstance()->getWinSize().height - cordY;
//
//            int steps = 3;
//            int beamWidthInPixels = 32;
//            int beamEastXPixel =cordX;
//            int beamWestXPixel = cordX + 2 * tileWidth;
//
//            bool isBlinking = false;
//            float blinkRateInSeconds = 1;
//            bool isMoving = true;
//            float speedPixelPerSecond = 200;
//            bool increasing = true;
//
//            bool showBeamBookEnd = true;
//            bool showBeamBoundry =true;
//            bool isRandomColor = true;
//            Color4F beamColor = Color4F::WHITE;
//
//            auto hFence = GLHorzFence::create(initYPixel,  minYPixel,  maxYPixel,
//                                              steps,
//                                              beamWidthInPixels,
//                                              beamEastXPixel,  beamWestXPixel,
//                                              isBlinking, blinkRateInSeconds,
//                                              isMoving, speedPixelPerSecond,  increasing,
//                                              showBeamBookEnd,
//                                              showBeamBoundry,
//                                              isRandomColor,beamColor );
//
//            hFence->setGameLayer(this);
//            hFence->setPlayer(player);
//            hFence->start(this,0);
//            //addChild(hFence);

        }
        // vertircal electric fence
        if( name == "VEF"){
//            log("--->VEF");
//
//            int initXPixel = cordX;
//            int minXPixel  = cordX;
//            int maxXPixel  = cordX;
//            int steps = 2;
//            int beamWidthInPixels = 32;
//            int beamBottomYPixel =  mapHeightPixels - height;
//            int beamTopYPixel = mapHeightPixels - cordY;
//            bool isBlinling = true;
//            float blinkRateInSeconds = 1;
//            bool isMoving = false;
//            float speedPixelPerSecond = 1;
//            bool increasing  = false;
//            bool showBameBookEnd = true;
//            bool showBeamBoundry = true;
//            bool isRandomColor = false;
//            Color4F beamColor = Color4F::WHITE;
//
//            auto vFence = GLVertFence::create(initXPixel,  minXPixel,  maxXPixel,
//                                              steps,
//                                              beamWidthInPixels,
//                                              beamBottomYPixel,  beamTopYPixel,
//                                              isBlinling, blinkRateInSeconds,
//                                              isMoving, speedPixelPerSecond,  increasing,
//                                              showBameBookEnd,
//                                              showBeamBoundry,
//                                              isRandomColor,beamColor );
//            vFence->setGameLayer(this);
//            vFence->setPlayer(player);
//            vFence->start(this,0);

        }

        // vertical scane beam
        if( name == "VSB"){
//            log("--->VSB");
//
//            Size winSize = Director::getInstance()->getWinSize();
//            Point orgin = Vec2(cordX, cordY);
//
//            int dispersion = 100;
//            int limitLeft =  orgin.x - 100 ;
//            int limitRight = orgin.x + 100  ;
//            float velocity = 1;
//            float offOnRate = 1;
//
//            auto beam = GLBeam::create(orgin, dispersion, limitLeft, limitRight,velocity,offOnRate);
//            beam->setGameLayer(this);
//            auto ply =getPlayer();
//            beam->setPlayer(ply);
//            beam->setGameLayer(this);
//            addChild(beam);
//            beam -> setDispersion(50);
//            beam -> setVelocity(10);
//            beam->start();

        }

        // mine
        if( name == "Mine"){
//            log("--->Mine");
//
//            int x = cordX;
//            int y =   cordY;
//            Point spawnPoint(x,y);
//            Point mineLocation(x,y);
//            bool isUsingPhysics = false;
//            bool isStationary = true;
//            auto mine =  Mine::create(spawnPoint,mineLocation, isUsingPhysics,isStationary );
//            //            mine->setGameLayer(this);
//            //            mine->setPlayer(player);
//            addChild(mine);
//            mine->setSize(64,64);
//            mine->start();

        }

        // saw
        if( name == "SAW"){
            log("--->SAW");
        }


        log("%s tile(%i,%i) : cord(%i,%i)",name.c_str(),tileCordX,tileCordY, cordX,cordY);

    }

}


