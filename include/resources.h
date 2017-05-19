#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <unordered_map>
#include <memory> // shared_ptr
#include <string> // to_string

using std::string;
using std::unordered_map;
using std::shared_ptr;
using std::to_string;

class Resources {
    private:
        static unordered_map<string, shared_ptr<SDL_Texture> > m_image_table;
        static unordered_map<string, shared_ptr<Mix_Music> > m_music_table;
        static unordered_map<string, shared_ptr<Mix_Chunk> > m_sound_table;
        static unordered_map<string, shared_ptr<TTF_Font> > m_font_table;

    public:
        static shared_ptr<SDL_Texture> get_image(string file);
        static void clear_images();

        static shared_ptr<Mix_Music> get_music(string file);
        static void clear_musics();

        static shared_ptr<Mix_Chunk> get_sound(string file);
        static void clear_sounds();

        static shared_ptr<TTF_Font> get_font(string file, int font_size);
        static void clear_fonts();
};

#endif
