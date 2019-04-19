#pragma once

#include "cocos2d.h"

#include <string>

using namespace std;
using namespace cocos2d;

namespace Assets {
    
    namespace Common {

    }
    namespace WelcomeLayer {

    }
    namespace GameLayer {

    }
    namespace OptionsLayer {

    }
    namespace FailedLayer {

    }
    namespace SuccessLayer {

    }
}

namespace GameState
{
    enum{
        IN_WELCOME ,
        IN_CONFIG ,
        IN_PLAY ,
        PAUSED ,
        IN_TRANSITION ,
        GAME_OVER
    };
}



namespace LayerLevel {
    enum {
        kBackground,
        kBackground1,
        kBackground2,
        kHud,
        kHud1,
        kHud2,
        kCtrl,
        kCtrl1,
        kCtrl2,
        kGame,
        kDlg
    };
}

namespace GameAssets {


    namespace Backgrounds {
        const char* const WELCOME_BACKGROUND           = "space-cave.jpg" ;
        const char* const OPTIONS_BACKGROUND           = "Options.png";
        const char* const FAILED_BACKGROUND            = "GameOver.png";
        const char* const GAME_LAYER                   = "star-space-x.png";
        const char* const SUCCESS_BACKGROUND           = "space-cave.jpg";
    }

    namespace Btn {
        const char* const  BTN_BACK                     =  "west.png";
        const char* const  BTN_BACK_SEL                 =  "west_sel.png"; 
        const char* const  BTN_WEST                     =  "west.png";
        const char* const  BTN_EAST                     =  "east.png";
        const char* const  BTN_EXIT                     =  "exit.png";
        const char* const  BTN_EXIT_SEL                 =  "exit_sel.png";
        const char* const  BTN_PLAY                     =  "play.png";
        const char* const  BTN_PLAY_SEL                 =  "play_sel.png";

    }
    
    
    namespace Sound {
        const char* const FAILED_SOUND                 =   "game-over-evil.wav";
        const char* const GAME_OVER                    =   "game-over.wav";
        const char* const ENERGY_WEAPON                =   "lazer.wav";
        const char* const DEATH_RAY                    =   "deathray.mp3";
        const char* const LEVEL_COMPLETE_SOUND         =   "level-completed.wav";
        const char* const GAME_BACKGROUND_SOUND        =   "background.mp3";
        const char* const BTN_SELECTED_SOUND           =   "bell-0104.wav";
        const char* const NUCLEAR_SOUND                =   "thunder.wav";
        const char* const HYPERSPACE_SOUND             =   "random.wav";
        const char* const GEM_PICKIP_SOUND             =   "debris.wav";
        const char* const COUNTDOWN                    =   "countdown.mp3";
        const char* const WAWAWA                       =   "wawawa.mp3";
        const char* const TADA                         =   "tada.mp3";
        const char* const ROCK_SLIDE                   =   "rockslide.mp3";
        const char* const SHOTGUN                      =    "shotgun.wav";
    }

    
    namespace Layer{
        const int           TAG_GAME_LAYER                  = 1111;
        const int           TAG_CTRL_LAYER                  = 2222;
        const int           TAG_HUD_LAYER                   = 3333;
        const int           TAG_WELCOME_LAYER               = 4444;
        const int           TAG_FAILED_LAYER                = 5555;
        const int           TAG_OPTIONS_LAYER               = 6666;
        const int           TAG_BACKGROUND_LAYER            = 7777;
    }

    namespace Sprite {
        
        
        const int           TAG_HOSTILE                 = 74589;
        
        const int           TEMP_LABEL                 = -45;
        
        const char* const   PLAYER_PNG                 =  "tank.png";
        const int           TAG_PLAYER                 = 100;

        const char* const   SHIELD_PNG                 = "ring.128.1.png";
        const char* const   SHIELD_LOW_PNG             = "ring.red.128.1.png";
        
        const char* const   PNG_PROJECTILE              = "eb.png";
        const int           TAG_PROJECTILE              = 101;
        const int           HIT_PROJECTILE              = 701;
        const int           WEIGHT_PROJECTILE           = 100;
        

        const int           MAX_ASTEROID_MAGNITUDE      = 6;
        const int           TAG_METEOR                  = 102;
        const int           WEIGHT_METEOR_LARGE         = 100;
        const int           WEIGHT_METEOR_MEDIUM        = 60;
        const int           WEIGHT_METEOR_SMALL         = 40;
        const int           VALUE_METEOR_LARGE          = 150;
        const int           VALUE_METEOR_MEDIUM         = 350;
        const int           VALUE_METEOR_SMALL          = 750;

        
        const char* const   PNG_ALIEN                   = "Alien.png";//"blue_hammer.png";//"badalien2.png";
        const int           TAG_ALIEN                   = 103;
        const int           HIT_ALIEN                   = 50;
        const int           WEIGHT_ALIEN                = 40;
        const int           VALUE_ALIEN                 = 40;
        
