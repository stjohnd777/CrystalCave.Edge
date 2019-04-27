#include "Utils.h"
 
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "LabelManager.h"







#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif

using namespace cocos2d;


std::string Utils::getPlatform(){
    
    std::string platform;
    if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32){
        platform = "win32";
        
    }else if ( CC_TARGET_PLATFORM == CC_PLATFORM_MAC){
        platform = "mac";
    } else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
        platform = "android";
        
    } else if ( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX){
        platform = "linux";
        
    }else if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        platform = "ios";
    } else {
        platform = "unknow";
    }
    return platform;
}

bool Utils::FlipCoin(){
    return Utils::getRandomIntBetweenTopBottom( 0, 100) > 50;
}

cocos2d::Size Utils::getWindowSize(){
    cocos2d::Size winSize = Director::getInstance()->getWinSize();
    return winSize;
}

cocos2d::Point Utils::getMidPoint(){
    cocos2d::Size winSize = Director::getInstance()->getWinSize();
    return Vec2(winSize.width/2,winSize.height/2);
}


int Utils::getRandomIntBetweenTopBottom(int bottom, int top){
    if ( bottom == top){
        return 0;
    }
    int range = top - bottom;
    int randX = rand() % range  + bottom;
    return randX;
}

float Utils::getRandomFloatBetweenTopBottom(float bottom, float top){
    float range = top - bottom;
    float randX = CCRANDOM_0_1()* range  + bottom;
    return randX;
}

int Utils::getRandomX()
{
    return getRandomIntBetweenTopBottom(0,getWindowSize().width);
}

int Utils::getRandomY()
{
    return getRandomIntBetweenTopBottom(0,getWindowSize().height);
}

cocos2d::Point Utils::getRandomPointOnScene(){
    cocos2d::Size size = Director::getInstance()->getWinSize();
    int x = getRandomIntBetweenTopBottom(0, size.width);
    int y = getRandomIntBetweenTopBottom(0, size.height);
    return Vec2(x,y);
}

cocos2d::Point Utils::getRandomPointAboveScene(){
    cocos2d::Size size = Director::getInstance()->getWinSize();
    int x = getRandomIntBetweenTopBottom(0, size.width);
    return Vec2(x,size.height+ 100);
}


cocos2d::Rect Utils::getBoundingRect(Sprite *s){
    
    cocos2d::Rect r(s->getPosition().x - (s->getContentSize().width/2),
                           s->getPosition().y - (s->getContentSize().height/2),
                           s->getContentSize().width,
                           s->getContentSize().height);
    
    return r;
    
}

bool Utils::isOutOfSceneBounds(Sprite *s){
    
    cocos2d::Size winSize = Director::getInstance()->getWinSize();
    if ( s->getPosition().x < 0 ||
        s->getPosition().x > winSize.width ||
        s->getPosition().y < 0 ||
        s->getPosition().y> winSize.height  ){
        
        return true;
    }
    return false;
}

bool Utils::isInterscting(cocos2d::Sprite *s,cocos2d::Sprite *t)
{
    cocos2d::Rect targetRectS =  Utils::getBoundingRect(s);
    cocos2d::Rect targetRectT =  Utils::getBoundingRect(t);
    return targetRectT.intersectsRect(targetRectS);
    
}

bool Utils::isInterscting( cocos2d::Rect targetRectS ,cocos2d::Sprite *t)
{
    cocos2d::Rect targetRectT =  Utils::getBoundingRect(t);
    return targetRectT.intersectsRect(targetRectS);
    
}

bool Utils::isInterscting(cocos2d::Sprite *t, cocos2d::Rect targetRectS )
{
    cocos2d::Rect targetRectT =  Utils::getBoundingRect(t);
    return targetRectT.intersectsRect(targetRectS);
}



std::vector<int> Utils::getRandumNumbers(int n, int floor, int celling)
{
    std::vector<int> results;
  
    int delta = celling -floor;
    for (int index = 0; index < n; index++) {
        int r = rand() * delta;
        results.push_back( r);
        //RandomHelper::random_int( floor,celling) );
    }

    return results;
}


