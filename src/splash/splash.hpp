
#ifndef SPLASH_HPP_55
#define SPLASH_HPP_55

#include <SFML/Graphics.hpp>

#include "../the_includes.hpp"
#include "../core_engine/state.hpp"

namespace Core {
    struct GameData;
}

class SplashState : public Core::GameState {
public:
    explicit SplashState( Core::GameData& data_ );
    void handleInput() override;
    void update(Core::fSeconds dt) override;
    void draw( float dtRatio ) override;
    //void pause() override;
    //void resume() override;
    //void init() override;
private:
    Core::GameData& dataM;
    sf::Clock clockM;
    sf::Sprite backgroundM;
    sf::Text textM;
    Core::fSeconds timeM{};
};

#endif // SPLASH_HPP_55
