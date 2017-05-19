#include "alien.h"
#include "rectangle.h"
#include "input_manager.h"
#include "camera.h"
#include "bullet.h"
#include "animation.h"
#include "game.h"
#include "penguins.h"
#include "sound.h"

#define SPEED_FACTOR 100
#define ROTATE_FACTOR 0.5
#define AI_COOLDOWN 3

int Alien::m_alien_count;

Alien::Alien(double x, double y, int n_minions, double rotation){
    m_alien_count++;
    m_state = Alien::AlienState::RESTING;

    m_rotation = rotation;

    m_sp = Sprite("img/alien.png");
    m_box = Rectangle(x, y, m_sp.get_width(), m_sp.get_height());
    m_hp = 30;
    m_speed = Vector(0, 0);

    for(int i = 0;i < n_minions; i++){
        double arc = i * (360.0 / n_minions);
        m_minion_array.push_back(Minion(this, arc, arc));
    }
}

Alien::~Alien(){
    m_alien_count--;
}

void Alien::update(double dt){
    // AI only if player is alive
    if(Penguins::m_player){
        if(m_rest_timer.get() > AI_COOLDOWN){
            m_destination = Penguins::m_player->m_box;

            m_speed = set_speed(m_destination, dt);
            m_state = Alien::AlienState::MOVING;
        }

        if(m_state == Alien::AlienState::RESTING){
            m_rest_timer.update(dt);
        }
        else if(m_state == Alien::AlienState::MOVING){
            m_box.set_x(m_box.get_x() + m_speed.get_x());
            m_box.set_y(m_box.get_y() + m_speed.get_y());

            if(close_enough(m_destination)){
                m_destination = Penguins::m_player->m_box;
                m_minion_array[get_closest_minion()].shoot(m_destination);
                m_rest_timer.restart();
                m_state = Alien::AlienState::RESTING;
            }
        }
    }

    if(is_dead()){
        Sound sound("audio/boom.wav");
        sound.play(0); // loops + 1 times

        Animation *alien_animation = new Animation(m_box.get_x(), m_box.get_y(), 0, "img/aliendeath.png", 4, 0.1, 0.5, true);

        Game::get_instance().get_current_state().add_object(alien_animation);

        for(auto minion : m_minion_array){
            Animation *minion_animation = new Animation(minion.m_box.get_x(), minion.m_box.get_y(), 0, "img/miniondeath.png", 4, 0.1, 0.5, true);
            Game::get_instance().get_current_state().add_object(minion_animation);
        }
    }

    for(auto &minion : m_minion_array){
        minion.update(dt);
    }

    // rotating alien
    m_rotation -= ROTATE_FACTOR;
    if(m_rotation < 0) m_rotation += 360;
}

void Alien::render(){
    m_sp.render(m_box.draw_x() + Camera::m_pos[0].get_x(), m_box.draw_y() + Camera::m_pos[0].get_y(), m_rotation);

    for(auto minion : m_minion_array){
        minion.render();
    }
}

bool Alien::is_dead(){
    return m_hp <= 0;
}

bool Alien::close_enough(Vector other){
    double dist = hypot(m_box.get_x() - other.get_x(), m_box.get_y() - other.get_y());
    return dist <= 300;
}

Vector Alien::set_speed(Vector pos, double dt){
    double angle = atan2(pos.get_y() - m_box.get_y(), pos.get_x() - m_box.get_x());

    return Vector(SPEED_FACTOR * dt * cos(angle), SPEED_FACTOR * dt * sin(angle));
}

void Alien::notify_collision(GameObject& other){
    if(other.is("bullet") && !((Bullet&)other).m_targets_player)
        m_hp -= 5;
}

bool Alien::is(string type){
    return type == "alien";
}

int Alien::get_closest_minion(){
    double min_dist = 1e9;
    int minion_idx = 0;

    for(unsigned int i = 0; i < m_minion_array.size(); i++){
        Minion minion = m_minion_array[i];
        double dist = hypot(minion.m_box.get_x() - m_destination.get_x(), minion.m_box.get_y() - m_destination.get_y());
        if(dist < min_dist){
            minion_idx = i;
            min_dist = dist;
        }
    }

    return minion_idx;
}
