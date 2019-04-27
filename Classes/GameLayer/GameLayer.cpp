#include "GameLayer.h"
#include "HudLayer.h"
#include "SuccessLayer.h"
#include "FailedLayer.h"

#include "MyMacros.h"
#include "Utils.h"

#include "LabelManager.h"
#include "SceneManager.h"

#include "GLVertFence.h"
#include "Mine.h"
#include "Ligthning.h"

//#include "PhysicsShapeCache.h"

#include "SimpleAudioEngine.h"


int GameLayer::level = 0;

GameLayer* GameLayer::INSTANCE = nullptr;

PhysicsShapeCache* shapeCache = nullptr;

int TAG_CRYSTAL = 843843;

int MIN_DISTANCE_BT_FENCE = 200;

int lengthsPerLevel [] = {2,2,2,3,3,3,4,4,4,4,4,5};
//int minMinesPerLenght = 2;
//int maxMinesPerLength = 4;
//float probablitySpwanMovingMine = .5;
int minesPerLength [] = {0,1,2,2,2,3,3,4,4,4,5};

//int minFencesPerLenght = 3;
//int maxFencesPerLength = 12;
int fencesPerLength []  = {0,1,2,2,2,3,3,4,4,4,5};

int minBoltsPerLenght = 2;
int maxBoltsPerLength = 4;

//int minObsticlesPerLenght = 2;
//int maxObsticlesPerLength = 10;


cocos2d::Scene* GameLayer::scene(int lengths ,  cocos2d::Vec2 g){

    lengths =lengthsPerLevel[GameLayer::level];

    Scene* scene = Scene::createWithPhysics();

    auto layer = GameLayer::create(lengths,g);
    scene->addChild(layer);

    layer->mWorld = scene->getPhysicsWorld();

    layer->mWorld->setGravity(  layer->m_gravity);

    if ( DEBUG) {
        scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    }

    LabelManager::getInstance()->setTarget(layer);

    INSTANCE = layer;

    return scene;
}

GameLayer* GameLayer::create(int lengths , Vec2 g)
{
    GameLayer *pRet = new(std::nothrow) GameLayer();
    if (pRet && pRet->init(lengths,g))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}


GameLayer::GameLayer(){
    
}


void GameLayer::initBackground(){
 
    strechBackgroundToScreen(GameAssets::GAME_LAYER, 0);
    //strechBackgroundToScreen("SIFI_GUI/Window/MediumDialogBox.png",1);
    //strechBackgroundToScreen("space-cave.jpg",1);
}

bool GameLayer::init(int lengths, Vec2 g){

    this->lenghts  = lengths;
    
    this->m_gravity = g;
    
    memset( buffer ,0,64 * sizeof(char));
    
    m_IsTouching = false;
    m_CtrlLayer = nullptr;
    m_HudLayer = nullptr;
    
    initBackground();
    initPlayer();
    initControlLayer();
    initHud();

    scheduleUpdate();

    Size size(Director::getInstance()->getWinSize().width * this->lenghts , Director::getInstance()->getWinSize().height );
    PhysicsMaterial material(1.0f,1.0f,1.0f);
    float border = 5;
    PhysicsBody* boundry = PhysicsBody::createEdgeBox( size,   material,  border);
    boundry->setPositionOffset(
            Vec2(
                 (Director::getInstance()->getWinSize().width * this->lenghts) /2   ,
                 Director::getInstance()->getWinSize().height/2));
    setPhysicsBody(boundry);

    // crystal floor

    CreateCrystalCeilingFloor();

    CreateMineField();

    CreateCrystalObsticals();

    //AddLighting();

    AddElectricFrences();

    AddFinishLine();


    // draw lengths for distance reference
    Size winSize = Director::getInstance()->getWinSize();
    drawNode = DrawNode::create();
    if ( drawNode) drawNode->removeFromParentAndCleanup(true);
    drawNode = DrawNode::create();
    for ( int i = 0; i < this->lenghts; i++ ){
        drawNode -> drawSegment( Vec2( i * winSize.width,0),  Vec2( i * winSize.width,winSize.height),1, Color4F::WHITE);
    }
    this->addChild(drawNode);


    schedule(schedule_selector(GameLayer::thrust), 1/15);
    
    return true;
}



