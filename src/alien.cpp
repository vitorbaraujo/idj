#include "alien.h"
#include "rectangle.h"
#include "input_manager.h"
#include "camera.h"

Alien::Alien(double x, double y, int n_minions){
    m_sp = Sprite("img/alien.png");
    m_box = Rectangle(x, y, m_sp.get_width(), m_sp.get_height());
    m_hp = 30; // fixme
    m_speed = Vector(0, 0);
    // initialize m_class
    // populate m_minion_array
}

Alien::~Alien(){
}

void Alien::update(double dt){
    InputManager input_manager = InputManager::get_instance();

    double mouse_x = input_manager.get_mouse_x();
    double mouse_y = input_manager.get_mouse_y();
    double camera_x = Camera::m_pos[0].get_x();
    double camera_y = Camera::m_pos[0].get_y();

    double pos_x = mouse_x + camera_x;
    double pos_y = mouse_y + camera_y;

    // queueing actions
    if(input_manager.on_mouse_press(LEFT_MOUSE_BUTTON)){
        Action action = Action(Action::ActionType::SHOOT, pos_x, pos_y);
        m_task_queue.push(action);
    }
    else if(input_manager.on_mouse_press(RIGHT_MOUSE_BUTTON)){
        Action action = Action(Action::ActionType::MOVE, pos_x, pos_y);
        m_task_queue.push(action);
    }

    // handle pending actions
    if(not m_task_queue.empty()){
        Action action = m_task_queue.front();
        m_task_queue.pop();

        if(action.m_type == Action::ActionType::MOVE){
            printf("MOVE\n");

            printf("DISTANCE: %.2f\n", action.m_pos.distance(Vector(m_box.get_x(), m_box.get_y())));
        }
        else if(action.m_type == Action::ActionType::SHOOT){
            // do nothing
            printf("SHOOT\n");
        }
    }
}

void Alien::render(){
    double camera_x = Camera::m_pos[0].get_x();
    double camera_y = Camera::m_pos[0].get_y();

    m_sp.render(m_box.get_x() + camera_x, m_box.get_y() + camera_y);

    for(auto minion : m_minion_array){
        int minion_x = minion.m_box.get_x() + camera_x;
        int minion_y = minion.m_box.get_y() + camera_y;

        minion.render();
    }
}

bool Alien::is_dead(){
    return m_hp <= 0;
}
