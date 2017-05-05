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

    Vector alien_center(Vector(minion_center->m_box));
    alien_center.increment_x(m_center->m_box.get_w() / 2);
    alien_center.increment_y(m_center->m_box.get_h() / 2);

    m_box = Rectangle(alien_center.get_x(), alien_center.get_y(), m_sp.get_width(), m_sp.get_height());

    // set scale between 1.0 and 1.5
    double random_scale = 1.0 + float(rand()) / float(RAND_MAX/(0.5));
    m_sp.set_scale_x(random_scale);
    m_sp.set_scale_y(random_scale);
}

void Minion::update(double dt){
    m_arc += SPEED_FACTOR * dt;
    if(m_arc > 360) m_arc = 0;
    double angle = m_arc * acos(-1) / 180.0;

    m_rotation = m_arc;

    Vector center(m_center->m_box.get_x() + m_center->m_box.get_w() / 2, m_center->m_box.get_y() + m_center->m_box.get_h() / 2);
    Vector pos(center);
    pos.translate(OFFSET, 0);

    pos.rotate(angle, center);

    m_box = Rectangle(pos.get_x(), pos.get_y(), m_sp.get_height(), m_sp.get_width());
}

void Minion::render(){
    m_sp.render(m_box.get_x() + Camera::m_pos[0].get_x(), m_box.get_y() + Camera::m_pos[0].get_y(), m_rotation);
}

bool Minion::is_dead(){
    return false;
}

void Minion::shoot(Vector pos){
    InputManager input_manager = InputManager::get_instance();

    double angle = atan2(m_box.get_y() - pos.get_y(), m_box.get_x() - pos.get_x());
    double speed = 100;
    double max_distance = 8000;

    Bullet *bullet = new Bullet(m_box.get_x(), m_box.get_y(), angle, speed, max_distance, "img/minionbullet1.png");

    State *state = Game::get_instance().get_state();
    state->add_object(bullet);
}
