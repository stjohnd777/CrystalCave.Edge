#pragma once

#include "cocos2d.h"

#include <string>

using namespace std;
using namespace cocos2d;


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

    const char* const WELCOME_BACKGROUND           = "space-cave.jpg" ;
    const char* const OPTIONS_BACKGROUND           = "Options.png";
    const char* const FAILED_BACKGROUND            = "GameOver.png";
    const char* const GAME_LAYER                   = "game.png";
    const char* const SUCCESS_BACKGROUND           = "space-cave.jpg";

    
    namespace Sound {

        const char* const GAME_BACKGROUND_SOUND        =   "Sound/bg/000665981.wav";

        const char* const FAILED_SOUND                 =   "Sound/failed/game-over-evil.wav";
        const char* const GAME_OVER                    =   "Sound/failed/game-over.wav";

        const char* const LEVEL_COMPLETE_SOUND         =   "Sound/Success/level-completed.wav";

        const char* const BTN_SELECTED_SOUND           =   "Sound/bell-0104.wav";

        const char* const GEM_PICKIP_SOUND             =   "Sound/debris.wav";

        const char* const WAWAWA                       =   "Sound/Failed/wawawa.mp3";
        const char* const TADA                         =   "Sound/success/tada.mp3";
        const char* const ROCK_SLIDE                   =   "Sound/rockslide.mp3";
        const char* const SHOTGUN                      =   "Sound/shotgun.wav";
        const char* const WOOSH                        =   "Sound/swoosh.wav";
    }

    
    namespace Layer{

        const int           TAG_GAME_LAYER                  = 1000;
        const int           TAG_HUD_LAYER                   = 1100;
        const int           TAG_CTRL_LAYER                  = 1200;

        const int           TAG_WELCOME_LAYER               = 100;

        const int           TAG_FAILED_LAYER                = 200;
        const int           TAG_SUCCESS_LAYER               = 300;
        const int           TAG_OPTIONS_LAYER               = 400;

    }

    namespace Sprite {

        const int           TAG_HOSTILE                 = -1000;
        const int           TEMP_LABEL                  = 1010;

        const char* const  BTN_BACK                     =  "SIFI_GUI/Normal/PreviousPage.png";
        const char* const  BTN_BACK_SEL                 =  "SIFI_GUI/Disabled/PreviousPage.png";

        const char* const  BTN_NORTH                     =  "SIFI_GUI/Normal/UpArrow.png";
        const char* const  BTN_NORTH_SEL                 =  "SIFI_GUI/Disabled/UpArrow.png";;

        const char* const  BTN_SOUTH                     = "SIFI_GUI/Normal/DownArrow.png";
        const char* const  BTN_SOUTH_SEL                 = "SIFI_GUI/Disabled/DownArrow.png";

        const char* const  BTN_WEST                     =  "SIFI_GUI/Normal/LeftArrow.png";
        const char* const  BTN_WEST_SEL                 =  "SIFI_GUI/Disabled/LeftArrow.png";

        const char* const  BTN_EAST                     =  "SIFI_GUI/Normal/RightArrow.png";
        const char* const  BTN_EAST_SEL                 =  "SIFI_GUI/Disabled/RightArrow.png";

        const char* const  BTN_CLOSE                     =  "SIFI_GUI/Normal/Close.png";
        const char* const  BTN_CLOSE_SEL                 =  "SIFI_GUI/Disabled/Close.png";

        const char* const  BTN_EXIT                     =  "SIFI_GUI/Normal/Close.png";
        const char* const  BTN_EXIT_SEL                 =  "SIFI_GUI/Disabled/Close.png";

        const char* const  BTN_PLAY                     =  "SIFI_GUI/Normal/Play.png" ;
        const char* const  BTN_PLAY_SEL                 =  "SIFI_GUI/Disabled/Play.png";

        const char* const  BTN_PAUSE                     =  "SIFI_GUI/Normal/Pause.png" ;
        const char* const  BTN_PAUSE_SEL                 =  "SIFI_GUI/Disabled/Pause.png";

        const char* const  BTN_SETTINGS                  =  "SIFI_GUI/Normal/Settings.png" ;
        const char* const  BTN_SETTINGS_SEL              =  "SIFI_GUI/Disabled/Settings.png";

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

