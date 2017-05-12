#include "penguins.h"

Penguins::Penguins(double x, double y){
    m_body_sp = Sprite("img/penguin.png");
    m_cannon_sp = Sprite("img/cubngun.png");
    m_speed = Vector(0,0);
    m_linear_speed = 0;
    m_cannon_angle = 0;
    m_hp = 30;

    m_player = this;

    m_rotation = 0;
    m_box = Rectangle(x, y, m_body_sp.get_width(), m_body_sp.get_height());
}

Penguins::~Penguins(){
    m_player = nullptr;
}

void Penguins::update(double dt){
    InputManager input_manager = InputManager::get_instance();
    double mouse_x = input_manager.get_mouse_x() - Camera::m_pos[0].get_x();
    double mouse_y = input_manager.get_mouse_y() - Camera::m_pos[0].get_y();

    double angle_offset = 5;
    double acceleration = 10;
    
    if(input_manager.is_key_down(W_KEY)){
        m_linear_speed += acceleration;     
    }
    else if(input_manager.is_key_down(S_KEY)){
        m_linear_speed -= acceleration;
    }

    if(input_manager.is_key_down(A_KEY)){
        m_rotation += angle_offset;
        if(m_rotation > 360) m_rotation = 0;
    }
    else if(input_manager.is_key_down(D_KEY)){
        m_rotation -= angle_offset;
        if(m_rotation < 0) m_rotation = 360;
    }

    m_cannon_angle = atan2(mouse_y - m_box.get_y(), mouse_x - m_box.get_x()) * 180 / acos(-1);

    if(input_manager.on_mouse_press(LEFT_MOUSE_BUTTON)){
        //shoot();
    }

    double rad_rotation = m_rotation * acos(-1) / 180.0;

    m_speed = Vector(dt * m_linear_speed * cos(rad_rotation), dt * m_linear_speed * sin(rad_rotation));

    m_box.set_x(m_box.get_x() + m_speed.get_x());
    m_box.set_y(m_box.get_y() + m_speed.get_y());
}

void Penguins::render(){
    m_body_sp.render(m_box.draw_x() + Camera::m_pos[0].get_x(), m_box.draw_y() + Camera::m_pos[0].get_y(), m_rotation);

    double cannon_x = m_box.draw_x() + abs(m_body_sp.get_width() - m_cannon_sp.get_width()) / 2;
    double cannon_y = m_box.draw_y() + abs(m_body_sp.get_height() - m_cannon_sp.get_height()) / 2;
    m_cannon_sp.render(cannon_x + Camera::m_pos[0].get_x(), cannon_y + Camera::m_pos[0].get_y(), m_cannon_angle);
}

bool Penguins::is_dead(){
    return m_hp <= 0;
}

void Penguins::shoot(){

}
