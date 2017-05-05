#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"

#include <iostream>

using std::string;

class Sprite {
    private:
        SDL_Texture* m_texture;
        int m_width, m_height;
        SDL_Rect* m_clip_rect;
        double m_scale_x, m_scale_y;

    public:
        Sprite();
        Sprite(string filename);
        ~Sprite();

        void open(string filename);
        void set_clip(int x, int y, int w, int h);
        void render(int x, int y, double angle = 0);
        int get_width();
        int get_height();
        bool is_open();
        void set_scale_x(double scale);
        void set_scale_y(double scale);
};

#endif
