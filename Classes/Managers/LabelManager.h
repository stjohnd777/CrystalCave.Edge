#pragma once

#include "cocos2d.h"
#include <vector>

class LabelManager {
    
public:
    
    static LabelManager* getInstance();

    // 2
    CC_SYNTHESIZE(float, m_DelayTime, DelayTime);

    // 1
    CC_SYNTHESIZE(float, m_FadeTime, FadeTime);
    
    // GameLayer::getInstance()
    CC_SYNTHESIZE(cocos2d::Node*, m_target, Target);
    
    std::vector< cocos2d::Label* >    s_ActiveLabels;

   
    // FontManager::FONT_NUM_ORANGE.c_str()
    // Vec2(0.5, 0.5)
    void makeHitLabel(int hit, cocos2d::Point pos,cocos2d::Color3B color);
    
    // FontManager::FONT_MSG_ARIAL.c_str()
    void makeFadingLabel(const char *const msg, cocos2d::Point pos, cocos2d::Color3B color);
    // FontManager::FONT_MSG_ARIAL.c_str()
    void makePerminateLabel(const char *const msg, cocos2d::Point pos, cocos2d::Color3B color);
    
    
    
    void makeFadingLabel(const char *const msg, float percentWidth, float percentHeight, cocos2d::Color3B color, cocos2d::Point anchor);
    
    void makePerminateLabel(const char *const msg, float percentWidth, float percentHeight, cocos2d::Color3B color, cocos2d::Point anchor);
    
    
    
    void makeFadingLabel(const char *const msg, cocos2d::Point pos, cocos2d::Color3B color, cocos2d::Point anchor, const char *font);
    
    void makePerminateLabel(const char *const msg, cocos2d::Point pos, cocos2d::Color3B color, cocos2d::Point anchor, const char *font);
    
    
   void removeFromRegistry(cocos2d::Label*);
    
   void clear();
    
private:
    
    LabelManager();
    
    static LabelManager* INSTANCE;

};

    