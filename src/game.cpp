#include "game.h"
#include "resources.h"
#include "input_manager.h"

Game* Game::m_instance = nullptr;

Game::Game(string title, int width, int height){
    m_dt = 0;
    m_frame_start = 0;

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

    m_stored_state = nullptr;
}

Game::~Game(){
    if(m_stored_state)
        delete(m_stored_state);

    while(!m_state_stack.empty()){
        // should delete something?
        m_state_stack.pop();
    }

    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

Game& Game::get_instance(){
    return *m_instance;
}

SDL_Renderer* Game::get_renderer(){
    return m_renderer;
}

State& Game::get_current_state(){
    return *(m_state_stack.top());
}

void Game::push(State* state){
    m_stored_state = state;
}

void Game::run(){
    // if there is no initial state, end the game
    if(!m_stored_state){
        return;
    }

    m_state_stack.emplace(m_stored_state);
    m_stored_state = nullptr;

    while(!m_state_stack.empty() && !m_state_stack.top()->quit_requested()){
        calculate_delta_time();
        InputManager::get_instance().update();
        m_state_stack.top()->update(get_delta_time());
        m_state_stack.top()->render();

        SDL_RenderPresent(m_renderer);

        if(m_state_stack.top()->pop_requested()){
            m_state_stack.pop();
            // check if stack not empty
            if(!m_state_stack.empty()) continue;

            m_state_stack.top()->resume();

            if(!m_stored_state){
                m_state_stack.top()->pause();
                m_state_stack.emplace(m_stored_state);
                m_stored_state = nullptr;
            }
        }

        SDL_Delay(33);
    }

    Resources::clear_images();
}

double Game::get_delta_time(){
    return m_dt;
}

void Game::calculate_delta_time(){
    unsigned int current_time = SDL_GetTicks();
    m_dt = (current_time - m_frame_start) / 1000.0;
    m_frame_start = current_time;
}
