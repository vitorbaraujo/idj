#include "tile_map.h"

TileMap::TileMap(string filename, TileSet* tile_set){
    load(filename);
    // set tile_set
}

void TileMap::load(string filename){

}

void TileMap::set_tile_set(TileSet* tile_set){

}

int& TileMap::at(int x, int y, int z){

}

void TileMap::render(int camera_x, int camera_y){

}

void TileMap::render_layer(int layer, int camera_x, int camera_y){

}

int TileMap::get_width(){

}

int TileMap::get_height(){

}

int TileMap::get_depth(){

}