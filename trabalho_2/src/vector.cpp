#include "vector.h"

#include <cmath>

Vector::Vector(int x, int y) : m_x(x), m_y(y) {

}

int Vector::get_x() {
    return m_x;
}

int Vector::get_y() {
    return m_y;
}

double Vector::length() {
    return hypot(m_x, m_y);
}

void Vector::scale(int sx, int sy) {
    m_x *= sx;
    m_y *= sy;
}

void Vector::translate(int dx, int dy) {
    m_x += dx;
    m_y += dy;
}

void Vector::rotate(double angle) {
    int new_x = m_x * cos(angle) - m_y * sin(angle);
    int new_y = m_x * sin(angle) + m_y * cos(angle);

    m_x = new_x;
    m_y = new_y;
}

void Vector::rotate(double angle, Vector c) {
    translate(-c.get_x(), -c.get_y());
    rotate(angle);
    translate(c.get_x(), c.get_y());
}
