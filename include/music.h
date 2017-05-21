#ifndef MUSIC_H
#define MUSIC_H

#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <memory>

using std::string;
using std::shared_ptr;

class Music {
    private:
        shared_ptr<Mix_Music> m_music;

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
