#include "music.h"
#include "resources.h"

Music::Music(){
    m_music = nullptr;
}

Music::Music(string file){
    open(file);
}

Music::~Music(){
}

void Music::play(int times){
    Mix_PlayMusic(m_music, times);
}

void Music::stop(int ms){
    Mix_FadeOutMusic(ms);
}

void Music::open(string file){
    m_music = Resources::get_music(file).get();
}

bool Music::is_open(){
    return m_music != nullptr;
}
