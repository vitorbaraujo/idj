#ifndef CAMERA_H
#define CAMERA_H

#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 600

#include "vector.h"
#include "game_object.h"
#include "input_manager.h"

class Camera {
    private:
        static GameObject *m_focus;

    public:
        static Vector m_pos[3], m_speed[3];

        static void follow(GameObject *new_focus);
        static void unfollow();
        static void update(double dt);
};

#endif
