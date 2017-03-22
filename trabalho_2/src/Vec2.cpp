#include "Vec2.h"

#include <cmath>

Vec2::Vec2(int x, int y) : m_x(x), m_y(y) {

}

int Vec2::get_x() {
    return m_x;
}

int Vec2::get_y() {
    return m_y;
}

double Vec2::length() {
    return hypot(m_x, m_y);
}

void Vec2::scale(int sx, int sy) {
    m_x *= sx;
    m_y *= sy;
}

Vec2 Vec2::translate(Vec2 p, int dx, int dy) {
    return Vec2(p.get_x() + dx, p.get_y() + dy);
}

Vec2 Vec2::rotate(Vec2 p, double angle) {
    double new_x = p.get_x() * cos(angle) - p.get_y() * sin(angle);
    double new_y = p.get_x() * sin(angle) + p.get_y() * cos(angle);

    return Vec2((int)new_x, (int)new_y);
}

Vec2 Vec2::rotate(Vec2 p, double angle, int cx, int cy) {
    Vec2 q = translate(p, -cx, -cy);
    q = rotate(q, angle);
    q = translate(q, cx, cy);

    return q;
}
