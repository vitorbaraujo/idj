#include "game.h"
#include "stage_state.h"

using namespace std;

int main(int argc, char** argv){
    Game game("Vitor Barbosa de Araujo - 140033149", 1024, 600);

    StageState* stage_state = new StageState();
    game.push(stage_state);

    game.run();

    return 0;
}
