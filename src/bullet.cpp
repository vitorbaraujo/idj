#include "bullet.h"
#include "camera.h"

Bullet::Bullet(double x, double y, double angle, double speed, double max_distance, string sprite, double frame_time, int frame_count, bool targets_player) {
    m_sp = Sprite(sprite, frame_count, frame_time);
    m_box = Rectangle(x, y, m_sp.get_width(), m_sp.get_height());
    m_speed = Vector(cos(angle) * speed, sin(angle) * speed);
    m_distance_left = max_distance;
    m_rotation = Utils::to_deg(angle);
    m_targets_player = targets_player;
}

void Bullet::update(double dt) {
    m_sp.update(dt);

    m_box.set_x(m_box.get_x() + m_speed.get_x() * dt);
    m_box.set_y(m_box.get_y() + m_speed.get_y() * dt);

    double dist = hypot(m_speed.get_x(), m_speed.get_y());

    m_distance_left -= dist;
}

void Bullet::render() {
    m_sp.render(m_box.draw_x() + Camera::m_pos[0].get_x(), m_box.draw_y() + Camera::m_pos[0].get_y(), m_rotation);
}

bool Bullet::is_dead() {
    return m_distance_left <= 0;
}

void Bullet::notify_collision(GameObject& other){
    if(!other.is("bullet")){
        if(m_targets_player && !other.is("alien")){
            m_distance_left = -1;
        }

        if(!m_targets_player && other.is("alien")){
            m_distance_left = -1;
        }
    }
}

bool Bullet::is(string type){
    return type == "bullet";
}