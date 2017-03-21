#include "Game.h"

using namespace std;

int main(int argc, char** argv){
    Game* game = new Game("Vitor Barbosa de Araujo - 14/0033149", 1024, 600);

    game->run();

    return 0;
}
