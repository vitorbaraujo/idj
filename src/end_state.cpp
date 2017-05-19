#include "end_state.h"
#include "input_manager.h"
#include "game.h"
#include "stage_state.h"
#include "title_state.h"

#define TEXT_TIMER_COOLDOWN 0.5

EndState::EndState(StateData state_data){
    if(state_data.player_victory){
        m_bg = Sprite("img/win.jpg");
        m_music = Music("audio/endStateWin.ogg");
    }
    else{
        m_bg = Sprite("img/lose.jpg");
        m_music = Music("audio/endStateLose.ogg");
    }

    m_instruction = new Text("font/Call me maybe.ttf", 25, Text::TextStyle::SOLID, "Pressione ESC para ir ao menu ou espaco para tentar de novo");
    m_instruction->set_pos(512, 550, true);
    m_show_text = true;
}

void EndState::update(double dt){
    InputManager input_manager = InputManager::get_instance();

    if(input_manager.quit_requested()){
        m_quit_requested = true;
        return;
    }

    if(input_manager.on_key_press(ESCAPE_KEY)){
        m_pop_requested = true;
        Game::get_instance().push(new TitleState());
        return;
    }

    if(input_manager.on_key_press(SPACE_KEY)){
        Game::get_instance().push(new StageState());
        m_pop_requested = true;
        return;
    }

    if(m_text_timer.get() > TEXT_TIMER_COOLDOWN){
        m_show_text = !m_show_text;
        m_text_timer.restart();
    }

    m_text_timer.update(dt);
}

void EndState::render(){
    m_bg.render(0, 0);

    if(m_show_text)
        m_instruction->render();
}

void EndState::pause(){

}

void EndState::resume(){

}
