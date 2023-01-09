#pragma once
#include "_Core.h"
#include "utility.h"

#include <MINIAUDIO/miniaudio.h>

namespace core {

    class CORE_API Sound
    {
    private:
        std::string soundFile;
        ma_engine engine;
        ma_sound currentSound;

    public:
        Sound();
        ~Sound();
        static void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
        bool loadSound(std::string soundFile);
        bool playSound();
        bool stopSound();
        void setVolume(float volume);
        float getVolume();
    };

}