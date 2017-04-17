#include "camera.h"

GameObject *Camera::m_focus = nullptr;
Vector Camera::m_pos = Vector();
Vector Camera::m_speed = Vector();

void Camera::follow(GameObject *new_focus){
    m_focus = new_focus;
}

void Camera::unfollow(){
    m_focus = nullptr;
}

void Camera::update(double dt){
    InputManager input_manager = InputManager::get_instance();

    m_speed = Vector(0, 0);

    if(m_focus){
        m_pos = Vector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    else{
        if(input_manager.is_key_down(RIGHT_ARROW_KEY)){
            m_speed.set_x(-1.0 / dt);
        }
        else if(input_manager.is_key_down(LEFT_ARROW_KEY)){
            m_speed.set_x(1.0 / dt);
        }
        else if(input_manager.is_key_down(UP_ARROW_KEY)){
            m_speed.set_y(1.0 / dt);
        }
        else if(input_manager.is_key_down(DOWN_ARROW_KEY)){
            m_speed.set_y(-1.0 / dt);
        }

        m_pos.increment_x(m_speed.get_x());
        m_pos.increment_y(m_speed.get_y());
    }
}
