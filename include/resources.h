#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL_image.h"

#include <iostream>
#include <unordered_map>

using std::string;
using std::unordered_map;

class Resources {
    private:
        static unordered_map<string, SDL_Texture* > image_table;

    public:
        static SDL_Texture* get_image(string file);
        static void clear_images();

};

#endif