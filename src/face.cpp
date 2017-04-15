#include "face.h"
#include "input_manager.h"

Face::Face(int x, int y) : m_hitpoints(30), m_sp(Sprite("img/penguinface.png")) {
    m_box = Rectangle(x, y, m_sp.get_width(), m_sp.get_height());
}

Face::~Face(){

}

void Face::damage(int damage){
    m_hitpoints -= damage;
}

void Face::update(float dt){
    InputManager input_manager = InputManager::get_instance();
    int mouse_x = input_manager.get_mouse_x();
    int mouse_y = input_manager.get_mouse_y();

    for(int i = 0; i < 6; i++){
        if(input_manager.is_mouse_down(i) && m_box.is_inside(mouse_x, mouse_y)){
            damage(rand() % 10 + 10);
        }
    }
}

void Face::render(){
    m_sp.render(m_box.get_x(), m_box.get_y());
}

bool Face::is_dead(){
    return m_hitpoints <= 0;
}
