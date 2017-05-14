#include "animation.h"
#include "camera.h"

Animation::Animation(double x, double y, double rotation, string sprite, int frame_count, double frame_time, double time_limit, bool ends){
    m_sp = Sprite(sprite, frame_count, frame_time);
    m_time_limit = time_limit;
    m_one_time_only = ends;

    m_box = Rectangle(x, y, m_sp.get_width(), m_sp.get_height());
    m_rotation = rotation;
}

void Animation::update(double dt){
    m_sp.update(dt);
    m_end_timer.update(dt);
}

void Animation::render(){
    m_sp.render(m_box.draw_x() + Camera::m_pos[0].get_x(), m_box.draw_y() + Camera::m_pos[0].get_y(), m_rotation);
}

bool Animation::is_dead(){    
    return m_one_time_only && m_end_timer.get() >= m_time_limit;
}

void Animation::notify_collision(GameObject& other){

}

bool Animation::is(string type){
    return type == "animation";
}