#include "LabelManager.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "HostileObject.h"
//#include "Utils.h"
#include "GameAssets.h"

#include <iterator>
//#include "GameObjectsManager.h"

LabelManager * LabelManager::INSTANCE = nullptr;


LabelManager* LabelManager::getInstance(){
    if ( INSTANCE == nullptr){
        INSTANCE = new LabelManager();
    }
    return INSTANCE;
}

LabelManager::LabelManager() : m_DelayTime(2), m_FadeTime(1),m_target(nullptr)
{
    
}


void LabelManager::makeHitLabel(int hit, Point pos,Color3B color){
    char szValue2[100] = {0};
    sprintf(szValue2,"%i",hit); // value
    auto font = GameAssets::Fonts::BMF::NUM::HIT_LABEL;
    makeFadingLabel(szValue2, pos, color, Vec2(0.5, 0.5),font);
}



void LabelManager::makeFadingLabel(const char *const msg, Point pos, Color3B color){
    auto font = GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL;
    makeFadingLabel(msg, pos, color, Vec2(1, 0.5), font);
}

void LabelManager::makeFadingLabel(const char *const msg, float percentWidth, float percentHeight, Color3B color,
                                   Point anchor){
    Size size = Director::getInstance()->getWinSize();
    Point pos = Vec2(size.width*percentWidth,size.height*percentHeight);
    auto font = GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL;
    makeFadingLabel(msg, pos, color, anchor, font);
}

void LabelManager::makeFadingLabel(const char *const msg, Point pos, Color3B color, Point anchor, const char *font){

    char szValue2[64] = {0};
    sprintf(szValue2,"%s",msg);

    Label* l = Label::createWithBMFont(font,szValue2);
    l->setWidth( 200);
    l->setColor(color);
    l->setAnchorPoint(anchor);
    l->setPosition(pos);
    l->setTag(GameAssets::Sprite::TEMP_LABEL);

    // add to registry
    s_ActiveLabels.push_back(l);

    assert(m_target);

    m_target->addChild(l,LayerLevel::kCtrl);

    m_DelayTime = 2;
    // remove your self
    DelayTime*  delayTimeAction = DelayTime::create(m_DelayTime);
    FadeOut* fadeOut = FadeOut::create(1);

    std::function<void()> f_remove = std::bind(&LabelBMFont::removeFromParent,l) ;
    CallFunc* removeLabel =  CallFunc::create( f_remove );

    auto f_remove0 = std::bind( &LabelManager::removeFromRegistry,this,l);
    CallFuncN* removeLabelFromRegistry =  CallFuncN::create( f_remove0 ) ;

    Sequence*   lableSequence = Sequence::create(delayTimeAction,fadeOut,removeLabelFromRegistry,removeLabel,NULL);
    l->runAction(lableSequence);

}



void LabelManager::makePerminateLabel(
                                      const char *const msg,
                                      Point pos,
                                      Color3B color){
    auto font = GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL;
    makePerminateBMFLabel(msg, pos, color, Vec2(1, 0.5), font);
}


void LabelManager::makePerminateLabel(
                                      const char *const msg,
                                      float percentWidth,
                                      float percentHeight,
                                      Color3B color,
                                      Point anchor){
    
    Size size = Director::getInstance()->getWinSize();
    Point pos = Vec2(size.width*percentWidth,size.height*percentHeight);
    auto font = GameAssets::Fonts::BMF::ALPHA_NUM::ARIAL;
    makePerminateBMFLabel(msg, pos, color, anchor,font);
}



void LabelManager::makePerminateBMFLabel(const char *const msg, Point pos, Color3B color, Point anchor, const char *font){

    char szValue2[64] = {0};
    sprintf(szValue2,"%s",msg);
    Label* l = Label::createWithBMFont(font,szValue2);
    l->setWidth( 200);
    l->setColor(color);
    l->setAnchorPoint(anchor);
    l->setPosition(pos);
    l->setTag(GameAssets::Sprite::TEMP_LABEL);

    // add to registry
    s_ActiveLabels.push_back(l);

    // add to game layer
    if (m_target == nullptr){
        m_target = GameLayer::getInstance();
    }

    //l->setScale(4);

    // add to game layer
    m_target->addChild(l,LayerLevel::kCtrl);


}



void LabelManager::removeFromRegistry(cocos2d::Label* o )
{
    auto i = std::find(s_ActiveLabels.begin(),s_ActiveLabels.begin(),o);
    if ( i != s_ActiveLabels.end()){
       s_ActiveLabels.erase(i);
    }
}

void LabelManager::clear()
{
    for(auto o: s_ActiveLabels)
    {
        o->removeFromParentAndCleanup(true);
    }
    s_ActiveLabels.clear();
}



