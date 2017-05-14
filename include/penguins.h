#ifndef PENGUINS_H
#define PENGUINS_H

#include <iostream>
#include <cmath>

#include "game_object.h"
#include "sprite.h"
#include "camera.h"
#include "timer.h"

using std::max;
using std::min;

class Penguins : public GameObject {
    private:
        Sprite m_body_sp;
        Sprite m_cannon_sp;
        Vector m_speed;
        double m_linear_speed;
        double m_cannon_angle;
        int m_hp;

    public:
        Penguins(double x, double y, double rotation = 0);
        ~Penguins();

        void update(double dt);
        void render();
        bool is_dead();
        void shoot();
        void notify_collision(GameObject& other);
        bool is(string type);

        Penguins* m_player;
        Timer m_timer;
};

#endif
