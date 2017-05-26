#include "game.h"
#include "title_state.h"

using namespace std;

int main(int argc, char** argv){
    Game game("Vitor Barbosa de Araujo - 140033149", 1024, 600);

    game.push(new TitleState());
    game.run();

    return 0;
}
