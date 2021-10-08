
#ifndef AUDIO_MANAGER_HPP_9
#define AUDIO_MANAGER_HPP_9

#include <SFML/Audio.hpp>
#include <array>

namespace Core {

class AudioManager {
public:
    void playMusic(const char* filename);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void playSound(const sf::SoundBuffer& buffer_, float volume=75);
    sf::Sound& playSound();

private:
    std::array<sf::Sound,5> soundArrayM;
    sf::Music musicM;
    size_t currentIndexM = 0;
};

} //end of namespace Core

#endif // AUDIO_MANAGER_HPP_9
