#ifndef SOUND_H
#define SOUND_H

#include "SDL2/SDL_mixer.h"

#include <iostream>

using std::string;

class Sound {
    private:
        Mix_Chunk* m_chunk;
        int m_channel;

    public:
        Sound();
        Sound(string file);

        void play(int times);
        void stop();
        void open(string file);
        bool is_open();
};

#endif
