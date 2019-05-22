//
//  SoundManager.hpp
//  DsjTemplate
//
//  Created by Daniel St. John on 5/5/16.
//
//

#pragma once

#include "GameAssets.h"
#include "SimpleAudioEngine.h"
#include <string>

class SoundManager {

public:

    static void PreLoadSound(){

        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();


        // pre-loading background music and effects. You could pre-load
        // effects, perhaps on app startup so they are already loaded
        // when you want to use them.
//        audio->preloadBackgroundMusic("myMusic1.mp3");
//        audio->preloadBackgroundMusic("myMusic2.mp3");
//
//        audio->preloadEffect("myEffect1.mp3");
//        audio->preloadEffect("myEffect2.mp3");

        // unload a sound from cache. If you are finished with a sound and
        // you wont use it anymore in your game. unload it to free up
        // resources.
        //audio->unloadEffect("myEffect1.mp3");

//        for ( auto sndFile : GameAssets::Sound::GetAllSoundEffectsFiles() ){
//            GetAllSoundEffectsFiles
//        }

    }

    static void playBackgroundMusic(std::string loop,float volume = .4)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume( volume);
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(loop.c_str(), true);
    }

    static void playEffect(std::string effect)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(effect.c_str());
    }


    static void stopBackgroundMusic()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }


    static void bell()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::BELL);
    }

    static void explosion()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::EXPLOSION);
    }

    static void shootgun()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::SHOTGUN);
    }

    static void woosh()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::WOOSH);
    }

    static void debris()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::DEBRIS);
    }

    static void wawawa()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::WAWAWA);
    }

    static void tada()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::TADA);
    }

    static void rockslide()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::ROCK_SLIDE);
    }
    static void siren()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::SIREN);
    }

    static void countdown()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::COUNTDOWN);
    }

    static void applause()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::APPLAUSE);
    }
    static void pickup()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::PICK_UP);
    }
    static void gameover()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::GAME_OVER);
    }

    static void levelcomplete()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::LEVEL_COMPLETE);
    }

    static void btnselected()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::BTN_SELECTED);
    }

    static void projectile_weapon()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::FIRE_PROJECTILE);
    }
    static void electric()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::ELECTRIC_0);
    }
    static void electric_arc()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::ELECTRIC_ARC);
    }



};
