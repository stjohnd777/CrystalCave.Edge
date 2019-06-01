#pragma once

#include <string>
#include "cocos2d.h"
 

class SceneManager {

    CC_SYNTHESIZE(int, m_currrentScene, CurrentScene)

public:
    enum {
        WELCOME_LAYER,
        OPTIONS_LAYER,
        ADVANCED_OPTIONS,
        GAME_LAYER,
        FAILURE_LAYER,
        SUCCESS_LAYER
    };

public:
    
    static SceneManager * getInstance();

    void Welcome();

    void Options();
    
    void LevelSelect();

    void Game(std::string level);

    void Failed();

    void Success();

    void Exit();

private :

    static SceneManager * INSTANCE ;
};
