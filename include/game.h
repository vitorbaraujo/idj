#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "state.h"

using std::string;

class Game {
    private:
        static Game* m_instance;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        State* m_state;
        int m_frame_start;
        double dt;

        void calculate_delta_time();

    public:
        Game(string title, int width, int height);
        ~Game();

        static Game& get_instance();
        SDL_Renderer* get_renderer();
        State& get_state();
        void run();
        double get_delta_time();
};

#endif
