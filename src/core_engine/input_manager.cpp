
#include "input_manager.hpp"
#include <cassert>

namespace Core {

bool InputManager::isSpriteClicked( sf::Sprite object, sf::Mouse::Button button,
                            const sf::RenderWindow& window) const {
    if( sf::Mouse::isButtonPressed( button ) ) {
        sf::IntRect tempRect = static_cast<sf::IntRect>(object.getGlobalBounds() );
        if( tempRect.contains( sf::Mouse::getPosition(window) )   )
            return true;
    }
    return false;
}

sf::Vector2i InputManager::getMousePosition( const sf::RenderWindow& window) const {
    return sf::Mouse::getPosition(window);
}

bool InputManager::checkInput(InputType input) const {
    switch(input) {

    case up:
        return sf::Keyboard::isKeyPressed(playerInputM.upInput);
    break;

    case down:
        return sf::Keyboard::isKeyPressed(playerInputM.downInput);
    break;

    case left:
        return sf::Keyboard::isKeyPressed(playerInputM.leftInput);
    break;

    case right:
        return sf::Keyboard::isKeyPressed(playerInputM.rightInput);
    break;
    }
    return 0;
}

InputManager::InputManager( std::initializer_list<sf::Keyboard::Key> keys )
{
    auto iter = keys.begin();
    playerInputM.upInput = *iter++;
    playerInputM.downInput = *iter++;
    playerInputM.leftInput = *iter++;
    playerInputM.rightInput = *iter++;
    assert( iter == keys.end() );
}

} //namespace Core
