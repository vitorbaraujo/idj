#ifndef VEC2_H
#define VEC2_H

#include <utility>
#include <cmath>

using std::pair;

class Vec2 {
    private:
        int m_x, m_y;

    public:
        Vec2(int x = 0, int y = 0);

        int get_x();
        int get_y();
        double length();
        void scale(int sx, int sy);
        Vec2 translate(Vec2 p, int dx, int dy);
        Vec2 rotate(Vec2 p, double angle);
        Vec2 rotate(Vec2 p, double angle, int cx, int cy);
};

#endif
