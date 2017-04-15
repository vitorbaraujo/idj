#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define SPACE_KEY           SDLK_SPACE

#include "SDL2/SDL.h"

#include <unordered_map>

using std::unordered_map;

class InputManager {
    private:
        bool m_mouse_state[6];
        int m_mouse_update[6];

        unordered_map<int, bool> m_key_state;
        unordered_map<int, int> m_key_update;

        bool m_quit_requested;
        int m_update_counter;
        int m_mouse_x, m_mouse_y;

    public:
        InputManager();
        ~InputManager();

        static InputManager& get_instance();

        void update();

        bool key_press(int key);
        bool key_release(int key);
        bool is_key_down(int key);

        bool mouse_press(int button);
        bool mouse_release(int button);
        bool is_mouse_down(int button);

        int get_mouse_x();
        int get_mouse_y();

        bool quit_requested();
};

#endif