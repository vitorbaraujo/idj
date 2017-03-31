#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "State.h"

using std::string;

class Game {
    private:
        static Game* m_instance;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        State* m_state;

    public:
        Game(string title, int width, int height);
        ~Game();

        void run();
        SDL_Renderer* get_renderer();
        State& get_state();
        static Game& get_instance();
};

#endif
