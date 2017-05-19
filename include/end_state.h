#ifndef END_STATE_H
#define END_STATE_H

#include "state.h"
#include "sprite.h"
#include "music.h"
#include "text.h"
#include "state_data.h"

class EndState : public State {
    private:
        Sprite m_bg;
        Music m_music;
        Text* m_instruction;

    public:
        EndState(StateData state_data);

        void update(double dt);
        void render();
        void pause();
        void resume();
};

#endif
