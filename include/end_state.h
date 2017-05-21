#ifndef END_STATE_H
#define END_STATE_H

#include "state.h"
#include "sprite.h"
#include "music.h"
#include "text.h"
#include "state_data.h"
#include "timer.h"
#include "resources.h"

class EndState : public State {
    private:
        Sprite m_bg;
        Music m_music;
        Text* m_instruction;
        Timer m_text_timer;
        bool m_show_text;

    public:
        EndState(StateData state_data);

        void update(double dt);
        void render();
        void pause();
        void resume();
        void load_assets();
};

#endif
