#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <iostream>
#include <vector>
#include <memory> // unique_ptr

#include "SDL2/SDL.h"

#include "game_object.h"
#include "tile_set.h"
#include "tile_map.h"
#include "state.h"
#include "music.h"
#include "resources.h"

using std::vector;
using std::unique_ptr;

class StageState : public State {

    private:
        Sprite m_bg;
        TileSet* m_tile_set;
        TileMap* m_tile_map;
        Music m_music;

    public:
        StageState();
        ~StageState();

        void update(double dt);
        void render();
        void pause();
        void resume();
        void load_assets();

        void check_collision();
};

#endif
