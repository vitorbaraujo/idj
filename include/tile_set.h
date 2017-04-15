#ifndef TILE_SET_H
#define TILE_SET_H

#include "sprite.h"

#include <iostream>

using std::string;

class TileSet {
    private:
        Sprite m_tile_set;
        int m_rows, m_columns;
        int m_tile_width, m_tile_height;

    public:
        TileSet(int width, int height, string filename);
        void render(int index, double x, double y);
        int get_tile_width();
        int get_tile_height();
};

#endif