
#include "../menu/main_menu_state.hpp"
#include "../core_engine/game.hpp"
#include "splash.hpp"

namespace {
    constexpr auto splashShowTime = Core::fSeconds{0.8f};
}

SplashState::SplashState( Core::GameData& data_ ) :
    dataM{data_} {
}

void SplashState::handleInput() {
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
}

void SplashState::update(Core::fSeconds dt) {
    //Waiting for a set time
    timeM += dt;
    if( timeM > splashShowTime ) {
        #ifndef NDEBUG
            //std::cout<<"Go to main state!\n";
        #endif // NDEBUG

        //switch to the main menu
        dataM.machine.addState( std::make_unique<Menu::MainMenuState>(dataM),true);
    }
}

void SplashState::draw( float) {
    dataM.window.clear( sf::Color::Blue );
    dataM.window.display();
}

