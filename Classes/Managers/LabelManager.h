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
    
    CC_SYNTHESIZE(cocos2d::Node*, m_target, Target);
    
    std::vector< cocos2d::Label* >    s_ActiveLabels;


    void makeHitLabel(
                      int hit,
                      cocos2d::Point pos,
                      cocos2d::Color3B color = cocos2d::Color3B::RED);
    

    void makeFadingLabel(
                         const char *const msg,
                         cocos2d::Point pos,
                         cocos2d::Color3B color);
    
    
    
    void makeFadingLabel(
                         const char *const msg,
                         float percentWidth,
                         float percentHeight,
                         cocos2d::Color3B color,
                         cocos2d::Point anchor);

    void makeFadingLabel(
                         const char *const msg,
                         cocos2d::Point pos,
                         cocos2d::Color3B color,
                         cocos2d::Point anchor,
                         const char *font);




    void makePerminateLabel(
                        const char *const msg,
                        cocos2d::Point pos,
                        cocos2d::Color3B color = cocos2d::Color3B::WHITE);

    void makePerminateLabel(
                        const char *const msg,
                        float percentWidth,
                        float percentHeight,
                        cocos2d::Color3B color,
                        cocos2d::Point anchor);
    
    

    void makePerminateBMFLabel(
                        const char *const msg,
                        cocos2d::Point pos,
                        cocos2d::Color3B color,
                        cocos2d::Point anchor,
                        const char *font);
    
    
   void removeFromRegistry(cocos2d::Label*);
    
   void clear();
    
private:
    
    LabelManager();
    
    static LabelManager* INSTANCE;

};

    
