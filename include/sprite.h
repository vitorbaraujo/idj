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
        int m_frame_count, m_current_frame;
        double m_time_elapsed, m_frame_time;

    public:
        Sprite();
        Sprite(string filename, int frame_count =  1, double frame_time = 1);
        ~Sprite();

        void open(string filename);
        void set_clip(int x, int y, int w, int h);
        void render(int x, int y, double angle = 0);
        int get_width();
        int get_height();
        bool is_open();
        void set_scale_x(double scale);
        void set_scale_y(double scale);
        void update(double dt);
        void set_frame(int frame);
        void set_frame_count(int frame_count);
        void set_frame_time(double frame_time);

};

#endif
