#include "minion.h"

Minion::Minion(GameObject *minion_center, double arc_offset){
    m_arc = arc_offset;
    m_center = minion_center;
    m_sp = Sprite("img/minion.png");
}

void Minion::update(double dt){

}

void Minion::render(){
    //m_sp.render();
}

bool Minion::is_dead(){
    return false;
}

void Minion::shoot(Vector pos){

}
