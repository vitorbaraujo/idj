#include "game.h"

using namespace std;

int main(int argc, char** argv){
    Game* game = new Game("IDJ", 1024, 600);

    game->run();

    return 0;
}
