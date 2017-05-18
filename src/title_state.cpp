#include "title_state.h"
#include "input_manager.h"
#include "stage_state.h"
#include "game.h"

TitleState::TitleState(){
    m_bg = Sprite("img/title.jpg");
}

void TitleState::update(double){
    InputManager input_manager = InputManager::get_instance();

    if(input_manager.is_key_down(ESCAPE_KEY)){
        m_quit_requested = true;
    }

    if(input_manager.is_key_down(SPACE_KEY)){
        // m_pop_requested = true;
        StageState* stage_state = new StageState();
        Game::get_instance().push(stage_state);
    }
}

void TitleState::render(){
    m_bg.render(0, 0);
}

void TitleState::pause(){
}

void TitleState::resume(){
}
