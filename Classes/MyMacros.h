#pragma once

#include "cocos2d.h"

#define DEBUG 0

#define IS_MOBILE (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

#define IS_DESKTOP (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32   || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)



/**
 * Creats get<funName>/set<funName> for instance varable of
 * type <varType> and name <varName> with initial value v
 *
 */
#define ATTR(varType, varName, funName, v)\
    protected: varType varName = v ;\
    public: virtual varType get##funName(void) const {\
        return varName;\
    }\
    public: virtual void set##funName(varType var){\
        varName = var;\
    }\

#define GETTERSETTER(varType, varName, funName)\
    protected: varType varName  ;\
    public: virtual varType get##funName(void) const {\
        return varName;\
    }\
    public: virtual void set##funName(varType var){\
        varName = var;\
    }\


#define GETTER(varType, varName, funName)\
protected: varType varName  ;\
public: virtual varType get##funName(void) const {\
return varName;\
}\

/**
 * Creats static get<funName>/set<funName> for static varable of
 * type <varType> and name <varName> with initial value v
 *
 */
#define STATIC_ATTR(varType, varName, funName, v)\
    protected: static varType varName = v ;\
    public: static varType get##funName(void) const {\
    return varName;\
}\
public: static void set##funName(varType var){\
    varName = var;\
}\



// fear this is re definition on existing macro, no np but FYI
#define CREATE_FUNCTION(__TYPE__)\
static __TYPE__* create( )\
{\
__TYPE__ *pRet = new(std::nothrow) __TYPE__();\
if ( pRet && pRet->init() ) \
{\
pRet->autorelease();\
return pRet;\
}\
else \
{\
delete pRet;\
pRet = NULL;\
return NULL;\
}\
}

// static TYPE* create(....


// CREATE_WITH_PHY
// modleled from the usual CREATE_FUNCTION for passing the physics
// inot the init methos, and the enevatable chaining required
#define CREATE_FUNCTION_PHY(__TYPE__)\
static __TYPE__* create(bool isUsingPhysics ,bool useOnContact )\
{\
    __TYPE__ *pRet = new(std::nothrow) __TYPE__();\
    if ( pRet && pRet->init(isUsingPhysics,useOnContact) ) \
    {\
        pRet->autorelease();\
        return pRet;\
    }\
    else \
    {\
        delete pRet;\
        pRet = NULL;\
        return NULL;\
    }\
}

#define CREATE_FUNCTION_DESC(__TYPE__) \
static __TYPE__* create(GameObjectDescriptor desc) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init(desc)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}










// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#define SCENE_PHY_G(__TYPE__)\
static Scene * scene(bool isUsingPhysics, bool useOnContact , cocos2d::Vec2 gravity = Vec2(0,-10))\
{\
    Scene* scene = nullptr;\
    auto layer = __TYPE__::create(isUsingPhysics,useOnContact);\
    if ( isUsingPhysics)\
    {\
        scene = Scene::createWithPhysics();\
        scene->getPhysicsWorld()->setGravity(gravity);\
        if( useOnContact)\
        {\
            auto contactListener = EventListenerPhysicsContact::create();\
            contactListener->onContactBegin = CC_CALLBACK_1(__TYPE__::onContactBegin, layer);\
            contactListener->onContactPreSolve =CC_CALLBACK_1(__TYPE__::onPreSolve, layer);\
            contactListener->onContactPostSolve =CC_CALLBACK_1(__TYPE__::onPostSolve, layer);\
            contactListener ->onContactSeparate = CC_CALLBACK_1(__TYPE__::onContactSeperate, layer);\
            layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,layer);\
        }\
    }\
    else \
    {\
        scene = Scene::create();\
    }\
    scene->addChild(layer);\
    return scene;\
}


#define SCENE_PHY_GRAVITY(__TYPE__,__GRAVITYX__,__GRAVITYY__)\
static Scene * scene(bool isUsingPhysics, bool useOnContact , cocos2d::Vec2 gravity = Vec2(__GRAVITYX__,__GRAVITYY__))\
{\
Scene* scene = nullptr;\
auto layer = __TYPE__::create(isUsingPhysics,useOnContact);\
if ( isUsingPhysics)\
{\
scene = Scene::createWithPhysics();\
scene->getPhysicsWorld()->setGravity(gravity);\
if( useOnContact)\
{\
auto contactListener = EventListenerPhysicsContact::create();\
contactListener->onContactBegin = CC_CALLBACK_1(__TYPE__::onContactBegin, layer);\
contactListener->onContactPreSolve =CC_CALLBACK_1(__TYPE__::onPreSolve, layer);\
contactListener->onContactPostSolve =CC_CALLBACK_1(__TYPE__::onPostSolve, layer);\
contactListener ->onContactSeparate = CC_CALLBACK_1(__TYPE__::onContactSeperate, layer);\
layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,layer);\
}\
}\
else \
{\
scene = Scene::create();\
}\
scene->addChild(layer);\
return scene;\
}




#define LOAD_SCENE(__TYPE__) \
static void LoadScene( \
                      std::string backgroundImage, \
                      std::string bgMusic,std::string gametitle, \
                      bool isUsingPhysics, \
                      bool  isUsingOnContact){ \
    cocos2d::Scene * pScene = __TYPE__::scene(backgroundImage,bgMusic,gametitle); \
    TransitionFlipAngular *animation = TransitionFlipAngular::create(.5,  pScene); \
    Director::getInstance()->replaceScene(animation); \
}


