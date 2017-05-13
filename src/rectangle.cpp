#include "rectangle.h"

#include <iostream>

Rectangle::Rectangle(double x, double y, double w, double h) : m_x(x), m_y(y), m_w(w), m_h(h) {
}

double Rectangle::get_x(){
    return m_x;
}

double Rectangle::get_y(){
    return m_y;
}

double Rectangle::get_w(){
    return m_w;
}

double Rectangle::get_h(){
    return m_h;
}

double Rectangle::draw_x(){
    return m_x - m_w / 2;
}

double Rectangle::draw_y(){
    return m_y - m_h / 2;
}

void Rectangle::set_x(double x){
    m_x = x;
}

void Rectangle::set_y(double y){
    m_y = y;
}

bool Rectangle::is_inside(double mouse_x, double mouse_y) {
    bool between_width = (mouse_x >= m_x && mouse_x <= (m_x + m_w));
    bool between_height = (mouse_y >= m_y && mouse_y <= (m_y + m_h));

    return (between_width and between_height);
}

Rectangle Rectangle::get_center(){
    return Rectangle(draw_x(), draw_y());
}
