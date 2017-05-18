#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stack>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "state.h"

using std::string;
using std::stack;

class Game {
    private:
        int m_frame_start;
        double m_dt;

        static Game* m_instance;

        State* m_stored_state;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        stack< unique_ptr<State> > m_state_stack;

        void calculate_delta_time();

    public:
        Game(string title, int width, int height);
        ~Game();

        static Game& get_instance();
        SDL_Renderer* get_renderer();

        State& get_current_state();
        void push(State* state);
        void run();
        double get_delta_time();
};

#endif
