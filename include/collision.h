#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>
#include <algorithm>

#include "rectangle.h"
#include "vector.h"
#include "utils.h"

class Collision {
    private:
        static inline double mag(const Vector& p);
        static inline Vector norm(const Vector& p);
        static inline double dot(const Vector& a, const Vector& b);
        static inline Vector rotate(const Vector& p, double angle);

    public:
        static bool is_colliding(Rectangle& a, Rectangle& b, double a_angle, double b_angle);
};

#endif