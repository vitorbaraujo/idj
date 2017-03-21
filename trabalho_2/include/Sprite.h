#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <iostream>

using std::string;

class Sprite {
    private:
        SDL_Texture* m_texture;
        int m_width, m_height;
        SDL_Rect* m_clip_rect;

    public:
        Sprite();
        Sprite(string filename);
        ~Sprite();

        void open(string filename);
        void set_clip(int x, int y, int w, int h);
        void render(int x, int y);
        int get_width();
        int get_height();
        bool is_open();
};

#endif
