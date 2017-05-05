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
                Vector m_initial_pos, m_final_pos;
                Vector m_distance;
                Vector m_current_camera;
                
                Action(){}

                Action(ActionType type, double x, double y) {
                    m_initial_pos = Vector(x, y);
                    m_type = type;
                }

                Action(ActionType type, Vector initial_pos, Vector final_pos, Vector camera){
                    m_type = type;
                    m_initial_pos = initial_pos;
                    m_final_pos = final_pos;
                    m_current_camera = camera;

                    m_distance.set_x(initial_pos.get_x() - final_pos.get_x());
                    m_distance.set_y(initial_pos.get_y() - final_pos.get_y());
                }
        };

        Action m_action;
        bool m_active_action;
        queue<Action> m_task_queue;

    public:
        Alien(double x, double y, int n_minions);
        ~Alien();

        void update(double dt);
        void render();
        bool is_dead();
        bool same_position(Vector v, Vector current_camera);
        bool speed_not_set(Action action);
        void set_speed(Action action, double delta_time);
};

#endif
