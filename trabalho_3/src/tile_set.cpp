#include "tile_set.h"

TileSet::TileSet(int tile_width, int tile_height, string filename) : m_tile_width(tile_width), m_tile_height(tile_height) {
    m_tile_set = Sprite(filename);
    m_rows = m_tile_set.get_width() / m_tile_width;
    m_columns = m_tile_set.get_height() / m_tile_height;

    printf("rows: %d\n", m_rows);
    printf("columns: %d\n", m_columns);
}

void TileSet::render(unsigned index, double x, double y){
    // check index
    m_tile_set.set_clip(x, y, m_tile_width, m_tile_height);
}

int TileSet::get_tile_width(){
    return m_tile_width;
}

int TileSet::get_tile_height(){
    return m_tile_height;
}