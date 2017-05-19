#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <unordered_map>
#include <memory> // shared_ptr

using std::string;
using std::unordered_map;
using std::shared_ptr;

class Resources {
    private:
        static unordered_map<string, shared_ptr<SDL_Texture> > m_image_table;
        static unordered_map<string, shared_ptr<Mix_Music> > m_music_table;
        static unordered_map<string, shared_ptr<Mix_Chunk> > m_sound_table;

    public:
        static shared_ptr<SDL_Texture> get_image(string file);
        static void clear_images();

        static shared_ptr<Mix_Music> get_music(string file);
        static void clear_music();

        static shared_ptr<Mix_Chunk> get_sound(string file);
        static void clear_sound();
};

#endif
