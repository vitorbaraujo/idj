#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>

#include "game_object.h"
#include "timer.h"
#include "sprite.h"

using std::string;

class Animation : public GameObject {
    private:
        Timer m_end_timer;
        Sprite m_sp;
        double m_time_limit;
        bool m_one_time_only;

    public:
        Animation(double x, double y, double rotation, string sprite, int frame_count, double frame_time, double time_limit, bool ends);

        void update(double dt);
        void render();
        bool is_dead();
        void notify_collision(GameObject& other);
        bool is(string type);
};

#endif