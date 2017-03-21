#include "Rect.h"
#include <iostream>

Rect::Rect(int x, int y, int w, int h) : m_x(x), m_y(y), m_w(w), m_h(h) {
	m_x -= m_w / 2;
	m_y -= m_h / 2;
}

int Rect::get_x(){
	return m_x;
}

int Rect::get_y(){
	return m_y;
}

int Rect::get_w(){
	return m_w;
}

int Rect::get_h(){
	return m_h;
}

bool Rect::is_inside(int mouse_x, int mouse_y) {
	if(mouse_x >= m_x && mouse_x <= (m_x + m_w) && mouse_y >= m_y && mouse_y <= (m_y + m_h)){
		return true;
	}

	return false;
}
