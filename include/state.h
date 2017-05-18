#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <memory> // unique_ptr
#include <vector>

#include "game_object.h"

using std::vector;
using std::unique_ptr;

class State {
    public:
        State();
        virtual ~State();

        virtual void update(double dt) = 0;
        virtual void render() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void add_object(GameObject* object);

        bool pop_requested();
        bool quit_requested();

    protected:
        virtual void update_array(double dt);
        virtual void render_array();

        bool m_pop_requested;
        bool m_quit_requested;
        vector< unique_ptr<GameObject> > m_object_array;
};

#endif
