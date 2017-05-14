#include "alien.h"
#include "rectangle.h"
#include "input_manager.h"
#include "camera.h"
#include "bullet.h"
#include "animation.h"
#include "game.h"

#define SPEED_FACTOR 100
#define ROTATE_FACTOR 0.5

Alien::Alien(double x, double y, int n_minions, double rotation){
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
}

void Alien::update(double dt){
    if(is_dead()){
        State *state = Game::get_instance().get_state();

        Animation *alien_animation = new Animation(m_box.get_x(), m_box.get_y(), 0, "img/aliendeath.png", 4, 0.1, 0.5, true);
        state->add_object(alien_animation);    

        for(auto minion : m_minion_array){
            Animation *minion_animation = new Animation(minion.m_box.get_x(), minion.m_box.get_y(), 0, "img/miniondeath.png", 4, 0.1, 0.5, true);
            state->add_object(minion_animation);
        }


        Camera::unfollow();
    }

    for(auto &minion : m_minion_array){
        minion.update(dt);
    }

    // rotating alien
    m_rotation -= ROTATE_FACTOR;
    if(m_rotation < 0) m_rotation += 360;

    // get mouse input
    InputManager input_manager = InputManager::get_instance();
    double mouse_x = input_manager.get_mouse_x() - Camera::m_pos[0].get_x();
    double mouse_y = input_manager.get_mouse_y() - Camera::m_pos[0].get_y();

    // queueing actions
    if(input_manager.on_mouse_press(LEFT_MOUSE_BUTTON)){
        m_task_queue.push(Action(Action::ActionType::SHOOT, mouse_x, mouse_y));
    }
    else if(input_manager.on_mouse_press(RIGHT_MOUSE_BUTTON)){
        // if there is a current movement action, stop this and begin new one
        if(m_task_queue.front().m_type == Action::ActionType::MOVE)
            m_task_queue.pop();

        m_task_queue.push(Action(Action::ActionType::MOVE, mouse_x, mouse_y));
    }

    // handle pending actions
    if(not m_task_queue.empty()){
        Action action = m_task_queue.front();

        if(action.m_type == Action::ActionType::MOVE){
            if(same_position(action.m_pos)){
                m_box.set_x(action.m_pos.get_x());
                m_box.set_y(action.m_pos.get_y());
                m_task_queue.pop();
                m_speed = Vector();
            }
            else{
                m_speed = set_speed(action.m_pos, dt);
            }
        }

        else if(action.m_type == Action::ActionType::SHOOT){
            double min_dist = 1e9;
            int minion_idx = 0;

            for(unsigned int i = 0; i < m_minion_array.size(); i++){
                Minion minion = m_minion_array[i];
                double dist = hypot(minion.m_box.get_x() - action.m_pos.get_x(), minion.m_box.get_y() - action.m_pos.get_y());
                if(dist < min_dist){
                    minion_idx = i;
                    min_dist = dist;
                }
            }

            Minion minion = m_minion_array[minion_idx];
            minion.shoot(action.m_pos);

            m_task_queue.pop();
        }
    }

    m_box.set_x(m_box.get_x() + m_speed.get_x());
    m_box.set_y(m_box.get_y() + m_speed.get_y());
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

bool Alien::same_position(Vector other){
    double EPS = 11;
    double diff_x = fabs(m_box.get_x() - other.get_x());
    double diff_y = fabs(m_box.get_y() - other.get_y());

    return diff_x < EPS && diff_y < EPS;
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