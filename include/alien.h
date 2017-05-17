#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <vector>

#include "game_object.h"
#include "sprite.h"
#include "vector.h"
#include "minion.h"
#include "timer.h"

using std::queue;
using std::vector;

class Alien : public GameObject {
    private:
        enum AlienState { MOVING, RESTING };

        int m_hp;
        AlienState m_state;
        Sprite m_sp;
        Vector m_speed, m_destination;
        Timer m_rest_timer;

        vector<Minion> m_minion_array;

    public:
        Alien(double x, double y, int n_minions, double rotation = 0);
        ~Alien();

        void update(double dt);
        void render();
        bool is_dead();
        bool close_enough(Vector other);
        void notify_collision(GameObject& other);
        bool is(string type);
        Vector set_speed(Vector pos, double dt);
        int get_closest_minion();

        static int m_alien_count;
};

#endif
