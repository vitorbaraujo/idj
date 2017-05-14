#ifndef UTILS_H
#define UTILS_H

#include <cmath>

class Utils {
    public:
        static constexpr double PI = acos(-1);

        static double to_rad(double angle);
        static double to_deg(double angle);
};

#endif