#include "timer.h"

Timer::Timer() : m_time(0) {

}

void Timer::update(double dt){
    m_time += dt;
}

void Timer::restart(){
    m_time = 0;
}

double Timer::get(){
    return m_time;
}