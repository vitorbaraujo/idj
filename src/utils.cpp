#include "utils.h"

double Utils::to_rad(double angle){
    return angle * (PI / 180);
}

double Utils::to_deg(double angle){
    return angle * (180 / PI);
}