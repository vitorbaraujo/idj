#include "State.h"
#include "Sprite.h"

State::State() : m_requested_quit(false), m_bg(new Sprite()) {
}

bool State::quit_requested(){
    return m_requested_quit; 
}

void State::update(float dt){
    if(SDL_QuitRequested()){
        m_requested_quit = true;
    }
}

void State::render(){
    m_bg->render(0, 0);
}

void State::load_assets(){
    m_bg->open("res/img/ocean.jpg");
}
