
#include "../menu/game_over_state.hpp"
#include "../core_engine/game.hpp"
#include "main_state.hpp"

namespace SnakeGame
{

void MainState::handleInput()
{
    sf::Event event;
    while( dataM.window.pollEvent(event) ) {
        switch(event.type) {

        case sf::Event::LostFocus:
            dataM.clock.stop();
            while(dataM.window.waitEvent(event) ) {
                if(event.type == sf::Event::GainedFocus) {
                    dataM.clock.resume();
                    break;
                }
            }
        break;

        case sf::Event::Closed:
            dataM.window.close();
        break;

        default:
        break;
        }
    }

    if( Core::atTimeInterval(timeM, snakeUpdateInterval) )
        snakeM.checkInput();
}

void MainState::update(Core::fSeconds dt)
{
    fruitM.update(dt);
    if( Core::atTimeInterval(timeM, snakeUpdateInterval) )
    {
        snakeM.update(dt);

        if( snakeM.getHitbox().intersects( fruitM.getHitbox() ) ) {
            fruitM.reset();
            snakeM.getFruit();
            dataM.audio.playSound( dataM.assets.getBuffer("ping") );
            //std::cout<<"Score is: "<<scoreM<<'\n';
            ++scoreM;
            snakeUpdateInterval /= 1.01;

        }

        if( snakeM.checkSelfCollision() )
        {
            //std::cout<<"SELF COLLISION!\n";
            dataM.machine.addState( std::make_unique<Menu::GameOverState>(scoreM,dataM),true );
        }
    }

    timeM += dt;
}

void MainState::draw( float )
{
    dataM.window.clear();
    dataM.window.draw(backgroundM);
    dataM.window.draw(snakeM);
    dataM.window.draw(fruitM);
    dataM.window.display();
}

MainState::MainState(Core::GameData& data_) :
    snakeM{ data_.input },
    dataM{data_}
{
    dataM.assets.loadBuffer("ping","sounds/ping.wav");
    dataM.assets.loadTexture("snake","images/snake.png");
    dataM.assets.loadTexture("fruit","images/fruit.png");
    dataM.assets.loadTexture("background","images/background.png");
    snakeM.init( dataM.assets.getTexture("snake") );
    fruitM.init( dataM.assets.getTexture("fruit") );
    backgroundM.setTexture( dataM.assets.getTexture("background") );
}

}
