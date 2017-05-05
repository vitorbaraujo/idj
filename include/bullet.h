#ifndef BULLET_H
#define BULLET_H

#include <iostream>

#include "game_object.h"
#include "sprite.h"
#include "vector.h"

using std::string;

class Bullet : public GameObject {
    private:
        Sprite m_sp;
        Vector m_speed;
        double m_distance_left;

    public:
        Bullet(double x, double y, double angle, double speed, double max_distance, string sprite);
        
        void update(double dt);
        void render();
        bool is_dead();
};

#endif
