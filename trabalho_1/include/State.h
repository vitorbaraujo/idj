#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>

class Sprite;

class State {
    private:
        Sprite* m_bg;
        bool m_requested_quit;

    public:
        State();

        bool quit_requested();
        void update(float dt);
        void render();
        void load_assets();
};

#endif
