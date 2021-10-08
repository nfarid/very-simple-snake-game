
#include "game_over_state.hpp"
#include <string>
#include "../core_engine/game.hpp"
#include "../snake/main_state.hpp"

using namespace std::string_literals;

namespace {

const sf::IntRect idleFrame = {0,0,128,128};
const sf::IntRect hoverFrame = {0,128,128,128};

inline bool isHover(const sf::Sprite& object, const sf::RenderWindow& window) {
    return object.getGlobalBounds().contains( window.mapPixelToCoords(sf::Mouse::getPosition(window) )  );
}

}

namespace Menu
{

void GameOverState::handleInput()
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

    if( isHover(retryButtonM, dataM.window) ) {
        retryButtonM.setTextureRect(hoverFrame);
        if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            dataM.machine.addState( std::make_unique<SnakeGame::MainState>(dataM),true );
    }else
        retryButtonM.setTextureRect(idleFrame);
}

void GameOverState::update(Core::fSeconds /*dt*/)
{

}

void GameOverState::draw( float /*dtRatio*/ )
{
    dataM.window.clear();
    dataM.window.draw(messageM);
    dataM.window.draw(retryButtonM);
    dataM.window.display();
}

GameOverState::GameOverState(int score_, Core::GameData& data_) :
    dataM{data_}
{
    dataM.assets.loadFont("squares","fonts/squares_bold_free.otf");
    messageM.setFont( dataM.assets.getFont("squares") );
    messageM.setString("Game over, your score is "s+ std::to_string(score_) +" !"s);
    auto rect_ = messageM.getLocalBounds();
    messageM.setPosition(theMiddle.x -rect_.width/2.0f ,windowSizeC.y/3.0f - rect_.height/2.0f);

    dataM.assets.loadTexture("retry","images/retry_button.png");
    retryButtonM.setTexture( dataM.assets.getTexture("retry") );
    rect_ = retryButtonM.getLocalBounds();
    retryButtonM.setPosition( theMiddle.x -rect_.width/2.0f, 2*windowSizeC.y/3.0f - rect_.height/2.0f);
}

} //end of namespace Menu
