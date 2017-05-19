#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "state.h"
#include "sprite.h"
#include "text.h"

class TitleState : public State {
    private:
        Sprite m_bg;
        Text* m_text;

    public:
        TitleState();

        void update(double dt);
        void render();
        void pause();
        void resume();
};

#endif
