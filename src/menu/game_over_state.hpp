
#ifndef MENU_GAME_OVER_STATE_HPP_77
#define MENU_GAME_OVER_STATE_HPP_77

#include "../core_engine/state.hpp"
#include <SFML/Graphics.hpp>

namespace Core { struct GameData; } //end of namespace Core

namespace Menu
{

class GameOverState : public Core::GameState
{
public:
    void handleInput() override;
    void update(Core::fSeconds dt) override;
    void draw( float dtRatio ) override;
    //void pause() override;
    //void resume() override;
    //void init() override;
    GameOverState(int score_, Core::GameData& data_);
private:
    sf::Text messageM;
    sf::Sprite retryButtonM;
    Core::GameData& dataM;
};

} //end of namespace Menu

#endif // MENU_GAME_OVER_STATE_HPP_77
