
#ifndef SNAKE_GAME_MAIN_STATE_HPP_48
#define SNAKE_GAME_MAIN_STATE_HPP_48

#include "snake.hpp"
#include "fruit.hpp"
#include "../core_engine/state.hpp"

namespace Core {struct GameData;} //end of namespace Core

namespace SnakeGame
{

class MainState final : public Core::GameState
{
public:
    void handleInput() override;
    void update(Core::fSeconds dt) override;
    void draw( float dtRatio ) override;
    //void pause() override;
    //void resume() override;
    //void init() override;
    explicit MainState(Core::GameData& data_);

private:
    Snake snakeM;
    Fruit fruitM;
    sf::Sprite backgroundM;
    int scoreM = 0;
    Core::fSeconds timeM = 0.0_fs;  //current time of this state
    Core::fSeconds snakeUpdateInterval = 0.125_fs; //snake will update 8 times per second
    Core::GameData& dataM;
};

} //end of namespace SnakeGame

#endif //SNAKE_GAME_MAIN_STATE_HPP_48
