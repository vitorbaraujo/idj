#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <vector>

#include "game_object.h"
#include "sprite.h"
#include "vector.h"
#include "minion.h"

using std::queue;
using std::vector;

class Alien : public GameObject {
    private:
        int m_hp;
        Sprite m_sp;
        Vector m_speed;

        vector<Minion> m_minion_array;

        class Action {
            public:
                enum ActionType { MOVE, SHOOT };

                ActionType m_type;
                Vector m_pos;
                
                Action(){}
                Action(ActionType type, double x, double y) {
                    m_pos = Vector(x, y);
                    m_type = type;
                }
        };

        queue<Action> m_task_queue;

    public:
        Alien(double x, double y, int n_minions, double rotation = 0);
        ~Alien();

        void update(double dt);
        void render();
        bool is_dead();
        bool same_position(Vector other);
        void notify_collision(GameObject& other);
        bool is(string type);
        Vector set_speed(Vector pos, double dt);
};

#endif
