
#ifndef SNAKE_GAME_FRUIT_HPP_71
#define SNAKE_GAME_FRUIT_HPP_71

#include <SFML/Graphics.hpp>
#include "../core_engine/clock.hpp"

namespace SnakeGame
{

class Fruit : public sf::Drawable
{
public:
    sf::FloatRect getHitbox() const;
    void update(Core::fSeconds dt);
    void reset();
    void init(const sf::Texture& texture_); //should be called ASAP after construction
    Fruit();
private:
    sf::RectangleShape squareM;
    Core::fSeconds timeM{};

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;
};

} //end of namespace SnakeGame

#endif //SNAKE_GAME_FRUIT_HPP_71
