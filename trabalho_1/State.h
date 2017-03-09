#include <SDL2/SDL.h>

class State {
    private:
        Sprite bg;
        bool requested_quit;

    public:
        State();

        bool quit_requested();
        void update(float dt);
        void render();
}