        const char* const   PNG_SPIDER                   = "spider.png";
        const int           TAG_SPIDER                   = 1114;
        const int           WEIGHT_SPIDER                = 40;
        const int           VALUE_SPIDER                 = 40;
        
        
        const char* const   PNG_SEEKER                   = "missile.01.png";
        const int           TAG_SEEKER                   = 104;
        const int           WEIGHT_SEEKER                = 90;
        const int           VALUE_SEEKER                 = 90;
        
        
        const char* const   PNG_ALIEN_PROJECTILE        = "eb.png";
        const int           TAG_ALIEN_PROJECTILE        = 105;
        const int           WEIGHT_ALIEN_PROJECTILE     = 50;
        const int           VALUE_ALIEN_PROJECTILE      = 50;
        
        const char* const   PNG_MINE                    = "mine.png";
        const int           TAG_MINE                    = 106;
        const int           WEIGHT_MINE                 = 60;
        const int           VALUE_MINE                  = 60;
        
        
        const int           POWERUP_GREENGEM            = 0;
        const char* const   POWERUP_GREENGEM_PNG        = "greengem.png";
        const int           TAG_GREENGEM                =  107;
        const char* const   MSG_GREENGEM                =  "Green Gem";
        const int           VALUE_GREENGEM              =  1600;
        
        const int           POWERUP_REDGEM              = 1;
        const char* const   POWERUP_REDGEM_PNG          = "redgem.png";
        const int           TAG_REDGEM                  = 108;
        const char* const   MSG_REDGEM                  = "Red Gem";
        const int           VALUE_REDGEM                = 800;
        
        const int           POWERUP_YELLOWGEM           = 2;
        const char* const   POWERUP_YELLOWGEM_PNG       = "yellowgem.png";
        const int           TAG_YELLOWGEM               = 109;
        const char* const   MSG_YELLOWGEM               = "Yellow Gem";
        const int           VALUE_YELLOWGEM            = 1200;
        
        const int           POWERUP_PURPLEGEM           = 3;
        const char* const   POWERUP_PURPLEGEM_PNG       = "purplegem.png";
        const int           TAG_PURPLEGEM               = 3;
        const char* const   MSG_PURPLEGEM               = "Purple Gem";
        const int           VALUE_PURPLEGEM              = 2200;
        
        const int           POWERUP_SHIELD              = 4;
        const char* const   POWERUP_SHIELD_PNG          = "shield.png";
        const int           TAG_POWERUP_SHIELD          = 4;
        const char* const   MSG_POWERUP_SHIELD          = "Shield";
        const int           VALUE_POWERUP_SHIELD = 250;
        
        const int           POWERUP_CONSTANT_FIRE        = 5;
        const char* const   POWERUP_CONSTANT_FIRE_PNG    = "autofire.png";
        const int           TAG_POWERUP_CONSTANT_FIRE    = 5;
        const char* const   MSG_POWERUP_CONSTANT_FIRE    = "Autofire";
        const int           VALUE_POWERUP_CONSTANT_FIRE = 750;
        
        const int           POWERUP_NUCLEAR              = 6;
        const char* const   POWERUP_NUCLEAR_PNG          = "nuclear.png";
        const int           TAG_POWERUP_NUCLEAR          = 6;
        const char* const   MSG_POWERUP_NUCLEAR          = "Nuclear Bomb";
        const int           VALUE_POWERUP_NUCLEAR = 1800;
        
        const int           POWERUP_HEALTH               = 7;
        const char* const   POWERUP_HEALTH_PNG           = "health.png";
        const int           TAG_POWERUP_HEALTH           = 7;
        const char* const   MSG_POWERUP_HEALTH           = "Health 100%";
        const int           VALUE_POWERUP_HEALTH = 250;


        const char* const  BTN_BACK                     =  "west.png";
        const char* const  BTN_BACK_SEL                 =  "west_sel.png";

        const char* const  BTN_WEST                     =  "west.png";
        const char* const  BTN_WEST_SEL                     =  "west.png";
        const char* const  BTN_EAST                     =  "east.png";

        const char* const  BTN_EXIT                     =  "exit.png";
        const char* const  BTN_EXIT_SEL                 =  "exit_sel.png";

        const char* const  BTN_PLAY                     =  "play.png";
        const char* const  BTN_PLAY_SEL                 =  "play_sel.png";

    }
}

