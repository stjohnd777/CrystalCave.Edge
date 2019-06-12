#pragma once

#include "cocos2d.h"

#include <string>
#include <vector>

using namespace std;
using namespace cocos2d;


namespace LayerLevel {
    enum {
        BOTTOM = -10,
        kBackground = 0,
        kBackground1 = 2,
        kBackground2 = 3,
        kGame0 = 100,
        kGame2 = 102,
        kGame3 = 104,
        kGame4  = 106,
        kHud  = 200,
        kHud1= 202,
        kHud2 = 204,
        kCtrl = 1000,
        kCtrl1 = 1002,
        kCtrl2 = 1004,
        kDlg= 2000,
        TOP  = 10000
    };
}

namespace GameAssets {

    //float MY_CONTENT_SCALE = 1;

    const char* const WELCOME_BACKGROUND           = "game.png" ;
    const char* const OPTIONS_BACKGROUND           = "Options.png";
    const char* const FAILED_BACKGROUND            = "GameOver.png";
    const char* const FAILED_BACKGROUND_2          = "game.png";
    const char* const GAME_LAYER_BACKGROUND                   = "star-space-x.png";//game.png";
    const char* const SUCCESS_BACKGROUND           = "game.png";


    
    namespace TAGS {

        const int PLAYER = 10;
        const int PLAYER_PROJECTILE = 12;

        // Fixture  [0-100] with Physics Body non-dynamic
        const int TR = 80;
        const int TR_TOP = 81;

        // Hostile object with PhysicsBody non-dynamic [100-200]
        const int SPIKE                     = 100;
        const int MINE                      = 140;
        const int ACID                      = 150;
        const int LAVA                      = 150;
        
        const int ELECTRIC_FENCE_VERTICLE   = 110;
        const int ELECTRIC_FENCE_HORIZONTAL = 120;
        const int LIGHTNING                 = 130;
        const int SCANBEAM                  = 160;
        
        const int SEEKER                    = 170;
      

        const int  WELCOME_LAYER               = 1000;
        const int  GAME_LAYER                  = 1002;
        const int  HUD_LAYER                   = 1004;
        const int  CTRL_LAYER                  = 1006;
        const int  FAILED_LAYER                = 1008;
        const int  SUCCESS_LAYER               = 1010;
        const int  OPTIONS_LAYER               = 1012;

        
        const int  TEMP_LABEL                  = 88;
    }


    
    namespace Sound {

        const char* const GAME_BACKGROUND_SOUND        =   "Sound/bg/ominious_mood.wav";

        const char* const FAILED_SOUND                 =   "Sound/failed/game-over-evil.wav";
        const char* const GAME_OVER                    =   "Sound/failed/game-over.wav";

        const char* const LEVEL_COMPLETE               =   "Sound/Success/level-completed.wav";


        const char* const WAWAWA                       =   "Sound/Failed/wawawa.mp3";
        const char* const TADA                         =   "Sound/success/tada.mp3";
        const char* const ROCK_SLIDE                   =   "Sound/rockslide.mp3";
        const char* const SHOTGUN                      =   "Sound/shotgun.wav";
        const char* const WOOSH                        =   "Sound/woosh.wav";
        const char* const THRUST                       =   "Sound/thrusters.wav";
        const char* const BELL                         =   "Sound/bell-0104.wav";
        const char* const ALARM                        =   "Sound/Alarm/alarm.wav";
        const char* const ALARMS                        =   "Sound/Alarm/alarms.wav";
        


        const char* const EXPLOSION                     =   "Sound/explosion.wav";
        const char* const DEBRIS                        =   "Sound/debris.wav";
        const char* const SIREN                         =   "Sound/Alarms/Siren.wav";
        const char* const COUNTDOWN                     =   "Sound/countdown.mp3";
        const char* const PICK_UP                       =   "Sound/dingding.wav";
        const char* const APPLAUSE                      =   "Sound/Success/applause.mp3";
        const char* const FIRE_PROJECTILE               =   "Sound/lazer.wav";
        const char* const ELECTRIC_0                    =   "Sound/elec.wav";
        const char* const ELECTRIC_1                    =   "Sound/electric-arcing-dry.aiff";
        
        
//        std::vector<const char* const> GetAllSoundEffect(){
//
//            std::vector<const char* const> snds =
//            {
//                FAILED_SOUND,GAME_OVER,LEVEL_COMPLETE
//                ,WAWAWA,TADA,ROCK_SLIDE,SHOTGUN,WOOSH,THRUST,BELL
//                ,EXPLOSION,DEBRIS,COUNTDOWN,APPLAUSE,FIRE_PROJECTILE,ELECTRIC_0,ELECTRIC_1
//            };
//            return snds;
//        }

    }



    namespace Sprite {
        
        
        const char* const  MINE = "TMX/space_mine.png";

        const char* const Stalactite = "TMX/stalactite.png";
        const char* const QuartzCrystalSouth = "TMX/QuartzCrystalSouth.png";
        const char* const QuartzCrystalNorth = "TMX/QuartzCrystalNorth.png";
        const char* const QuartzCrystalNorth3 = "TMX/QuartzCrystalNorth3.png";
        const char* const QuartzCrystalNorthFlipped = "TMX/QuartzCrystalNorthFliped.png";
        const char* const QuartzCrystalNorthFliped3 ="TMX/QuartzCrystalNorthFliped3.png";
        const char* const Geyzer = "TMX/geyzer.png";
        const char* const FINISH = "TMX/vfinish.png";
        const char* const STEAL_BALL = "TMX/steelball.png";
        
        


