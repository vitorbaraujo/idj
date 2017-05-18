#include "stage_state.h"
#include "alien.h"
#include "camera.h"
#include "collision.h"
#include "input_manager.h"
#include "penguins.h"
#include "rectangle.h"
#include "sprite.h"
#include "vector.h"
#include "title_state.h"
#include "game.h"

StageState::StageState() {
    m_bg = Sprite("img/ocean.jpg");
    m_tile_set = new TileSet(64, 64, "img/tileset.png");
    m_tile_map = new TileMap("map/tileMap.txt", m_tile_set);

    Alien* alien = new Alien(412, 200, 6);
    Penguins* penguins = new Penguins(704, 640);

    add_object(alien);
    add_object(penguins);

    Camera::follow(penguins);
}

StageState::~StageState() {
    delete(m_tile_set);
}

void StageState::update(double dt){
    InputManager input_manager = InputManager::get_instance();

    Camera::update(dt);

    if(input_manager.quit_requested()){
        m_quit_requested = true;
    }

    if(input_manager.is_key_down(ESCAPE_KEY)){
        // go back to title screen
        TitleState* title_state = new TitleState();
        Game::get_instance().push(title_state);

        m_pop_requested = true;
    }

    update_array(dt);

    check_collision();
}

void StageState::render(){
    m_bg.render(0, 0);
    m_tile_map->render_layer(0, Camera::m_pos);

    render_array();

    m_tile_map->render_layer(1, Camera::m_pos);
}

void StageState::pause(){
}

void StageState::resume(){
}

void StageState::check_collision(){
    for(unsigned int it = 0; it < m_object_array.size(); ++it){
        for(unsigned int it2 = it + 1; it2 < m_object_array.size(); ++it2){
            Rectangle it_box = m_object_array[it]->m_box;
            Rectangle it2_box = m_object_array[it2]->m_box;

            it_box.set_x(it_box.draw_x() + Camera::m_pos[0].get_x());
            it_box.set_y(it_box.draw_y() + Camera::m_pos[0].get_y());

            it2_box.set_x(it2_box.draw_x() + Camera::m_pos[0].get_x());
            it2_box.set_y(it2_box.draw_y() + Camera::m_pos[0].get_y());

            double it_angle = m_object_array[it]->m_rotation;
            double it2_angle = m_object_array[it2]->m_rotation;

            if(Collision::is_colliding(it_box, it2_box, it_angle, it2_angle)){
                m_object_array[it]->notify_collision(*m_object_array[it2]);
                m_object_array[it2]->notify_collision(*m_object_array[it]);
            }
        }
    }
}
