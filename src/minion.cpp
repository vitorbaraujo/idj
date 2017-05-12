#include "input_manager.h"
#include "minion.h"
#include "camera.h"
#include "bullet.h"
#include "state.h"
#include "game.h"

#define OFFSET 200
#define SPEED_FACTOR 100

Minion::Minion(GameObject *minion_center, double arc_offset, double rotation){
    m_rotation = rotation;
    m_arc = arc_offset;
    m_center = minion_center;
    m_sp = Sprite("img/minion.png");

    m_box = Rectangle(minion_center->m_box.get_x(), minion_center->m_box.get_y(), m_sp.get_width(), m_sp.get_height());

    // set scale between 1.0 and 1.5
    double random_scale = 1.0 + double(rand()) / double(RAND_MAX/(0.5));
    m_sp.set_scale_x(random_scale);
    m_sp.set_scale_y(random_scale);
}

void Minion::update(double dt){
    m_arc += SPEED_FACTOR * dt;
    if(m_arc > 360) m_arc = 0;
    double angle = m_arc * acos(-1) / 180.0;

    m_rotation = m_arc + 90;

    Vector pos(m_center->m_box);
    pos.translate(OFFSET, 0);

    pos.rotate(angle, m_center->m_box);

    m_box = Rectangle(pos.get_x(), pos.get_y(), m_sp.get_height(), m_sp.get_width());
}

void Minion::render(){
    m_sp.render(m_box.draw_x() + Camera::m_pos[0].get_x(), m_box.draw_y() + Camera::m_pos[0].get_y(), m_rotation);
}

bool Minion::is_dead(){
    return false;
}

void Minion::shoot(Vector pos){
    InputManager input_manager = InputManager::get_instance();

    double angle = atan2(pos.get_y() - m_box.get_y(), pos.get_x() - m_box.get_x());
    double speed = 100;
    double max_distance = 20000;

    Bullet *bullet = new Bullet(m_box.get_x(), m_box.get_y(), angle, speed, max_distance, "img/minionbullet2.png", 1, 3);

    State *state = Game::get_instance().get_state();
    state->add_object(bullet);
}