void GameLayer::initControlLayer(){
    
    m_CtrlLayer =  CtrlLayer::create();
    m_CtrlLayer->setShip(ship);
    addChild(m_CtrlLayer,3000);
    
//    auto singleTouchListener = EventListenerTouchOneByOne::create();
//    singleTouchListener->setSwallowTouches(true);
//    singleTouchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
//    singleTouchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
//    singleTouchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
//    singleTouchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
//    getEventDispatcher()->addEventListenerWithSceneGraphPriority(singleTouchListener, this);

#if IS_DESKTOP
    // mouse and keyboard listener for input
    setKeypadEnabled(true);
    auto listenerKey = EventListenerKeyboard::create();
    listenerKey->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
    listenerKey->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased , this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseUp, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
    mouseListener->onMouseScroll = CC_CALLBACK_1(GameLayer::onMouseScroll, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#endif
 
}


void GameLayer::initPlayer(){
    ship = LunarModule::create();
    
    ship->setGameLayer(this);
    ship->useHealthLabel();
    ship->useInfoLabel();
    ship->setPosition(Utils::getMidPoint());
    setPlayer(ship);
    
    ship->getPhysicsBody()->setRotationEnable(false);
    // move parent player about player
    Follow* follow = Follow::create(ship);
    this->runAction(follow);
    
    addChild(ship,99);
}


void GameLayer::initHud() {
    m_HudLayer =  HudLayer::create();
    addChild(m_HudLayer,1000);
    m_HudLayer->startTracking();
}


void GameLayer::AddVerticalElectricFence(
                                 int posLine,
                                 float percentLen,
                                 float blinkRate,
                                 float percentageRun,
                                 float speedRun )
{

    int initXPixel = posLine;
    int minXPixel = posLine + 0;
    int maxXPixel = posLine +0;

    int steps = 7;
    int beamWidthInPixels = 64;
    int beamBottomYPixel = 128;
    int beamTopYPixel = Director::getInstance()->getWinSize().height - 128;

    bool isBlinkling = true;
    float blinkRateInSeconds = Utils::getRandomIntBetweenTopBottom(1, 4);

    bool isMoving = false ; //Utils::FlipCoin();
    float speedPixelPerSecond =  0; //isMoving ? Utils::getRandomIntBetweenTopBottom(100, 1024) : 0;
    bool increasing = Utils::FlipCoin();

    bool showBeamBookEnd = true;
    bool showBeamBoundry = false;
    bool isRandomColor = false;

    cocos2d::Color4F beamColor = cocos2d::Color4F::BLUE;

    GLVertFence * vFence = GLVertFence::create(  initXPixel,  minXPixel,  maxXPixel,
                                                steps,
                                                beamWidthInPixels,
                                                beamBottomYPixel,  beamTopYPixel,
                                                isBlinkling, blinkRateInSeconds,
                                                isMoving, speedPixelPerSecond,  increasing,
                                                showBeamBookEnd,
                                                showBeamBoundry,
                                                isRandomColor ,
                                                beamColor);
    vFence->setPlayer(ship);
    
    vFence->start(this,0);
}


void GameLayer::AddLigthning(Point a,
                            Point b,
                            int numberBolts,
                            int thickness,
                            int displacement,
                            int detail,
                            Color4F myColor ,
                            bool isRandomColor){
    
    Ligthning* ligthning =  Ligthning::create();
    ligthning->setGameLayer(this);
    ligthning->setPointA(a);
    ligthning->setPointB(b);
    ligthning->setNumberBolts(numberBolts);
    ligthning->setThickness(thickness);
    ligthning->setDisplacement(displacement);
    ligthning->setDetail(detail);
    ligthning->setMyColor(myColor);
    ligthning->setIsRandomColor(isRandomColor);
    ligthning->start(0);
    
    this->addChild(ligthning, 98);
}


void GameLayer::thrust(float dt)  {
    ship->thrushOff();
}




// GameLoop
// check for finish condition
// check for game over condition

void GameLayer::update(float dt)  {

    Size size = Director::getInstance()->getWinSize();
    // Level end success
    if ( finsh->getBoundingBox().intersectsRect( ship->getBoundingBox()) && canEnterFinishedProcess){

        GameLayer::level ++;
        canEnterFinishedProcess = false;

        unscheduleAllCallbacks();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::TADA, false);

        SceneManager::getInstance()->Success();
    }
    
    // Level End Failure
    if(ship->getHealth() <= 0 && canEnterDiedProcess){
        canEnterDiedProcess = false;
        unscheduleAllCallbacks();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::FAILED_SOUND, false);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::GAME_OVER);
        SceneManager::getInstance()->Failed();
    }
    // keep the ship level
    ship->setRotation(0);

    // move the hud, controls and background
    Point offestShip = Vec2(ship->getPosition().x - Director::getInstance()->getWinSize().width /2 , 0);

    // move control
    m_CtrlLayer->setPosition( offestShip);

    // move HUB
    m_HudLayer->setPosition(offestShip);

    // move BG
    if ( getChildByName("BG")) {
        getChildByName("BG")->setPosition(Utils::getMidPoint() +  offestShip);
    }

    // scrole only in X
    Point p = getPosition();
    p.y = p.y + ship->getPosition().y - Director::getInstance()->getWinSize().height/2;
    setPosition(p);
}

