#include "text.h"
#include "game.h"
#include "resources.h"

Text::Text() {

}

Text::Text(string font_file, int font_size, Text::TextStyle style, string text, SDL_Color color, int x, int y){
    m_font = Resources::get_font(font_file, font_size);
    m_texture = nullptr;
    m_text = text;
    m_style = style;
    m_font_size = font_size;
    m_color = color;
    m_box = Rectangle(x, y);

    if(m_font){
        remake_texture();
    }
}

Text::~Text(){
    if(m_texture){
        SDL_DestroyTexture(m_texture);
    }
}

void Text::render(int camera_x, int camera_y){
    if(m_texture){
        SDL_Rect src_rect = { 0, 0, (int)m_box.get_w(), (int)m_box.get_h() };
        SDL_Rect dest_rect = { (int)m_box.get_x() + camera_x, (int)m_box.get_y() + camera_y, (int)m_box.get_w(), (int)m_box.get_h() };

        SDL_RenderCopy(Game::get_instance().get_renderer(), m_texture, &src_rect, &dest_rect);
    }
}

void Text::set_pos(int x, int y, bool center_x, bool center_y){
    if(center_x) x -= m_box.get_w() / 2;
    if(center_y) y -= m_box.get_h() / 2;

    m_box.set_x(x);
    m_box.set_y(y);
}

void Text::set_text(string text){
    m_text = text;
    remake_texture();
}

void Text::set_color(SDL_Color color){
    m_color = color;
    remake_texture();
}

void Text::set_style(Text::TextStyle style){
    m_style = style;
    remake_texture();
}

void Text::set_font_size(int font_size){
    m_font_size = font_size;
    remake_texture();
}

void Text::remake_texture(){
    if(m_texture){
        SDL_DestroyTexture(m_texture);
    }

    SDL_Surface* surface = nullptr;

    if(m_style == Text::TextStyle::SOLID){
        surface = TTF_RenderText_Solid(m_font.get(), m_text.c_str(), m_color);
    }
    else if(m_style == Text::TextStyle::SHADED){
        SDL_Color black = { 0, 0, 0, 0 };
        surface = TTF_RenderText_Shaded(m_font.get(), m_text.c_str(), m_color, black);
    }
    else if(m_style == Text::TextStyle::BLENDED){
        surface = TTF_RenderText_Blended(m_font.get(), m_text.c_str(), m_color);
    }

    m_texture = SDL_CreateTextureFromSurface(Game::get_instance().get_renderer(), surface);

    int width, height;

    SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);

    m_box.set_w(width);
    m_box.set_h(height);

    SDL_FreeSurface(surface);
}
