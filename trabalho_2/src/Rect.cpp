#include "Rect.h"

Rect::Rect(float x, float y, float w, float h) : m_x(x), m_y(y), m_w(w), m_h(h) {

}

float Rect::get_x(){
	return m_x;
}

float Rect::get_y(){
	return m_y;
}

float Rect::get_w(){
	return m_w;
}

float Rect::get_h(){
	return m_h;
}

bool Rect::is_inside(float mouse_x, float mouse_y) {
	// do this
	return true;
}