        const char* const  BTN_BACK                     =  "SIFI_GUI/Normal/PreviousPage.png";
        const char* const  BTN_BACK_SEL                 =  "SIFI_GUI/Disabled/PreviousPage.png";

        const char* const  BTN_NORTH                    =  "SIFI_GUI/Normal/UpArrow.png";
        const char* const  BTN_NORTH_SEL                =  "SIFI_GUI/Disabled/UpArrow.png";;

        const char* const  BTN_SOUTH                    = "SIFI_GUI/Normal/DownArrow.png";
        const char* const  BTN_SOUTH_SEL                = "SIFI_GUI/Disabled/DownArrow.png";

        const char* const  BTN_WEST                     =  "SIFI_GUI/Normal/LeftArrow.png";
        const char* const  BTN_WEST_SEL                 =  "SIFI_GUI/Disabled/LeftArrow.png";

        const char* const  BTN_EAST                     =  "SIFI_GUI/Normal/RightArrow.png";
        const char* const  BTN_EAST_SEL                 =  "SIFI_GUI/Disabled/RightArrow.png";

        const char* const  BTN_CLOSE                    =  "SIFI_GUI/Normal/Close.png";
        const char* const  BTN_CLOSE_SEL                =  "SIFI_GUI/Disabled/Close.png";

        const char* const  BTN_EXIT                     =  "SIFI_GUI/Normal/Close.png";
        const char* const  BTN_EXIT_SEL                 =  "SIFI_GUI/Disabled/Close.png";

        const char* const  BTN_PLAY                     =  "SIFI_GUI/Normal/Play.png" ;
        const char* const  BTN_PLAY_SEL                 =  "SIFI_GUI/Disabled/Play.png";

        const char* const  BTN_PAUSE                    =  "SIFI_GUI/Normal/Pause.png" ;
        const char* const  BTN_PAUSE_SEL                =  "SIFI_GUI/Disabled/Pause.png";

        const char* const  BTN_SETTINGS                 =  "SIFI_GUI/Normal/Settings.png" ;
        const char* const  BTN_SETTINGS_SEL             =  "SIFI_GUI/Disabled/Settings.png";
        
        const char* const  BTN_RELOAD                 =  "SIFI_GUI/Normal/Reload.png" ;
        const char* const  BTN_RELOAD_SEL             =  "SIFI_GUI/Disabled/Reload.png";
        
        const char* const  BTN_SOUND                 =  "SIFI_GUI/Normal/Sound.png" ;
        const char* const  BTN_SOUND_SEL             =  "SIFI_GUI/Disabled/Sound.png";
        
        
        const char* const  LEVEL_BG                     =  "SIFI_GUI/Window/Window.png";
        
        const char* const  BTN_MENU                     =  "SIFI_GUI/Normal/Menu.png" ;
        const char* const  BTN_MENU_SEL                 =  "SIFI_GUI/Disabled/Menu.png";
        
        const char* const  BTN_LOCKED                   =  "SIFI_GUI/Normal/Locked.png" ;
        const char* const  BTN_LOCKED_SEL               =  "SIFI_GUI/Disabled/Locked.png";
        
        const char* const  STAR_ON                      =  "SIFI_GUI/GameIcon/StarON.png" ;
        const char* const  STAR_OFF                     =  "SIFI_GUI/GameIcon/StarOFF.png";
        
        const char* const  DLG_MED                      =  "SIFI_GUI/Window/MediumDialogBox.png";
        const char* const  DLG_WIDE                     =  "SIFI_GUI/Window/WideDialogBox.png";
        const char* const  WINDOW                       =  "SIFI_GUI/Window/Window.png";
        
        const char* const  WINDOW_MED                  =  "SIFI_GUI/Window/WindowMedium.png";
        const char* const  WINDOW_POPUP                =  "SIFI_GUI/Window/WindowPopup.png";
        const char* const  WINDOW_TALL                 =  "SIFI_GUI/Window/WindowTall.png";
      

    }

    namespace PE_KEY {
        const char* const QuartzCrystalSouth =  "QuartzCrystalNorthFliped";
        const char* const QuartzCrystalNorth = "QuartzCrystalNorth";

        const char* const QuartzCrystalNorthFliped3 = "QuartzCrystalNorthFliped3";
        const char* const QuartzCrystalNorth3 = "QuartzCrystalNorth3";

        const char* const Geyzer = "geyzer";

    }


    namespace Fonts {
        namespace BMF {

            namespace NUM {

                const char* const DEFAULT    = "fonts/bmf/num/font_num_orange.fnt";

                const char* const CRISP      = "fonts/bmf/num/font_num_crisp.fnt";

                const char* const HIT_LABEL  = "fonts/bmf/num/font_num_orange.fnt";
            }


            namespace ALPHA_NUM {

                const char* const DEFAULT  = "fonts/bmf/alpha/CleanFont.fnt";

                const char* const HUD      = "fonts/bmf/alpha/CleanFont.fnt";

                const char* const ARIAL    = "fonts/bmf/alpha/arial_message.fnt";

                const char* const TELETYPE    = "fonts/bmf/alpha/teletype_messages.fnt";

                const char* const FUTURA_48    = "fonts/bmf/alpha/futura-48.fnt";

            }
        }
        namespace TTF {

            const char* const ABDUCTION   = "fonts/ttf/Abduction.ttf";

            const char* const MESS   = "fonts/ttf/ADamnMess.ttf";

            const char* const ARIAL   = "fonts/ttf/arial.ttf";

            const char* const MarkerFelt   = "fonts/ttf/MarkerFelt.ttf";

            const char* const ScissorCuts   = "fonts/ttf/ScissorCuts.ttf";
        }
    }
    
}

