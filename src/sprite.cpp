#include "sprite.h"
#include "game.h"
#include "resources.h"

Sprite::Sprite() : m_texture(nullptr) {
    m_scale_x = 1;
    m_scale_y = 1;
}

Sprite::Sprite(string filename) : m_texture(nullptr){
    open(filename);
    m_scale_x = 1;
    m_scale_y = 1;
}

Sprite::~Sprite(){
}

void Sprite::open(string filename){
    m_texture = Resources::get_image(filename);

    if(m_texture == nullptr){
        printf("IMG_LoadTexture error: %s\n", SDL_GetError());
    }

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

    set_clip(0, 0, m_width, m_height);
}

void Sprite::set_clip(int x, int y, int w, int h){
    m_clip_rect = new SDL_Rect { x, y, w, h };    
}

void Sprite::render(int x, int y, double angle){
    SDL_Rect* dest_rect = new SDL_Rect { x, y, m_clip_rect->w * m_scale_x, m_clip_rect->h * m_scale_y };

    SDL_RenderCopyEx(Game::get_instance().get_renderer(), m_texture, m_clip_rect, dest_rect, angle, nullptr, SDL_FLIP_NONE);
}

int Sprite::get_width(){
    return m_width * m_scale_x;
}

int Sprite::get_height(){
    return m_height * m_scale_y;
}

bool Sprite::is_open(){
    if(m_texture) return true;

    return false;
}

void Sprite::set_scale_x(double scale){
    m_scale_x = scale;
}

void Sprite::set_scale_y(double scale){
    m_scale_y = scale;
}
