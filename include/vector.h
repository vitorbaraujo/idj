#ifndef VECTOR_H
#define VECTOR_H

#include "rectangle.h"

#include <cmath>

class Vector {
    private:
        double m_x, m_y;

    public:
        Vector(double x = 0, double y = 0);
        Vector(Rectangle r);
        Vector(const Vector &v);

        double get_x();
        double get_y();
        void increment_x(double x);
        void increment_y(double y);
        void set_x(double x);
        void set_y(double y);
        double length();
        double distance(Vector v);
        void scale(double sx, double sy);
        void translate(double dx, double dy);
        void rotate(double angle);
        void rotate(double angle, Vector c);
};

#endif
