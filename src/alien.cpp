#include "alien.h"

Alien::Alien(double x, double y, int n_minions){
    m_sp = Sprite("img/alien.png");

    m_class = Alien::Action(Alien::Action::ActionType::MOVE, x, y);
}

Alien::~Alien(){
}

void Alien::update(double dt){

}

void Alien::render(){

}

bool Alien::is_dead(){

}
