#include "title_state.h"
#include "input_manager.h"
#include "stage_state.h"
#include "game.h"
#include "camera.h"

TitleState::TitleState(){
    m_bg = Sprite("img/title.jpg");
    m_text = new Text("font/Call me maybe.ttf", 40, Text::TextStyle::SOLID, "Pressione espaco para continuar");
    m_text->set_pos(512, 500, true);
}

void TitleState::update(double dt){
    InputManager input_manager = InputManager::get_instance();

    if(input_manager.on_key_press(ESCAPE_KEY) || input_manager.quit_requested()){
        m_quit_requested = true;
        return;
    }

    if(input_manager.on_key_press(SPACE_KEY)){
        Game::get_instance().push(new StageState());
        m_pop_requested = true;
        return;
    }

    update_array(dt);
}

void TitleState::render(){
    m_bg.render(0, 0);
    m_text->render();
}

void TitleState::pause(){
}

void TitleState::resume(){
}
