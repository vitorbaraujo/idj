#include "state.h"
#include "sprite.h"
#include "vector.h"
#include "input_manager.h"
#include "camera.h"
#include "alien.h"
#include "penguins.h"
#include "collision.h"

State::State() : m_requested_quit(false) {
    m_bg = new Sprite();
    m_tile_set = new TileSet(64, 64, "img/tileset.png");
    m_tile_map = new TileMap("map/tileMap.txt", m_tile_set);

    Alien* alien = new Alien(512, 300, 6);
    m_objects_array.emplace_back(alien);

    Penguins* penguins = new Penguins(704, 640);
    m_objects_array.emplace_back(penguins);

    Camera::follow(penguins);
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

    for(unsigned int it = 0; it < m_objects_array.size(); ++it){
        for(unsigned int it2 = it + 1; it2 < m_objects_array.size(); ++it2){
            Rectangle it_box = m_objects_array[it]->m_box;
            Rectangle it2_box = m_objects_array[it2]->m_box;

            it_box.set_x(it_box.draw_x() + Camera::m_pos[0].get_x());
            it_box.set_y(it_box.draw_y() + Camera::m_pos[0].get_y());

            it2_box.set_x(it2_box.draw_x() + Camera::m_pos[0].get_x());
            it2_box.set_y(it2_box.draw_y() + Camera::m_pos[0].get_y());

            double it_angle = m_objects_array[it]->m_rotation;
            double it2_angle = m_objects_array[it2]->m_rotation;

            if(Collision::is_colliding(it_box, it2_box, it_angle, it2_angle)){
                m_objects_array[it]->notify_collision(*m_objects_array[it2]);
                m_objects_array[it2]->notify_collision(*m_objects_array[it]);
            }
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