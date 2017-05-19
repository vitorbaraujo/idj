#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "state.h"
#include "sprite.h"
#include "text.h"
#include "timer.h"

class TitleState : public State {
    private:
        Sprite m_bg;
        Text* m_text;
        Timer m_text_timer;
        bool m_show_text;

    public:
        TitleState();

        void update(double dt);
        void render();
        void pause();
        void resume();
};

#endif
