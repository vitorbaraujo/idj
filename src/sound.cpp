#include "sound.h"
#include "resources.h"

Sound::Sound(){
    m_chunk = nullptr;
}

Sound::Sound(string file){
    open(file);
}

void Sound::play(int times){
    m_channel = Mix_PlayChannel(-1, m_chunk.get(), times);
}

void Sound::stop(){
    Mix_HaltChannel(m_channel);
}

void Sound::open(string file){
    m_chunk = Resources::get_sound(file);
}

bool Sound::is_open(){
    return m_chunk != nullptr;
}