void GameLayer::CreateCrystalCeilingFloor()
{

    if ( !shapeCache) {
        shapeCache = PhysicsShapeCache::getInstance();
        shapeCache->addShapesWithFile("crystal_cave.plist");
    }
    int worldWidth = Director::getInstance()->getWinSize().width * this->lenghts ;
    int stalactiteWidth = Sprite::create("stalactite.png" )->getContentSize().width;
    int stalactiteSegments = 2 * worldWidth/stalactiteWidth;
    int nx = stalactiteSegments;

    bool flipedX = Utils::FlipCoin();
    char* keyPhysicsBody = nullptr;
    for ( int i = 0 ; i < nx ; i ++)
    {
        int choiceFloor = Utils::getRandomIntBetweenTopBottom(1, 4);
        bool flipedX = Utils::FlipCoin();
        log("choise floor part %i and fliped %i",choiceFloor, flipedX);
        Sprite* crystalFloorPart = nullptr;
        PhysicsBody * bodyFloorPart = nullptr;

        switch (choiceFloor) {
            case 1:
                continue;
                break;
            case 2:

                if (flipedX) {
                    keyPhysicsBody = "QuartzCrystalNorthFliped";
                    crystalFloorPart =  Sprite::create("QuartzCrystalNorthFliped.png");
                } else {
                    keyPhysicsBody =  "QuartzCrystalNorth";
                    crystalFloorPart =  Sprite::create("QuartzCrystalNorth.png");
                }

                bodyFloorPart = shapeCache->createBodyWithName(keyPhysicsBody);
                break;
            case 3:
                if (flipedX) {
                    keyPhysicsBody = "QuartzCrystalNorthFliped3";
                    crystalFloorPart= Sprite::create("QuartzCrystalNorthFliped3.png");
                } else {
                    keyPhysicsBody =  "QuartzCrystalNorth3";
                    crystalFloorPart= Sprite::create("QuartzCrystalNorth3.png");
                }
                bodyFloorPart = shapeCache->createBodyWithName(keyPhysicsBody);
                break;
            default:
                keyPhysicsBody = "geyzer";
                crystalFloorPart = Sprite::create("geyzer.png");
                bodyFloorPart = shapeCache->createBodyWithName(keyPhysicsBody);
                break;
        }

        // PE setting issue with the contact bitmask, category, test, ectra
        auto hack = PhysicsBody::createBox(crystalFloorPart->getContentSize());
        bodyFloorPart->setContactTestBitmask(hack->getContactTestBitmask());
        bodyFloorPart->setCollisionBitmask(hack->getCollisionBitmask());
        bodyFloorPart->setCategoryBitmask(hack->getCategoryBitmask());
        crystalFloorPart->setPhysicsBody(bodyFloorPart);
        bodyFloorPart->setDynamic(false);
        crystalFloorPart->setAnchorPoint(Vec2(.5,0));

        int xcoord = i * crystalFloorPart->getContentSize().width/2;
        Vec2 pos =  Vec2(xcoord,0);
        crystalFloorPart->setPosition(pos);

        // Crystal Floor Part Randomization Size
        float scaleXFloorPart = 4 * Utils::getRandomFloatBetweenTopBottom(.5, 2);
        float scaleYfloorPart = 4 * Utils::getRandomFloatBetweenTopBottom(.5, 2);
        crystalFloorPart->setScale(scaleXFloorPart, scaleYfloorPart);

        addChild(crystalFloorPart, 99, TAG_CRYSTAL);


        // Crystal Ceiling
        Sprite* crystalCiellingPart = Sprite::create("stalactite.png" /*"QuartzCrystal.128.png"*/);
        crystalCiellingPart->setPosition(Point(xcoord,Director::getInstance()->getWinSize().height));
        crystalCiellingPart->setAnchorPoint(Vec2(.5,1));
        //crystalCiellingPart->setFlippedY(true);

        Size sizeCeilingPart(crystalCiellingPart->getContentSize());
        auto bodyC = PhysicsBody::createBox(sizeCeilingPart);
        crystalCiellingPart->setPhysicsBody(bodyC);
        bodyC->setDynamic(false);

        float scaleXCeilingPart = 4* Utils::getRandomFloatBetweenTopBottom(1, 3);
        float scaleCeilingPart = 4 * Utils::getRandomFloatBetweenTopBottom(1, 3);

        crystalCiellingPart->setScale(scaleXCeilingPart, scaleCeilingPart);
        if ( Utils::getRandomFloatBetweenTopBottom(0, 1) < .5){
            crystalCiellingPart->setFlippedX(true);
        }

        addChild(crystalCiellingPart, 99, TAG_CRYSTAL);
    }

}


