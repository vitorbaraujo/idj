#include "State.h"

State::State() : requested_quit(false) {
    // instantiate bg
}

State::bool quit_requested(){
    return requested_quit; 
}

State::void update(float dt){
    if(SDL_QuitRequested()){
        requested_quit = true;
    }
}

State::void render(){
    // render bg
    // open bg with img/ocean.png
    
}
