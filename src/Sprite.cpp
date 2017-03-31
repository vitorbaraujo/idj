#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : m_texture(nullptr) {

}

Sprite::Sprite(string filename) : m_texture(nullptr){
    open(filename);
}

Sprite::~Sprite(){
    if(m_texture){
        SDL_DestroyTexture(m_texture);
    }
}

void Sprite::open(string filename){
    if(m_texture){
        SDL_DestroyTexture(m_texture);
    }

    m_texture = IMG_LoadTexture(Game::get_instance().get_renderer(), filename.c_str());

    if(m_texture == nullptr){
        printf("IMG_LoadTexture error: %s\n", SDL_GetError());
    }

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

    set_clip(0, 0, m_width, m_height);
}

void Sprite::set_clip(int x, int y, int w, int h){
    m_clip_rect = new SDL_Rect { x, y, w, h };    
}

void Sprite::render(int x, int y){
    SDL_Rect* dest_rect = new SDL_Rect { x, y, m_clip_rect->w, m_clip_rect->h };

    SDL_RenderCopy(Game::get_instance().get_renderer(), m_texture, m_clip_rect, dest_rect);
}

int Sprite::get_width(){
    return m_width;
}

int Sprite::get_height(){
    return m_height;
}

bool Sprite::is_open(){
    if(m_texture) return true;

    return false;
}
