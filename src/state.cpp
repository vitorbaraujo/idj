#include "state.h"

State::State(){
    m_pop_requested = false;
    m_quit_requested = false;
}

State::~State(){
}

void State::add_object(GameObject* object){
    m_object_array.emplace_back(object);
}

void State::load_assets(){
}

bool State::pop_requested(){
    return m_pop_requested;
}

bool State::quit_requested(){
    return m_quit_requested;
}

void State::update_array(double dt){
  for(unsigned int it = 0; it < m_object_array.size(); ++it){
      m_object_array[it]->update(dt);

      if(m_object_array[it]->is_dead()){
          m_object_array.erase(m_object_array.begin() + it);
          break;
      }
  }
}

void State::render_array(){
  for(auto& object : m_object_array) {
    object->render();
  }
}
