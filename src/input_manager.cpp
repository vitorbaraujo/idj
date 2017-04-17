#include "input_manager.h"

#include <cstring>

InputManager::InputManager(){
    memset(m_mouse_state, 0, sizeof m_mouse_state);
    memset(m_mouse_update, 0, sizeof m_mouse_update);
    m_quit_requested = false;
    m_update_counter = 0;
    m_mouse_x = 0;
    m_mouse_y = 0;
}

InputManager::~InputManager(){

}

InputManager& InputManager::get_instance(){
    static InputManager input_manager;

    return input_manager;
}

void InputManager::update(){
    SDL_Event event;
    m_quit_requested = false;

    SDL_GetMouseState(&m_mouse_x, &m_mouse_y);

    m_update_counter++;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            m_quit_requested = true;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN){
            m_mouse_state[event.button.button] = true;
            m_mouse_update[event.button.button] = m_update_counter;
        }

        if(event.type == SDL_MOUSEBUTTONUP){
            m_mouse_state[event.button.button] = false;
            m_mouse_update[event.button.button] = m_update_counter;
        }

        if(event.type == SDL_KEYDOWN && event.key.repeat != 1){
            m_key_state[event.key.keysym.sym] = true;
            m_key_update[event.key.keysym.sym] = m_update_counter;
        }

        if(event.type == SDL_KEYUP){
            m_key_state[event.key.keysym.sym] = false;
            m_key_update[event.key.keysym.sym] = m_update_counter;
        }
    }
}

bool InputManager::on_key_press(int key){
    return m_key_update[key] == m_update_counter && is_key_down(key);
}

bool InputManager::on_key_release(int key){
    return m_key_update[key] == m_update_counter && !is_key_down(key);
}

bool InputManager::is_key_down(int key){
    return m_key_state[key];   
}

bool InputManager::on_mouse_press(int button){
    return m_mouse_update[button] == m_update_counter && is_mouse_down(button);
}

bool InputManager::on_mouse_release(int button){
    return m_mouse_update[button] == m_update_counter && !is_mouse_down(button);
}

bool InputManager::is_mouse_down(int button){
    return m_mouse_state[button];
}

int InputManager::get_mouse_x(){
    return m_mouse_x;
}

int InputManager::get_mouse_y(){
    return m_mouse_y;
}

bool InputManager::quit_requested(){
    return m_quit_requested;
}
