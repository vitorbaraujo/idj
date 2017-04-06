#include "resources.h"
#include "game.h"

unordered_map<string, SDL_Texture* > Resources::image_table;

SDL_Texture* Resources::get_image(string file){
    auto it = image_table.find(file);

    if(it != image_table.end())
        return it->second;

    SDL_Texture* texture = IMG_LoadTexture(Game::get_instance().get_renderer(), file.c_str());

    image_table.emplace(file, texture);

    return texture;
}

void Resources::clear_images(){
    for(auto it = image_table.begin(); it != image_table.end(); ++it){
        SDL_DestroyTexture(it->second);
    }

    image_table.clear();
}