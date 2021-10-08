
#ifndef CORE_GAME_HPP_90
#define CORE_GAME_HPP_90

#include <utility>
#include "state_machine.hpp"
#include "asset_manager.hpp"
#include "input_manager.hpp"
#include "audio_manager.hpp"
#include "clock.hpp"
#include "../the_includes.hpp"

namespace Core {

struct GameData {
    GameStateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    AudioManager audio;
    Time clock;
    InputManager input{sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right};
};

class Game {
public:
    Game(const char* title);
    void run();
private:
    GameData dataM;
};

}//namespace Core

#endif // CORE_GAME_HPP_90
