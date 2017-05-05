#include "alien.h"
#include "rectangle.h"
#include "input_manager.h"
#include "camera.h"

#define SPEED_FACTOR 150
#define ROTATE_FACTOR 0.5

Alien::Alien(double x, double y, int n_minions, double rotation){
    m_rotation = rotation;

    m_sp = Sprite("img/alien.png");
    m_box = Rectangle(x, y, m_sp.get_width(), m_sp.get_height());
    m_hp = 30; // fixme
    m_speed = Vector(0, 0);
    m_active_action = false;

    for(int i = 0;i < n_minions; i++){
        double arc = i * (360.0 / n_minions);
        m_minion_array.push_back(Minion(this, arc, arc));
    }
}

Alien::~Alien(){
}

void Alien::update(double dt){
    for(auto &minion : m_minion_array){
        minion.update(dt);
    }

    m_rotation -= ROTATE_FACTOR;
    if(m_rotation < 0) m_rotation += 360;

    InputManager input_manager = InputManager::get_instance();

    double mouse_x = input_manager.get_mouse_x();
    double mouse_y = input_manager.get_mouse_y();
    double camera_x = Camera::m_pos[0].get_x();
    double camera_y = Camera::m_pos[0].get_y();

    // queueing actions
    if(input_manager.on_mouse_press(LEFT_MOUSE_BUTTON)){
        Action action = Action(Action::ActionType::SHOOT, mouse_x - camera_x, mouse_y - camera_y);
        m_task_queue.push(action);
    }
    else if(input_manager.on_mouse_press(RIGHT_MOUSE_BUTTON)){
        // if there is a current movement action, stop this and begin new one
        if(m_active_action && m_action.m_type == Action::ActionType::MOVE){
            m_task_queue.pop();
            m_speed = Vector(0,0);
        }

        Vector initial_position(m_box.get_x() + m_box.get_w() / 2, m_box.get_y() + m_box.get_h() / 2);
        Vector final_position(mouse_x - camera_x, mouse_y - camera_y);

        Action action = Action(Action::ActionType::MOVE, initial_position, final_position);
        m_task_queue.push(action);
    }

    // handle pending actions
    if(not m_task_queue.empty()){
        m_action = m_task_queue.front();
        m_active_action = true;

        if(m_action.m_type == Action::ActionType::MOVE){
            if(same_position(m_action.m_final_pos)){
                m_task_queue.pop();
                m_speed = Vector(0,0);
                m_active_action = false;
            }
            else{
                set_speed(m_action, dt);
            }
        }

        else if(m_action.m_type == Action::ActionType::SHOOT){
            int idx_minion = rand() % m_minion_array.size();
            Minion minion = m_minion_array[idx_minion];

            minion.shoot(m_action.m_initial_pos);

            m_task_queue.pop();
        }
    }

    m_box.set_x(m_box.get_x() - m_speed.get_x());
    m_box.set_y(m_box.get_y() - m_speed.get_y());
}

void Alien::render(){
    double camera_x = Camera::m_pos[0].get_x();
    double camera_y = Camera::m_pos[0].get_y();

    m_sp.render(m_box.get_x() + camera_x, m_box.get_y() + camera_y, m_rotation);

    for(auto minion : m_minion_array){
        minion.render();
    }
}

bool Alien::is_dead(){
    return m_hp <= 0;
}

bool Alien::same_position(Vector other){
    double EPS = 5;
    double diff_x = abs(m_box.get_x() + m_box.get_w() / 2 - other.get_x());
    double diff_y = abs(m_box.get_y() + m_box.get_h() / 2 - other.get_y());

    return diff_x < EPS && diff_y < EPS;
}

bool Alien::speed_not_set(Action action){
    bool same_pos = same_position(action.m_final_pos);
    return not same_pos && m_speed.get_x() == 0 && m_speed.get_y() == 0;
}

void Alien::set_speed(Action action, double dt){
    Vector initial_pos = action.m_initial_pos;
    Vector final_pos = action.m_final_pos;

    double angle = atan2(initial_pos.get_y() - final_pos.get_y(), initial_pos.get_x() - final_pos.get_x());

    Vector velocity(SPEED_FACTOR * dt * cos(angle), SPEED_FACTOR * dt * sin(angle));

    m_speed = velocity;
}
