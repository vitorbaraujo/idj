#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>
#include <algorithm>

#include "rectangle.h"
#include "vector.h"

class Collision {
    private:
        static inline double mag(const Vector& p);
        static inline Vector norm(const Vector& p);
        static inline double dot(const Vector& a, const Vector& b);
        static inline Vector rotate(const Vector& p, double angle);

    public:
        // Observação: IsColliding espera ângulos em radianos!
        // Para usar graus, forneça a sua própria implementação de rotate,
        // ou transforme os ângulos no corpo de IsColliding.
        static bool is_colliding(Rectangle& a, Rectangle& b, double a_angle, double b_angle);
};

#endif