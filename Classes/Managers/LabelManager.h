#pragma once

#include <vector>

#include "cocos2d.h"

#include "MyMacros.h"

class LabelManager {
    
public:
    
    static LabelManager* getInstance();

    GETTERSETTER(cocos2d::Node*, m_target, Target);
    
    GETTERSETTER(float, m_DelayTime, DelayTime);
    GETTERSETTER(float, m_FadeTime, FadeTime);
   
    
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

    
