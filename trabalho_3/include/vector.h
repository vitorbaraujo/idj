#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector {
    private:
        int m_x, m_y;

    public:
        Vector(int x = 0, int y = 0);

        int get_x();
        int get_y();
        double length();
        void scale(int sx, int sy);
        Vector translate(Vector p, int dx, int dy);
        Vector rotate(Vector p, double angle);
        Vector rotate(Vector p, double angle, int cx, int cy);
};

#endif
