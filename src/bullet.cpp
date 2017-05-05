#include "bullet.h"
#include "camera.h"

Bullet::Bullet(double x, double y, double angle, double speed, double max_distance, string sprite) {
    m_sp = Sprite(sprite);
    m_box = Rectangle(x, y, m_sp.get_height(), m_sp.get_width());
    m_speed = Vector(cos(angle) * speed, sin(angle) * speed);
    m_distance_left = max_distance;
}

void Bullet::update(double dt) {
    m_box.set_x(m_box.get_x() - m_speed.get_x() * dt);
    m_box.set_y(m_box.get_y() - m_speed.get_y() * dt);

    double dist = hypot(m_speed.get_x(), m_speed.get_y());

    m_distance_left -= dist;
}

void Bullet::render() {
    m_sp.render(m_box.get_x() + Camera::m_pos[0].get_x(), m_box.get_y() + Camera::m_pos[0].get_y());
}

bool Bullet::is_dead() {
    return m_distance_left <= 0;
}
