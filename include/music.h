#ifndef MUSIC_H
#define MUSIC_H

#include "SDL2/SDL_mixer.h"

#include <iostream>

using std::string;

class Music {
    private:
        Mix_Music* m_music;

    public:
        Music();
        Music(string file);
        ~Music();

        void play(int times);
        void stop(int ms = 0);
        void open(string file);
        bool is_open();
};

#endif
