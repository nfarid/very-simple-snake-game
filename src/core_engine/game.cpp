
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include "../splash/splash.hpp"
#include "../util/get_dir.hpp"

#define BENCHMARK(MESSAGE,CODE) do{ std::chrono::steady_clock::time_point tp1,tp2; \
    tp1 = std::chrono::steady_clock::now(); CODE; tp2 = std::chrono::steady_clock::now();\
    std::cout<<"Time taken for "<<MESSAGE<<" is: "<<std::chrono::duration_cast<std::chrono::microseconds>(tp2-tp1).count()<<"us \n";\
    }while(0)


namespace {
    auto upperFrameTime = Core::microseconds{250000}; //2.5e5us or 0.25s
    //limit the frame time
}

namespace Core {

Game::Game(const char* title) {
    dataM.window.create( sf::VideoMode{windowSizeC.x,windowSizeC.y}, title
                        /*, sf::Style::Close | sf::Style::Titlebar*/ );

    #ifdef NDEBUG
        sf::Image icon;
        icon.loadFromFile(Util::get_resource_dir() + "images/main_icon.png");
        dataM.window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
    #endif // NDEBUG
}

void Game::run() {
    dataM.machine.addState( std::make_unique<SplashState>(dataM) );
    using namespace std::chrono;
    using namespace std;

    microseconds currentTime = dataM.clock.getElapsedTime();
    microseconds newTime;
    microseconds accumulator{};
    microseconds actualFrameTime;
    float interpolation;
    while( dataM.window.isOpen() ) {
        dataM.machine.processStateChanges();
        newTime = dataM.clock.getElapsedTime();
        actualFrameTime = newTime - currentTime;
        actualFrameTime = ( actualFrameTime <= upperFrameTime ? actualFrameTime : upperFrameTime);
        currentTime = newTime;
        accumulator += actualFrameTime;
        while( accumulator >= idealFrameTime ) {
            accumulator -= idealFrameTime;
            dataM.machine.getActiveState()->handleInput();
            dataM.machine.getActiveState()->update( duration_cast<fSeconds>(idealFrameTime) );
        }
        interpolation = accumulator / idealFrameTime;
        dataM.machine.getActiveState()->draw(interpolation);
    }
}

} //namespace Core
