#include "rectangle.h"

#include <iostream>

Rectangle::Rectangle(int x, int y, int w, int h) : m_x(x), m_y(y), m_w(w), m_h(h) {
	m_x -= m_w / 2;
	m_y -= m_h / 2;
}

int Rectangle::get_x(){
	return m_x;
}

int Rectangle::get_y(){
	return m_y;
}

int Rectangle::get_w(){
	return m_w;
}

int Rectangle::get_h(){
	return m_h;
}

bool Rectangle::is_inside(int mouse_x, int mouse_y) {
	if(mouse_x >= m_x && mouse_x <= (m_x + m_w) && mouse_y >= m_y && mouse_y <= (m_y + m_h)){
		return true;
	}

	return false;
}
