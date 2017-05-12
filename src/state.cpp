#include "state.h"
#include "sprite.h"
#include "vector.h"
#include "input_manager.h"
#include "camera.h"
#include "alien.h"

State::State() : m_requested_quit(false) {
    m_bg = new Sprite();
    m_tile_set = new TileSet(64, 64, "img/tileset.png");
    m_tile_map = new TileMap("map/tileMap.txt", m_tile_set);

    Alien* alien = new Alien(512, 300, 6);
    m_objects_array.emplace_back(alien);
}

State::~State() {
    delete(m_bg);

    m_objects_array.clear();
}

bool State::quit_requested(){
    return m_requested_quit; 
}

void State::update(double dt){
    InputManager input_manager = InputManager::get_instance();

    Camera::update(dt);

    if(input_manager.is_key_down(ESCAPE_KEY) || input_manager.quit_requested()){
        m_requested_quit = true;
    }

    for(unsigned int it = 0; it < m_objects_array.size(); ++it){
        m_objects_array[it]->update(dt);

        if(m_objects_array[it]->is_dead()){
            m_objects_array.erase(m_objects_array.begin() + it);
            break;
        }
    }
}

void State::render(){
    m_bg->render(0, 0);
    m_tile_map->render_layer(0, Camera::m_pos);

    for(auto& object : m_objects_array) {
        object->render();
    }

    m_tile_map->render_layer(1, Camera::m_pos);
}

void State::load_assets(){
    m_bg->open("img/ocean.jpg");
}

void State::add_object(GameObject *ptr) {
    m_objects_array.emplace_back(ptr);
}
