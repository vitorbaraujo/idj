#ifndef PENGUINS_H
#define PENGUINS_H

#include "game_object.h"
#include "sprite.h"
#include "camera.h"

class Penguins : public GameObject {
    private:
        Sprite m_body_sp;
        Sprite m_cannon_sp;
        Vector m_speed;
        double m_linear_speed;
        double m_cannon_angle;
        int m_hp;

    public:
        Penguins(double x, double y);
        ~Penguins();

        void update(double dt);
        void render();
        bool is_dead();
        void shoot();

        Penguins* m_player;
};

#endif
