#include "AppDelegate.h"


#include "GameLayer.h"
#include "WelcomeLayer.h"

#include "MyTmx.h"

#include "SoundManager.h"

//#include "SimpleAudioEngine.h"
//using namespace CocosDenshion;


USING_NS_CC;


//static cocos2d::Size designResolutionSize = cocos2d::Size(2048, 1536);
//static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size designResolutionSize = cocos2d::Size(1650, 1050);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    // initialize director
    auto director = Director::getInstance();

    auto glview = director->getOpenGLView();

    if(!glview) {
        
#if IS_DESKTOP
        glview = GLViewImpl::createWithFullScreen("CrystalCave");
        glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,ResolutionPolicy::NO_BORDER);
#endif

#if IS_MOBILE
        glview = GLViewImpl::create("CrystalCave");
#endif

    }
    else
    { // how does one get here?
     
         glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,ResolutionPolicy::NO_BORDER);

    }

    director->setOpenGLView(glview);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    isUseContentScale = false;
    if ( isUseContentScale){
        Size frameSize = glview->getFrameSize();
        float scaleX = designResolutionSize.width / frameSize.width;
        float scaleY = designResolutionSize.height / frameSize.height;
        float f = MAX (scaleX,scaleY);
        director->setContentScaleFactor(f);
    }
    //Director::getInstance()->setContentScaleFactor(4);
    //Director::getInstance()->setContentScaleFactor(1);


    register_all_packages();

    // load sprite sheet
    
    //const char* plist = "images.plist";
    //const char* sheet = "images.png";
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist,sheet);    // create a scene. it's an autorelease object

    // load sounds
    //SoundManager::PreLoadSound();


    // PE
    PhysicsShapeCache::getInstance()->addShapesWithFile("crystal_cave.plist");

    
    //auto scene = WelcomeLayer::scene();
    auto scene = MyTMX::scene("TMX-cave/simplest_long.tmx");

    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
