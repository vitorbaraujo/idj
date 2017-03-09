#include <SDL2/SDL.h>

class Sprite {
    private:
        SDL_Texture* texture;
        int widht, height;
        SDL_Rect clip_rect;

    public:
        Sprite();
        Sprite(string filename);
        ~Sprite();

        void open(string filename);
        void set_clip(int x, int y, int w, int h);
        void render(int x, int y);
        int get_width();
        int get_height();
        bool is_open();
}
