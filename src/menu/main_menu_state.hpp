
#ifndef MENU_MAIN_MENU_STATE_HPP_26
#define MENU_MAIN_MENU_STATE_HPP_26

#include <SFML/Graphics.hpp>
#include "../core_engine/state.hpp"

namespace Core { struct GameData; } //end of namespace Core

namespace Menu
{

class MainMenuState : public Core::GameState
{
public:
    MainMenuState(Core::GameData& data_);
    void handleInput() override;
    void update(Core::fSeconds dt) override;
    void draw( float dtRatio ) override;
    //void pause() override;
    //void resume() override;
    //void init() override;
private:
    sf::Sprite playButtonM;
    sf::Sprite exitButtonM;
    Core::GameData& dataM;
};

} //end of namespace Menu

#endif //MENU_MAIN_MENU_STATE_HPP_26
