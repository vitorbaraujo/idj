#include "penguins.h"
#include "bullet.h"
#include "state.h"
#include "game.h"

#define MAX_SPEED 600.0
#define MIN_SPEED -600.0

#define BULLET_TIME 0.5

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
        m_linear_speed = min(m_linear_speed + acceleration, MAX_SPEED);     
    }
    else if(input_manager.is_key_down(S_KEY)){
        m_linear_speed = max(m_linear_speed - acceleration, MIN_SPEED);
    }

    if(input_manager.is_key_down(A_KEY)){
        m_rotation += angle_offset;
        if(m_rotation > 360) m_rotation = 0;
    }
    else if(input_manager.is_key_down(D_KEY)){
        m_rotation -= angle_offset;
        if(m_rotation < 0) m_rotation = 360;
    }

    m_cannon_angle = atan2(mouse_y - m_box.get_y(), mouse_x - m_box.get_x());

    if(input_manager.on_mouse_press(LEFT_MOUSE_BUTTON)){
        // shoot();
    }

    double rad_rotation = m_rotation * acos(-1) / 180.0;

    m_speed = Vector(dt * m_linear_speed * cos(rad_rotation), dt * m_linear_speed * sin(rad_rotation));

    m_box.set_x(m_box.get_x() + m_speed.get_x());
    m_box.set_y(m_box.get_y() + m_speed.get_y());
}

void Penguins::render(){
    double cannon_deg_angle = m_cannon_angle * 180 / acos(-1);

    double diff_w = fabs(m_body_sp.get_width() - m_cannon_sp.get_width()) / 2;
    double diff_h = fabs(m_body_sp.get_height() - m_cannon_sp.get_height()) / 2;

    double body_x = m_box.draw_x() + Camera::m_pos[0].get_x();
    double body_y = m_box.draw_y() + Camera::m_pos[0].get_y();
    double cannon_x = body_x + diff_w;
    double cannon_y = body_y + diff_h;

    m_body_sp.render(body_x, body_y, m_rotation);
    m_cannon_sp.render(cannon_x, cannon_y, cannon_deg_angle);
}

bool Penguins::is_dead(){
    return m_hp <= 0;
}

void Penguins::shoot(){
    double speed = 100;
    double max_distance = 20000;

    double diff_w = fabs(m_body_sp.get_width() - m_cannon_sp.get_width()) / 2;
    double diff_h = fabs(m_body_sp.get_height() - m_cannon_sp.get_height()) / 2;

    double cannon_x = m_box.draw_x() + diff_w + m_cannon_sp.get_width() / 2;
    double cannon_y = m_box.draw_y() + diff_h + m_cannon_sp.get_height() / 2;

    Vector cannon_end(cannon_x + m_cannon_sp.get_width() * 0.8, cannon_y);
    cannon_end.rotate(m_cannon_angle, Vector(cannon_x, cannon_y));

    Bullet *bullet = new Bullet(cannon_end.get_x(), cannon_end.get_y(), m_cannon_angle, speed, max_distance, "img/penguinbullet.png", BULLET_TIME, 4);

    State *state = Game::get_instance().get_state();
    state->add_object(bullet);
}

void Penguins::notify_collision(GameObject& other){

}

bool Penguins::is(string type){
    return type == "penguins";
}