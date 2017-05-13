#include "camera.h"

GameObject *Camera::m_focus = nullptr;
Vector Camera::m_pos[3];
Vector Camera::m_speed[3];

void Camera::follow(GameObject *new_focus){
    m_focus = new_focus;
}

void Camera::unfollow(){
    m_focus = nullptr;
}

void Camera::update(double dt){
    InputManager input_manager = InputManager::get_instance();

    m_speed[0] = Vector(0, 0);
    m_speed[1] = Vector(0, 0);

    if(m_focus){
        double focus_x = m_focus->m_box.get_x();
        double focus_y = m_focus->m_box.get_y();

        m_pos[0] = Vector(-focus_x + SCREEN_WIDTH / 2, -focus_y + SCREEN_HEIGHT / 2);
        m_pos[1] = Vector(-focus_x + SCREEN_WIDTH / 2, -focus_y + SCREEN_HEIGHT / 2);
    }
    else{
        if(input_manager.is_key_down(RIGHT_ARROW_KEY)){
            m_speed[0].set_x(-1.0 / dt);
            m_speed[1].set_x(-0.6 / dt);
        }
        if(input_manager.is_key_down(LEFT_ARROW_KEY)){
            m_speed[0].set_x(1.0 / dt);
            m_speed[1].set_x(0.6 / dt);
        }
        if(input_manager.is_key_down(UP_ARROW_KEY)){
            m_speed[0].set_y(1.0 / dt);
            m_speed[1].set_y(0.6 / dt);
        }
        if(input_manager.is_key_down(DOWN_ARROW_KEY)){
            m_speed[0].set_y(-1.0 / dt);
            m_speed[1].set_y(-0.6 / dt);
        }

        m_pos[0].increment_x(m_speed[0].get_x());
        m_pos[0].increment_y(m_speed[0].get_y());

        m_pos[1].increment_x(m_speed[1].get_x());
        m_pos[1].increment_y(m_speed[1].get_y());
    }
}
