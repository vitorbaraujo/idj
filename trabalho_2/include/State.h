#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <memory> // unique_ptr

#include <SDL2/SDL.h>

#include "GameObject.h"

using std::vector;
using std::unique_ptr;

class Sprite;

class State {
    private:
        Sprite* m_bg;
        bool m_requested_quit;
        vector< unique_ptr<GameObject> > m_objects_array;

        void input();
        void add_object(float mouse_x, float mouse_y);

    public:
        State();
        ~State();

        bool quit_requested();
        void update(float dt = 0);
        void render();
        void load_assets();
};

#endif
