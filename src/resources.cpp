#include "resources.h"
#include "game.h"

unordered_map<string, shared_ptr<SDL_Texture> > Resources::image_table;

shared_ptr<SDL_Texture> Resources::get_image(string file){
    auto it = image_table.find(file);

    if(it != image_table.end())
        return it->second;

    SDL_Texture* texture = IMG_LoadTexture(Game::get_instance().get_renderer(), file.c_str());

    if(!texture){
        return nullptr;
    }

    shared_ptr<SDL_Texture> ptr(texture, [](SDL_Texture *t){ SDL_DestroyTexture(t); });
    image_table.emplace(file, ptr);

    return ptr;
}

void Resources::clear_images(){
    for(auto it = image_table.begin(); it != image_table.end(); ++it){
        if(it->second.unique()){
            SDL_DestroyTexture(it->second.get());
            image_table.erase(it);
        }
    }

    image_table.clear();
}
