#pragma once

#include "cocos2d.h"

#include "BaseLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class OptionLayer : public BaseLayer   {
    
public:
    
    static cocos2d::Scene* scene();
    
    CREATE_FUNC(OptionLayer);
    
    bool init();

    void initBackGround() ;
    
private:
    
    MenuItemToggle* itemToggleMusic;
    MenuItem *itemOn;
    MenuItem *itemOff;
    
    
    Menu*         pMenuDifficulty;
    MenuItemFont* pEasyItem;
    MenuItemFont* pMedItem ;
    MenuItemFont* pHardItem ;
    
    Menu*         pMenuTilt;
    MenuItemFont* pL1Item;
    MenuItemFont* pL2Item;
    MenuItemFont* pL3Item;
 
    MenuItemFont *backgroundMusicMenuItem;
    
    OptionLayer();
    
    void setData();

    void controls(Ref* pSender);

    void menuBackgroundMusicCallback(Ref* pSender);
    void menuCloseCallback(Ref* pSender);
    void nillCallback(Ref* pSender);

    void advancedOptions(Ref* pSender);
};
