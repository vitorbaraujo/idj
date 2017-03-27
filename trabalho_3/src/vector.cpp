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

Vector Vector::translate(Vector p, int dx, int dy) {
    return Vector(p.get_x() + dx, p.get_y() + dy);
}

Vector Vector::rotate(Vector p, double angle) {
    double new_x = p.get_x() * cos(angle) - p.get_y() * sin(angle);
    double new_y = p.get_x() * sin(angle) + p.get_y() * cos(angle);

    return Vector((int)new_x, (int)new_y);
}

Vector Vector::rotate(Vector p, double angle, int cx, int cy) {
    Vector q = translate(p, -cx, -cy);
    q = rotate(q, angle);
    q = translate(q, cx, cy);

    return q;
}
