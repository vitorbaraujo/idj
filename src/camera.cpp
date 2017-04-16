#include "camera.h"

GameObject *Camera::m_focus = nullptr;
Vector Camera::m_pos = Vector();

void Camera::follow(GameObject *new_focus){
    m_focus = new_focus;
}

void Camera::unfollow(){
    m_focus = nullptr;
}

void Camera::update(double dt){
    if(m_focus){
        m_pos = Vector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    else{
        
    }
}
