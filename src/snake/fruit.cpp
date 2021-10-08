
#include "fruit.hpp"
#include <random>

namespace {

std::default_random_engine engR;

const sf::Vector2f fruitSize = {blockSize,blockSize};

std::uniform_int_distribution<int> distH{ 0, totalSectionN.x};
std::uniform_int_distribution<int> distV{ 0, totalSectionN.y};

} //end of anonymous namespace

namespace SnakeGame
{

sf::FloatRect Fruit::getHitbox() const
{
    return squareM.getGlobalBounds();
}

void Fruit::update(Core::fSeconds dt)
{
    if(Core::atTimeInterval(timeM, 0.5_fs) ) //update animations every 0.5s
    {
        auto texRect = squareM.getTextureRect();
        texRect.top = ( texRect.top + 32 )%64;
        squareM.setTextureRect(texRect);
    }
    timeM += dt;
}

void Fruit::reset()
{
    const int posX = fruitSize.x * distH(engR) + gameBoundary.left;
    const int posY = fruitSize.y * distV(engR) + gameBoundary.top;
    squareM.setPosition(posX, posY);
    //std::cout<<"Fruit position: "<<posX<<','<<posY<<'\n';
}

void Fruit::init(const sf::Texture& texture_)
{
    squareM.setTexture(&texture_);
    squareM.setTextureRect( {0,0,32,32} );
}

Fruit::Fruit() :
    squareM{fruitSize}
{
    engR.seed( Core::seedNumber() );
    //squareM.setFillColor( sf::Color::Red );
    reset();
}

void Fruit::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(squareM);
}

} //end of namespace SnakeGame
