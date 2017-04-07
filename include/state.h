#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <memory> // unique_ptr

#include "SDL2/SDL.h"

#include "game_object.h"
#include "tile_set.h"
#include "tile_map.h"

using std::vector;
using std::unique_ptr;

class Sprite;

class State {
    private:
        Sprite* m_bg;
        TileSet* m_tile_set;
        TileMap* m_tile_map;
        bool m_requested_quit;
        vector< unique_ptr<GameObject> > m_objects_array;

        void input();
        void add_object(int mouse_x, int mouse_y);

    public:
        State();
        ~State();

        bool quit_requested();
        void update(float dt = 0);
        void render();
        void load_assets();
};

#endif
