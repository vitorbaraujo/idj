#include "resources.h"
#include "game.h"

unordered_map<string, shared_ptr<SDL_Texture> > Resources::m_image_table;
unordered_map<string, shared_ptr<Mix_Music> > Resources::m_music_table;
unordered_map<string, shared_ptr<Mix_Chunk> > Resources::m_sound_table;
unordered_map<string, shared_ptr<TTF_Font> > Resources::m_font_table;

shared_ptr<SDL_Texture> Resources::get_image(string file){
    if(m_image_table.find(file) == m_image_table.end()){
        SDL_Texture* texture = IMG_LoadTexture(Game::get_instance().get_renderer(), file.c_str());

        if(texture == nullptr){
            printf("IMG_LoadTexture error: %s\n", SDL_GetError());
            exit(-1);
        }

        shared_ptr<SDL_Texture> ptr(texture, [](SDL_Texture *t){ SDL_DestroyTexture(t); });
        m_image_table.emplace(file, ptr);
    }

    return m_image_table[file];
}

void Resources::clear_images(){
    for(auto it = m_image_table.begin(); it != m_image_table.end(); ++it){
        if(it->second.unique()){
            m_image_table.erase(it);
        }
    }
}

shared_ptr<Mix_Music> Resources::get_music(string file){
    if(m_music_table.find(file) == m_music_table.end()){
        Mix_Music* music = Mix_LoadMUS(file.c_str());

        if(music == nullptr){
            printf("Mix_LoadMUS error: %s\n", SDL_GetError());
            exit(-1);
        }

        shared_ptr<Mix_Music> ptr(music, [](Mix_Music* m){ Mix_FreeMusic(m); });
        m_music_table.emplace(file, ptr);
    }

    return m_music_table[file];
}

void Resources::clear_musics(){
    for(auto it = m_music_table.begin(); it != m_music_table.end(); ++it){
        if(it->second.unique()){
            m_music_table.erase(it);
        }
    }
}

shared_ptr<Mix_Chunk> Resources::get_sound(string file){
    if(m_sound_table.find(file) == m_sound_table.end()){
        Mix_Chunk* sound = Mix_LoadWAV(file.c_str());

        if(sound == nullptr){
            printf("Mix_LoadWAV error: %s\n", SDL_GetError());
            exit(-1);
        }

        shared_ptr<Mix_Chunk> ptr(sound, [](Mix_Chunk* c){ Mix_FreeChunk(c); });
        m_sound_table.emplace(file, ptr);
    }

    return m_sound_table[file];
}

void Resources::clear_sounds(){
    for(auto it = m_sound_table.begin(); it != m_sound_table.end(); ++it){
        if(it->second.unique()){
            m_sound_table.erase(it);
        }
    }
}

shared_ptr<TTF_Font> Resources::get_font(string file, int font_size){
    const string font_key = file + to_string(font_size);

    if(m_font_table.find(font_key) == m_font_table.end()){
        TTF_Font* font = TTF_OpenFont(file.c_str(), font_size);

        if(font == nullptr){
            printf("TTF_OpenFont error: %s\n", SDL_GetError());
            exit(-1);
        }

        shared_ptr<TTF_Font> ptr(font, [](TTF_Font* f){ TTF_CloseFont(f); });
        m_font_table.emplace(font_key, ptr);
    }

    return m_font_table[font_key];
}

void Resources::clear_fonts(){
    for(auto it = m_font_table.begin(); it != m_font_table.end(); ++it){
        if(it->second.unique()){
            m_font_table.erase(it);
        }
    }
}
