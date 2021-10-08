
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "core_engine/game.hpp"
#include "the_includes.hpp"

int main()
{
    Core::Game game{"Snake"};
    game.run();

    return 0;
}
