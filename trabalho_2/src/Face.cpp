#include "Face.h"

Face::Face(float x, float y){
	m_sp = new Sprite("res/img/penguinface.png");
	// change x and y to be in the center, not the corner
	m_box = Rect(x, y);	
}

void Face::damage(int damage){
	m_hitpoints -= damage;
}

void Face::update(float dt){

}

void Face::render(){
	printf("render face in (%d, %d)\n", (int)m_box.get_x(), (int)m_box.get_y());
	m_sp->render((int)m_box.get_x(), (int)m_box.get_y());
}

bool Face::is_dead(){
	return m_hitpoints <= 0;
}