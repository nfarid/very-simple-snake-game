
#include "audio_manager.hpp"
#include "../the_includes.hpp"
#include "../util/get_dir.hpp"
#include <cassert>

namespace  {
    const auto res_dir = Util::get_resource_dir();
}


namespace Core {


void AudioManager::playSound(const sf::SoundBuffer& buffer_, float volume/*=75*/) {
    for(auto& sound: soundArrayM) {
        if(sound.getBuffer() == &buffer_) {
            sound.play();
            return;
        }
    }

    soundArrayM[currentIndexM].setBuffer(buffer_);
    soundArrayM[currentIndexM].setVolume(volume);
    soundArrayM[currentIndexM].play();
    currentIndexM = (currentIndexM+1)%soundArrayM.size();

    assert( currentIndexM < soundArrayM.size() );
    assert( (currentIndexM+soundArrayM.size()-1)%soundArrayM.size() < soundArrayM.size() );


}

sf::Sound& AudioManager::playSound() {
    assert( currentIndexM < soundArrayM.size() );
    soundArrayM[currentIndexM].play();
    return soundArrayM[currentIndexM];
}

void AudioManager::playMusic(const char* filename) {
    musicM.openFromFile(res_dir + filename) || exitNow();
    musicM.play();
}

void AudioManager::stopMusic() {
    musicM.stop();
}

void AudioManager::resumeMusic() {
    musicM.play();
}

void AudioManager::pauseMusic() {
    musicM.pause();
}

} //end of namespace Core
