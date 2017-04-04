#include "tile_map.h"

TileMap::TileMap(string file, TileSet* tile_set) {
    load(file);
    set_tile_set(tile_set);
}

TileMap::~TileMap(){
    delete(m_tile_set);
}

void TileMap::load(string file){
    fstream f(file, f.in);
    string s;
    int tile;

    if(not f.is_open()){
        printf("Erro na abertura do arquivo\n");
        return;
    }

    getline(f, s);
    stringstream ss;
    ss << s;

    ss >> m_map_width;
    ss.ignore(2, ',');

    ss >> m_map_height;
    ss.ignore(2, ',');

    ss >> m_map_depth;
    ss.ignore(2, ',');

    while(getline(f, s)){
        ss.clear();
        ss << s;

        while(ss >> tile){
            m_tile_matrix.emplace_back(tile - 1);
            ss.ignore(2, ',');
        }
    }
}

void TileMap::set_tile_set(TileSet* tile_set){
    m_tile_set = tile_set;
}

int& TileMap::at(int x, int y, int z){
    int index = (z * m_map_width * m_map_height) + (y * m_map_width) + x;

    return m_tile_matrix[index];
}

void TileMap::render(int camera_x, int camera_y){
    for(int layer = 0; layer < m_map_depth; ++layer) {
        render_layer(layer); // fix camera_x and camera_y
    }
}

void TileMap::render_layer(int layer, int camera_x, int camera_y){
    for(int x = 0; x < m_map_width; ++x){
        for(int y = 0; y < m_map_height; ++y){
            int to_x = x * m_tile_set->get_tile_width();
            int to_y = y * m_tile_set->get_tile_height();

            m_tile_set->render(at(x, y ,layer), to_x, to_y);
        }
    }
}

int TileMap::get_width(){
    return m_map_width;
}

int TileMap::get_height(){
    return m_map_height;
}

int TileMap::get_depth(){
    return m_map_depth;
}

