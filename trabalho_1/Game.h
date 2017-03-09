#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game {
    private:
        Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

    public:
        Game(string title, int widht, int height);
        ~Game();

        void run();
        SDL_Renderer* get_renderer();
        State& get_state();
        Game& get_instance();
}
