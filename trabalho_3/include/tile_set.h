#ifndef TILE_SET_H
#define TILE_SET_H

#include "sprite.h"

#include <iostream>

using std::string;

class TileSet {
    private:
        int m_rows, m_columns;
        int m_tile_width, m_tile_height;
        Sprite m_tile_set;

    public:
        TileSet(int tile_width, int tile_height, string filename);

        void render(unsigned index, double x, double y);
        int get_tile_width();
        int get_tile_height();
};

#endif