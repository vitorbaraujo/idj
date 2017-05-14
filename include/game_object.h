#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>

#include "rectangle.h"
#include "utils.h"

using std::string;

class GameObject {
    public:
        virtual ~GameObject() {}

        virtual void update(double dt) = 0;
        virtual void render() = 0;
        virtual bool is_dead() = 0;
        virtual void notify_collision(GameObject& other) = 0;
        virtual bool is(string type) = 0;

        Rectangle m_box;
        double m_rotation;
};

#endif
