#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "state.h"
#include "sprite.h"

class TitleState : public State {
    private:
        Sprite m_bg;

    public:
        TitleState();

        void update(double dt);
        void render();
        void pause();
        void resume();
};

#endif
