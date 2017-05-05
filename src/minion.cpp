#include "minion.h"
#include "camera.h"

#define OFFSET 200

Minion::Minion(GameObject *minion_center, double arc_offset){
    m_arc = arc_offset;
    m_center = minion_center;
    m_sp = Sprite("img/minion.png");

    Vector alien_center(Vector(minion_center->m_box));
    alien_center.increment_x(m_center->m_box.get_w() / 2);
    alien_center.increment_y(m_center->m_box.get_h() / 2);

    m_box = Rectangle(alien_center.get_x(), alien_center.get_y(), m_sp.get_width(), m_sp.get_height());
}

void Minion::update(double dt){
    m_arc += 1.0;
    if(m_arc > 360) m_arc = 0;
    double angle = m_arc * acos(-1) / 180.0;

    Vector center(m_center->m_box.get_x() + m_center->m_box.get_w() / 2, m_center->m_box.get_y() + m_center->m_box.get_h() / 2);
    Vector pos(center);
    pos.translate(OFFSET, 0);

    pos.rotate(angle, center);

    m_box = Rectangle(pos.get_x(), pos.get_y(), m_sp.get_height(), m_sp.get_width());
}

void Minion::render(){
    m_sp.render(m_box.get_x() + Camera::m_pos[0].get_x(), m_box.get_y() + Camera::m_pos[0].get_y());
}

bool Minion::is_dead(){
    return false;
}

void Minion::shoot(Vector pos){

}
