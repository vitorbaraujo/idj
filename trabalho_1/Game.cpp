#include "Game.cpp"


Game::Game(string title, int widht, int height){
    if(instance != nullptr){
        instance = this; 
    }

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 0;
    }

    int image_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

    if(IMG_Init(image_flags) != image_flags){
        printf("IMG_Init error: %s\n", IMG_GetError());
        return 0;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, widht, height, 0);

    if(window == nullptr){
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return 0;
    }

    // SDL_RENDERER_ACCELERATED to require use of OpenGL or Direct3D
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr){
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        return 0;
    }

    state = new State();
}

Game::~Game(){
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Game::void run(){
    while(!state->quit_requested()){
       state->update();
       state->render();

       SDL_RenderPresent(renderer);
       SDL_Delay(33);
    }
}

Game::SDL_Renderer* get_renderer(){
    return renderer;
}

Game::State& get_state(){
    return state;
}

Game::Game& get_instance(){
    return instance;
}
