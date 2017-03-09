#include "Sprite.h"

Sprite::Sprite() : texture(nullptr) {

}

Sprite::Sprite(string filename) : texture(nullptr){
    open(filename);
}

Sprite::~Sprite(){
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

Sprite::void open(string filename){
    if(texture){
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(/* get game renderer */, filename);

    if(texture == nullptr){
        printf("IMG_LoadTexture error: %s\n", SDL_GetError());
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

Sprite::void set_clip(int x, int y, int w, int h){
    clip_rect = new SDL_Rect(x, y, w, h);    
}

Sprite::void render(int x, int y){
    SDL_Rect * dest_rect = new SDL_Rect(x, y, clip_rect.w, clip_rect.h);

    SDL_RenderCopy(/* get game renderer */, texture, clip_rect, dest_rect);
}

Sprite::int get_width(){
    return width;
}

Sprite::int get_height(){
    return height;
}

Sprite::bool is_open(){
    if(texture) return true;

    return false;
}