void GameLayer::CreateMineField(){

    for( int currentLenght = 1 ; currentLenght < this->lenghts ; currentLenght++){

        int numberMineOnThisLenght = minesPerLength[GameLayer::lenghts];
        //Utils::getRandomIntBetweenTopBottom(minMinesPerLenght, maxMinesPerLength);

        for ( int i = 0; i < numberMineOnThisLenght ; i++){

            Point r = Utils::getRandomPointOnScene();
            int lenghtOffset = currentLenght * Director::getInstance()->getWinSize().width;
            r.x += lenghtOffset;

            Mine* mine = Mine::create(r ,r ,false,false,true);

            mine->setGameLayer(this);
            mine->setPlayer(ship);

            auto body =PhysicsBody::createCircle(mine->getContentSize().width / 2);
            body->setTag(Mine::TAG);
            body->setDynamic(false);

            mine->setPhysicsBody(body);
            mine->start();
            addChild(mine, 99);


            //float randomMove = Utils::getRandomFloatBetweenTopBottom(0, 1);
            bool IsMoving =  true; //randomMove < probablitySpwanMovingMine;
            if ( IsMoving){

                Size size = Director::getInstance()->getWinSize();
                Point down = Point(r.x, 128 * 2) ;
                MoveTo * moveToDown = MoveTo::create(1,down);

                Point up = Point( r.x, size.height -128);
                MoveTo * moveToUp = MoveTo::create(1,up);

                MoveTo * orginal = MoveTo::create(1,r);
                Sequence * seq = Sequence::create(moveToDown,moveToUp,orginal,nullptr);
                RepeatForever* repeatForEver = RepeatForever::create(seq);
                mine->runAction(repeatForEver);
            }
        }
    }
}



void GameLayer::CreateCrystalObsticals(){

    for( int currentLenght = 1 ; currentLenght < this->lenghts ; currentLenght++){

        int numberMineOnThisLenght = 7 ;//Utils::getRandomIntBetweenTopBottom(minObsticlesPerLenght, maxObsticlesPerLength);

        for ( int i = 0; i < numberMineOnThisLenght ; i++){

            Point r = Utils::getRandomPointOnScene();
            int lenghtOffset = currentLenght * Director::getInstance()->getWinSize().width;
            r.x += lenghtOffset;

            // AddBarrier();

            Sprite* crystalBarrier = Sprite::create("QuartzCrystalNorthFliped3.png");//QuartzCrystal.2.128.png");
            crystalBarrier->setAnchorPoint(Vec2(.4,0));
            auto bodyCrystal = PhysicsBody::createBox(crystalBarrier->getContentSize());
            crystalBarrier->setPosition(r);
            crystalBarrier->setPhysicsBody(bodyCrystal);
            bodyCrystal->setDynamic(false);
            float scaleCrystalBarrier = Utils::getRandomFloatBetweenTopBottom(3, 7);
            crystalBarrier->setScaleY(scaleCrystalBarrier);
            addChild(crystalBarrier);
        }
    }
}

void GameLayer::AddFinishLine(){
    finsh = Sprite::create("vfinish.png");
    finsh->setPosition(this->lenghts * Director::getInstance()->getWinSize().width -128, Director::getInstance()->getWinSize().height/2);
    finsh->setScale(4, 4);
    addChild(finsh);
}



