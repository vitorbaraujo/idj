#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include <iostream>
#include <memory>

#include "rectangle.h"

using std::string;
using std::shared_ptr;

class Text {
    public:
        enum TextStyle { SOLID, SHADED, BLENDED };

    private:
        shared_ptr<TTF_Font> m_font;
        SDL_Texture* m_texture;
        string m_text;
        TextStyle m_style;
        int m_font_size;
        SDL_Color m_color;
        Rectangle m_box;

        void remake_texture();

    public:
        static constexpr SDL_Color BLACK = { 0, 0, 0, 0 };
        static constexpr SDL_Color WHITE = { 255, 255, 255, 255 };

        Text(string font_file, int font_size, TextStyle style, string text, SDL_Color color = BLACK, int x = 0, int y = 0);
        Text();
        ~Text();

        void render(int camera_x = 0, int camera_y = 0);
        void set_pos(int x, int y, bool center_x = false, bool center_y = false);
        void set_text(string text);
        void set_color(SDL_Color color);
        void set_style(TextStyle style);
        void set_font_size(int font_size);
};

#endif
