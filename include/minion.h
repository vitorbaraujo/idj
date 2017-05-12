#ifndef MINION_H
#define MINION_H

#include "game_object.h"
#include "vector.h"
#include "sprite.h"

class Minion : public GameObject {
    private:
        GameObject *m_center;
        Sprite m_sp;
        double m_arc;

    public:
        Minion(GameObject *minion_center, double arc_offset = 0, double rotation = 0);

        void update(double dt);
        void render();
        bool is_dead();
        void shoot(Vector pos);
};

#endif
