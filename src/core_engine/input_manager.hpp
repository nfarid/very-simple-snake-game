
#ifndef INPUT_MANAGER_HPP_21
#define INPUT_MANAGER_HPP_21

#include <SFML/Graphics.hpp>

namespace Core {

enum InputType {up,down,left,right};

class InputManager {
public:
    bool isSpriteClicked( sf::Sprite object, sf::Mouse::Button button,
                         const sf::RenderWindow& window) const;

    sf::Vector2i getMousePosition( const sf::RenderWindow& window) const;

    bool checkInput(InputType input) const;
    InputManager( std::initializer_list<sf::Keyboard::Key> keys );
private:
    struct PlayerInput {
    sf::Keyboard::Key upInput;
    sf::Keyboard::Key downInput;
    sf::Keyboard::Key leftInput;
    sf::Keyboard::Key rightInput;
    } playerInputM;
};

}

#endif // INPUT_MANAGER_HPP_21
