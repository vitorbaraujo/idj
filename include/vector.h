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
        void set_x(int x);
        void set_y(int y);
        double length();
        void scale(int sx, int sy);
        void translate(int dx, int dy);
        void rotate(double angle);
        void rotate(double angle, Vector c);
};

#endif
