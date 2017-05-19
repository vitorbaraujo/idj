#include "sprite.h"
#include "game.h"
#include "resources.h"

Sprite::Sprite() : m_texture(nullptr) {
    m_scale_x = 1;
    m_scale_y = 1;
    m_frame_count = 1;
    m_frame_time = 1;
    m_current_frame = 0;
    m_time_elapsed = 0;
}

Sprite::Sprite(string filename, int frame_count, double frame_time){
    m_texture = nullptr;
    m_scale_x = 1;
    m_scale_y = 1;
    m_frame_count = frame_count;
    m_frame_time = frame_time;
    m_current_frame = 0;
    m_time_elapsed = 0;

    open(filename);
}

Sprite::~Sprite(){
}

void Sprite::open(string filename){
    m_texture = Resources::get_image(filename);

    if(m_texture == nullptr){
        printf("IMG_LoadTexture error: %s\n", SDL_GetError());
    }

    SDL_QueryTexture(m_texture.get(), nullptr, nullptr, &m_width, &m_height);
    m_width /= m_frame_count;

    set_clip(0, 0, m_width, m_height);
}

void Sprite::set_clip(int x, int y, int w, int h){
    m_clip_rect = new SDL_Rect { x, y, w, h };
}

void Sprite::render(int x, int y, double angle){
    SDL_Rect* dest_rect = new SDL_Rect { x, y, m_clip_rect->w * (int) m_scale_x, m_clip_rect->h * (int) m_scale_y };

    SDL_RenderCopyEx(Game::get_instance().get_renderer(), m_texture.get(), m_clip_rect, dest_rect, angle, nullptr, SDL_FLIP_NONE);
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

void Sprite::update(double dt){
    m_time_elapsed += dt;

    if(m_time_elapsed > m_frame_time){
        m_time_elapsed = 0;
        set_frame((m_current_frame + 1) % m_frame_count);
    }

}

void Sprite::set_frame(int frame){
    m_current_frame = frame;

    set_clip(m_width * m_current_frame, 0, m_width, m_height);
}

void Sprite::set_frame_count(int frame_count){
    m_frame_count = frame_count;
}

void Sprite::set_frame_time(double frame_time){
    m_frame_time = frame_time;
}
