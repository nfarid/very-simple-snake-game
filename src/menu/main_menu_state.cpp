
#include "../core_engine/game.hpp"
#include "../snake/main_state.hpp"
#include "main_menu_state.hpp"

namespace {

//checks if the mouse is currently above the sprite
inline bool isHover(const sf::Sprite& object, const sf::RenderWindow& window) {
    return object.getGlobalBounds().contains( window.mapPixelToCoords(sf::Mouse::getPosition(window) )  );
}

const sf::IntRect idleFrame = {0,0,128,128};
const sf::IntRect hoverFrame = {0,128,128,128};

} //end of anonymous namespace

namespace Menu
{

void MainMenuState::handleInput()
{
    sf::Event event;
    while( dataM.window.pollEvent(event) )
    {
        switch(event.type)
        {
        case sf::Event::LostFocus:
            dataM.clock.stop();
            while(dataM.window.waitEvent(event) )
            {
                if(event.type == sf::Event::GainedFocus)
                {
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

    if( isHover(playButtonM, dataM.window) ) {
        playButtonM.setTextureRect( hoverFrame );
        if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            dataM.machine.addState( std::make_unique<SnakeGame::MainState>(dataM),true );
    }else
        playButtonM.setTextureRect( idleFrame );

    if( isHover(exitButtonM, dataM.window) ) {
        exitButtonM.setTextureRect( hoverFrame );
        if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            dataM.window.close();
    }else
        exitButtonM.setTextureRect( idleFrame );
}

void MainMenuState::update(Core::fSeconds)
{
    //0;
}

void MainMenuState::draw( float )
{
    dataM.window.clear();
    dataM.window.draw(playButtonM);
    dataM.window.draw(exitButtonM);
    dataM.window.display();
}

MainMenuState::MainMenuState(Core::GameData& data_) :
    dataM{data_}
{
    dataM.assets.loadTexture("play","images/play_button.png");
    dataM.assets.loadTexture("exit","images/exit_button.png");

    playButtonM = sf::Sprite{ dataM.assets.getTexture("play"), idleFrame};
    playButtonM.setPosition( windowSizeC.x/3.0f - idleFrame.width/2, windowSizeC.y/2.0f - idleFrame.height/2 );

    exitButtonM = sf::Sprite{ dataM.assets.getTexture("exit"), idleFrame };
    exitButtonM.setPosition( 2.0f*windowSizeC.x/3.0f - idleFrame.width/2, windowSizeC.y/2.0f - idleFrame.height/2 );
}

} //end of namespace Menu
