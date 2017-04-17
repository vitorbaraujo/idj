#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "tile_set.h"
#include "vector.h"

#include <vector>
#include <fstream>
#include <sstream>

using std::vector;
using std::string;
using std::fstream;
using std::stringstream;

class TileMap {
    private:
        vector<int> m_tile_matrix;
        TileSet* m_tile_set;
        int m_map_width, m_map_height, m_map_depth;

    public:
        TileMap(string file, TileSet* tile_set);
        ~TileMap();
        void load(string file);
        void set_tile_set(TileSet* tile_set);
        int& at(int x, int y, int z = 0);
        void render(Vector *cameras);
        void render_layer(int layer, Vector *cameras);

        int get_width();
        int get_height();
        int get_depth();
};

#endif