void GameLayer::AddLighting()
{

    int numberBolts = 4;
    int thickness = 4;
    int displacement = 200;
    int detail = 2;
    Color4F lightingColor(.5,  .5, .5, .8);
    bool isRandom = false;

    Size size = Director::getInstance()->getWinSize();

    for( int currentLenght = 1 ; currentLenght < this->lenghts ; currentLenght++){

        int numberBoltsOnThisLenght = Utils::getRandomIntBetweenTopBottom(minBoltsPerLenght, maxBoltsPerLength);

        for ( int i = 0; i < numberBoltsOnThisLenght ; i++){

            Point r = Utils::getRandomPointOnScene();

            r.x += size.width *currentLenght;
            AddLigthning(
                         Point(r.x,size.height),
                         Point(r.x, 0),
                         numberBolts,// numberBolts
                         thickness,// thickness
                         displacement,// displacement
                         detail , // detail
                         lightingColor,
                         false);
        }
    }
}


int lastXElectricFence;
void GameLayer::AddElectricFrences(){

    for( int currentLenght = 1 ; currentLenght < this->lenghts ; currentLenght++){

        int numberMineOnThisLenght = fencesPerLength[GameLayer::lenghts];
        //Utils::getRandomIntBetweenTopBottom(minFencesPerLenght, maxFencesPerLength);

        for ( int i = 0; i < numberMineOnThisLenght ; i++){

            Point r;
            do {
              r = Utils::getRandomPointOnScene();
            } while ( abs (lastXElectricFence - r.x) < MIN_DISTANCE_BT_FENCE );
            lastXElectricFence = r.x;

            r.x +=  currentLenght * Director::getInstance()->getWinSize().width;

            Point p = Point(r.x, 0);

            AddVerticalElectricFence(p.x,1,2,0,0);
        }
    }
}

void GameLayer::AddMine(){ }


//bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
//{
//    m_IsTouching = !m_IsTouching;
//    m_LocationOfTouch = touch->getLocationInView();
//    m_LocationOfTouch = Director::getInstance()->convertToGL(m_LocationOfTouch);
//    return false;
//}
//
//void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){}
//
//void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
//    m_IsTouching = false;
//}
//void  GameLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event){
//    onTouchEnded(touch, event);
//}


#if IS_DESKTOP

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
    gkeyCode = keyCode;
    m_IsTouching = !m_IsTouching;
    isKeyDown = true;

    float percentThrust =  m_CtrlLayer->getThrustPercentage();

    log("thrust %f", percentThrust);

    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            ship->applyThrush(Vec2(-1,0), percentThrust);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            ship->applyThrush(Vec2(1,0),percentThrust);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            ship->applyThrush(Vec2(0,-1),  percentThrust);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            ship->applyThrush(Vec2(0,1), percentThrust);
            break;

        case EventKeyboard::KeyCode::KEY_1:
        case EventKeyboard::KeyCode::KEY_Q:
        case EventKeyboard::KeyCode::KEY_KP_MINUS:
            m_CtrlLayer->setThrust(m_CtrlLayer->getThrust() - 1 ) ;
            break;
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_2:
        case EventKeyboard::KeyCode::KEY_KP_PLUS:
            m_CtrlLayer->setThrust(m_CtrlLayer->getThrust() + 1 ) ;


        case EventKeyboard::KeyCode::KEY_ESCAPE:
            if (Director::getInstance()->isPaused()){
                Director::getInstance()->resume();
            }else {
                Director::getInstance()->pause();
            }
            break;
            
        case EventKeyboard::KeyCode::KEY_X:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bell-0104.wav", false);
            Director::getInstance()->end();
            break;
    }
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
    bool isKeyDown = false;
}


void GameLayer::onMouseDown(Event *event){
    EventMouse* e = (EventMouse*)event;
    Point p = Point(e->getCursorX(),e->getCursorY());
    m_LocationOfTouch = Point(e->getCursorX(),e->getCursorY());
    m_LocationOfTouch = Director::getInstance()->convertToGL(m_LocationOfTouch);
}

void GameLayer::onMouseUp(Event *event){
    EventMouse* e = (EventMouse*)event;

}
void GameLayer::onMouseMove(Event *event){
    EventMouse* e = (EventMouse*)event;

}

void GameLayer::onMouseScroll(Event *event) {
    EventMouse* e = (EventMouse*)event;
}
#endif







