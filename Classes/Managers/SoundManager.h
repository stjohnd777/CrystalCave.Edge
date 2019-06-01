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
        //auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

        // TODO : solve problem with resolving GameAssets::Sound::GetAllSoundEffect()
        /*
        for ( auto sndFile : GameAssets::Sound::GetAllSoundEffect() ){
           audio->preloadEffect(sndFile);
        }
        */
    }

    static void playBackgroundMusic(std::string loop,float volume = .4)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(loop.c_str(), true);
    }
    static void stopBackgroundMusic()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    

    static int playEffect(std::string effect,bool loop = false)
    {
        return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(effect.c_str(),loop);
    }

    static void stopEffect(int soundId)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect( soundId);
    }

    static int alarm(bool loop = false)
    {
        return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::ALARM,loop);
    }
    
    
    static int alarms(bool loop = false)
    {
        return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::ALARMS,loop);
    }
    
    static int siren(bool loop = false)
    {
        return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::SIREN,loop);
    }
    
    
    static int electric(bool loop = false)
    {
        return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::ELECTRIC_0,loop);
    }
    static int electric_arc(bool loop = false)
    {
        return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::ELECTRIC_1),loop;
    }
    

    
    static void projectile_weapon()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::FIRE_PROJECTILE);
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
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GameAssets::Sound::BELL);
    }
    
};
