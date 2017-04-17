#include "rectangle.h"

#include <iostream>

Rectangle::Rectangle(double x, double y, double w, double h) : m_x(x), m_y(y), m_w(w), m_h(h) {
    m_x -= m_w / 2;
    m_y -= m_h / 2;
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

bool Rectangle::is_inside(double mouse_x, double mouse_y) {
    bool between_width = (mouse_x >= m_x && mouse_x <= (m_x + m_w));
    bool between_height = (mouse_y >= m_y && mouse_y <= (m_y + m_h));

    return (between_width and between_height);
}
