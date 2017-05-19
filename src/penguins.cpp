#include "penguins.h"
#include "bullet.h"
#include "stage_state.h"
#include "game.h"
#include "animation.h"
#include "sound.h"

#define MAX_SPEED 300.0
#define MIN_SPEED -300.0
#define MAP_WIDTH 1408
#define MAP_HEIGHT 1280
#define BULLET_TIME 0.5

Penguins* Penguins::m_player;

Penguins::Penguins(double x, double y, double rotation){
    m_body_sp = Sprite("img/penguin.png");
    m_cannon_sp = Sprite("img/cubngun.png");
    m_speed = Vector(0,0);
    m_linear_speed = 0;
    m_cannon_angle = 0;
    m_hp = 30;

    m_player = this;

    m_rotation = rotation;
    m_box = Rectangle(x, y, m_body_sp.get_width(), m_body_sp.get_height());
}

Penguins::~Penguins(){
    m_player = nullptr;
}

void Penguins::update(double dt){
    m_timer.update(dt);

    if(is_dead()){
        Sound sound("audio/boom.wav");
        sound.play(0); // loops + 1 times

        Animation *animation = new Animation(m_box.get_x(), m_box.get_y(), m_rotation, "img/penguindeath.png", 5, 0.1, 0.5, true);
        Game::get_instance().get_current_state().add_object(animation);

        Camera::unfollow();
    }

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
        m_rotation -= angle_offset;
        if(m_rotation < 0) m_rotation = 360;
    }
    else if(input_manager.is_key_down(D_KEY)){
        m_rotation += angle_offset;
        if(m_rotation > 360) m_rotation = 0;
    }

    m_cannon_angle = atan2(mouse_y - m_box.get_y(), mouse_x - m_box.get_x());

    if(input_manager.on_mouse_press(LEFT_MOUSE_BUTTON) && m_timer.get() > 1.0){
        m_timer.restart();
        shoot();
    }

    double rad_rotation = Utils::to_rad(m_rotation);

    m_speed = Vector(dt * m_linear_speed * cos(rad_rotation), dt * m_linear_speed * sin(rad_rotation));

    double updated_x = m_box.get_x() + m_speed.get_x();
    double updated_y = m_box.get_y() + m_speed.get_y();

    // make penguin walk only on map
    if(updated_x > MAP_WIDTH) m_box.set_x(MAP_WIDTH);
    else if(updated_x < 0) m_box.set_x(0);
    else m_box.set_x(updated_x);

    if(updated_y > MAP_HEIGHT) m_box.set_y(MAP_HEIGHT);
    else if(updated_y < 0) m_box.set_y(0);
    else m_box.set_y(updated_y);
}

void Penguins::render(){
    double cannon_deg_angle = Utils::to_deg(m_cannon_angle);

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

    Bullet *bullet = new Bullet(cannon_end.get_x(), cannon_end.get_y(), m_cannon_angle, speed, max_distance, "img/penguinbullet.png", BULLET_TIME, 4, false);

    Game::get_instance().get_current_state().add_object(bullet);
}

void Penguins::notify_collision(GameObject& other){
    if(other.is("bullet")){
        if(((Bullet&)other).m_targets_player)
            m_hp -= 5;
    }
}

bool Penguins::is(string type){
    return type == "penguins";
}
