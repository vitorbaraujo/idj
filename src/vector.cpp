#include "vector.h"

#include <cmath>

Vector::Vector(double x, double y) : m_x(x), m_y(y) {

}

Vector::Vector(Rectangle r) : m_x(r.get_x()), m_y(r.get_y()) {

}

Vector::Vector(const Vector &v) : m_x(v.m_x), m_y(v.m_y) {

}

double Vector::get_x() {
    return m_x;
}

double Vector::get_y() {
    return m_y;
}

void Vector::increment_x(double x){
    m_x += x;
}

void Vector::increment_y(double y){
    m_y += y;
}

void Vector::set_x(double x){
    m_x = x;
}

void Vector::set_y(double y){
    m_y = y;
}

double Vector::length() {
    return hypot(m_x, m_y);
}

double Vector::distance(Vector v){
    return hypot(m_x - v.get_x(), m_y - v.get_y());
}

void Vector::scale(double sx, double sy) {
    m_x *= sx;
    m_y *= sy;
}

void Vector::translate(double dx, double dy) {
    m_x += dx;
    m_y += dy;
}

void Vector::rotate(double angle) {
    double new_x = m_x * cos(angle) - m_y * sin(angle);
    double new_y = m_x * sin(angle) + m_y * cos(angle);

    m_x = new_x;
    m_y = new_y;
}

void Vector::rotate(double angle, Vector c) {
    translate(-c.get_x(), -c.get_y());
    rotate(angle);
    translate(c.get_x(), c.get_y());
}
