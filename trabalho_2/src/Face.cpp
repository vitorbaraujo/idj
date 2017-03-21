#include "Face.h"

Face::Face(int x, int y) : m_hitpoints(30), m_sp(Sprite("res/img/penguinface.png")) {
	m_box = Rect(x, y, m_sp.get_width(), m_sp.get_height());
}

void Face::damage(int damage){
	m_hitpoints -= damage;
}

void Face::update(float dt){

}

void Face::render(){
	m_sp.render(m_box.get_x(), m_box.get_y());
}

bool Face::is_dead(){
	return m_hitpoints <= 0;
}