#include "tile_set.h"

TileSet::TileSet(int width, int height, string filename) : m_tile_width(width), m_tile_height(height) {
    m_tile_set.open(filename);
    m_rows = m_tile_set.get_height() / height;
    m_columns = m_tile_set.get_width() / width;
}

void TileSet::render(int index, double x, double y) {
    if(index >= m_rows * m_columns){
        printf("Invalid index\n");
        return;
    }

    m_tile_set.set_clip((int)x, (int)y, m_tile_width, m_tile_height);
    m_tile_set.render((int)x, (int)y);
}

int TileSet::get_tile_width() {
    return m_tile_width;
}

int TileSet::get_tile_height() {
    return m_tile_height;
}