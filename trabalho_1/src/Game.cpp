#include "Game.h"

Game* Game::m_instance = nullptr;

Game::Game(string title, int width, int height){
    if(m_instance == nullptr){
        m_instance = this; 
    }

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
        printf("SDL_Init error: %s\n", SDL_GetError());
        return;
    }

    int image_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

    if(IMG_Init(image_flags) != image_flags){
        printf("IMG_Init error: %s\n", IMG_GetError());
        return;
    }

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if(m_window == nullptr){
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return;
    }

    // SDL_RENDERER_ACCELERATED to require use of OpenGL or Direct3D
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if(m_renderer == nullptr){
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
		return;
    }

    m_state = new State();
}

Game::~Game(){
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::run(){
    while(!m_state->quit_requested()){
        m_state->update();
        m_state->render();

        SDL_RenderPresent(m_renderer);
        SDL_Delay(33);
    }
}

SDL_Renderer* Game::get_renderer(){
    return m_renderer;
}

State& Game::get_state(){
    return *m_state;
}

Game& Game::get_instance(){
    return *m_instance;
}
