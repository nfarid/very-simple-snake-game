
#ifndef SNAKE_GAME_SNAKE_HPP_35
#define SNAKE_GAME_SNAKE_HPP_35

#include<SFML/Graphics.hpp>
#include <array>
#include "dynamic_array.hpp"
#include "../maths/speed.hpp"

namespace Core { class InputManager; } //end of namespace Core

namespace SnakeGame
{

class Snake : public sf::Drawable
{
public:
    sf::FloatRect getHitbox() const;
    bool checkSelfCollision() const;
    void checkInput();
    void update( Core::fSeconds dt);
    void getFruit();
    void init(const sf::Texture& texture_); //should be called ASAP after construction
    explicit Snake(Core::InputManager& input_);

private:
    typedef std::array<sf::Vertex,quadVertexN> Segment; //would have made a struct but unreasonable padding may occur
    Container::DynamicArray<Segment> segmentsM;
    Maths::Velocity velocityM;
    Core::InputManager& inputM;
    const sf::Texture* textureM;
    bool gotFruitM = false;
    enum Direction : char {right = '\0', down, left, up};
    byte directionM{};
    byte oldDirectionM{};
    byte animationFrameM{};
    bool alreadyInputM = false;


    void draw(sf::RenderTarget& target, sf::RenderStates) const override;
};

} //end of namespace SnakeGame

#endif //SNAKE_GAME_SNAKE_HPP_35
