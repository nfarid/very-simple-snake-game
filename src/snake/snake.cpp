
#include "../core_engine/input_manager.hpp"
#include "snake.hpp"
#include "../the_includes.hpp"
#include <memory>

//Quite messy code, Snake starts at line 100
namespace {
typedef std::array<sf::Vertex,quadVertexN> Segment;

const sf::Vector2f segmentSize = {32.0f,32.0f};

constexpr auto snakeSpeed =  Maths::Speed{ idealFPS * blockSize}; //pixels per second

const sf::FloatRect snakeHead1 = {0,0,32,32};
const sf::FloatRect snakeHead2 = {32,0,32,32};
const sf::FloatRect snakeSteadyBody = {0,32,32,32};
const sf::FloatRect snakeTurnBody = {32,32,32,32};

inline void setSegmentTexture(Segment& segment, sf::FloatRect texRect) {
    segment[0].texCoords = sf::Vector2f{texRect.left, texRect.top};
    segment[1].texCoords = sf::Vector2f{texRect.left + texRect.width, texRect.top};
    segment[2].texCoords = sf::Vector2f{texRect.left + texRect.width, texRect.top + texRect.height};
    segment[3].texCoords = sf::Vector2f{texRect.left, texRect.top + texRect.height};
    segment[4].texCoords = segment[0].texCoords;
    segment[5].texCoords = segment[2].texCoords;
}

void setSegment(Segment& segment, const sf::Vector2f pos, const sf::Vector2f size) {
    segment[0].position = pos;
    segment[1].position = sf::Vector2f{ pos.x+size.x, pos.y };
    segment[2].position = pos + size;
    segment[3].position = sf::Vector2f{ pos.x, pos.y+size.y };
    segment[4] = segment[0];
    segment[5] = segment[2];
}

inline void setSegmentPosition(Segment& segment, sf::Vector2f pos) {
    const auto size = segment[2].position - segment[0].position;
    setSegment(segment,pos,size);
}

enum : char {right = '\0', down, left, up};
inline void rotateSegment(Segment& segment, ptrdiff_t n)
{
    const auto pos = segment[0].texCoords;
    const auto fullSize = segment[2].position - segment[0].position;
    const auto halfSize = 0.5f * fullSize;
    const auto middle = pos + halfSize;
    sf::FloatRect currentTex;
    switch(n)
    {
    case right:     //assuming default Texture is going right
        currentTex = {middle.x-halfSize.x, middle.y-halfSize.y, fullSize.x, fullSize.y};
        //std::cout<<"right\n";
    break;

    case down:
        currentTex = {middle.x-halfSize.x, middle.y+halfSize.y, fullSize.x, -fullSize.y};
        //std::cout<<"down\n";
    break;

    case left:
        currentTex = {middle.x+halfSize.x, middle.y+halfSize.y, -fullSize.x, -fullSize.y};
        //std::cout<<"left\n";
    break;

    case up:
        currentTex = {middle.x+halfSize.x, middle.y-halfSize.y, -fullSize.x, fullSize.y} ;
        //std::cout<<"up\n";
    break;
    }

    segment[0].texCoords = {currentTex.left, currentTex.top};
    segment[1].texCoords = {currentTex.left + currentTex.width, currentTex.top};
    segment[2].texCoords = {currentTex.left + currentTex.width, currentTex.top + currentTex.height};
    segment[3].texCoords = {currentTex.left, currentTex.top + currentTex.height};
    if( n == down || n==up )
        std::swap( segment[1].texCoords, segment[3].texCoords); //for the rotation
    segment[4].texCoords = segment[0].texCoords;
    segment[5].texCoords = segment[2].texCoords;

    /*
    std::cout<<"Texture Coords: \n";
    std::cout<<segment[0].texCoords.x<<" , "<<segment[0].texCoords.y<<'\n';
    std::cout<<segment[1].texCoords.x<<" , "<<segment[1].texCoords.y<<'\n';
    std::cout<<segment[2].texCoords.x<<" , "<<segment[2].texCoords.y<<'\n';
    std::cout<<segment[3].texCoords.x<<" , "<<segment[3].texCoords.y<<"\n\n";
    */
    /*
    auto middleIter = segment.begin() + (n+4)%4;
    assert( segment.begin() <= middleIter );
    assert( segment.end() > middleIter );
    auto pos = segment[0].position;
    std::rotate( segment.begin(), middleIter, segment.begin()+4 );
    setSegmentPosition(segment,pos);
    */
}

} //end of anonymous namespace



namespace SnakeGame
{

sf::FloatRect Snake::getHitbox() const
{
    const auto pos = segmentsM.front()[0].position;
    return { pos.x, pos.y, segmentSize.x, segmentSize.y };
    //return segmentsM.front().getGlobalBounds();
}

void Snake::checkInput()
{

    if( Maths::nearlyEqual(velocityM.y,0_pps) )
    {
        if( inputM.checkInput(Core::up) ) {
            velocityM = { 0_pps, -snakeSpeed };
            directionM = up;
            alreadyInputM = true;
        }else if( inputM.checkInput(Core::down) ) {
            velocityM = {0_pps, snakeSpeed };
            directionM = down;
            alreadyInputM = true;
        }
    }

    if(!alreadyInputM && Maths::nearlyEqual(velocityM.x, 0_pps) )
    {
        if( inputM.checkInput(Core::left) ) {
            velocityM = { -snakeSpeed, 0_pps };
            directionM = left;
            alreadyInputM = true;
        }else if( inputM.checkInput(Core::right) ) {
            velocityM = { snakeSpeed, 0_pps };
            directionM = right;
            alreadyInputM = true;
        }
    }

    //std::cout<<"Velocity: "<<velocityM.x.count()<<" , "<<velocityM.y.count()<<'\n';
}

void Snake::getFruit()
{
    gotFruitM = true;
}

bool Snake::checkSelfCollision() const
{
    const auto frontPos = segmentsM.front()[0].position;

    for(size_t i=1; i<segmentsM.size(); ++i)
    {
        if( Maths::nearlyEqual(frontPos, segmentsM[i][0].position) )
            return true;
    }
    return false;
}

void Snake::update( Core::fSeconds dt)
{
    alreadyInputM = false;
    if( directionM == oldDirectionM ) {
        setSegmentTexture(segmentsM.front(), snakeSteadyBody);
        rotateSegment(segmentsM.front(),directionM);
    }else {
        setSegmentTexture(segmentsM.front(), snakeTurnBody);

        auto temp_ = directionM;
        if( (oldDirectionM + 1) % 4 == directionM ) {  //if the snake is moving clockwise
            std::swap( oldDirectionM, directionM );
            directionM = (directionM+2)%4;
            oldDirectionM = (oldDirectionM+2)%4;
            for(auto& vertex : segmentsM.front() )
                vertex.texCoords += {32,0};
        }

        if( directionM - oldDirectionM == -1 ) {
            if( directionM + oldDirectionM == 1 )
                rotateSegment(segmentsM.front(),0); //going from down to right
            else if( directionM + oldDirectionM == 3 )
                rotateSegment(segmentsM.front(),1); //going from left to down
            else
                rotateSegment(segmentsM.front(),2); //going from up to left
        }else
            rotateSegment(segmentsM.front(),3); //going from right to up

        directionM = temp_;
    }
    auto newPos = static_cast<sf::Vector2i>(segmentsM.front()[0].position + velocityM * dt ) + sf::Vector2i{windowSizeC.x, windowSizeC.y};
    newPos = sf::Vector2i(newPos.x%windowSizeC.x, newPos.y%windowSizeC.y);

    segmentsM.push_forward( segmentsM.back() );
    //auto newPos = segmentsM.front()[0].position + velocityM * dt;
    setSegmentPosition( segmentsM.front(), static_cast<sf::Vector2f>(newPos) );

    sf::FloatRect snakeHead;
    if(animationFrameM == 1) {
        snakeHead = snakeHead1;
        animationFrameM = 2;
    }else if(animationFrameM == 2) {
        snakeHead = snakeHead2;
        animationFrameM = 1;
    }

    setSegmentTexture(segmentsM.front(), snakeHead);
    rotateSegment(segmentsM.front(), directionM );
    if( gotFruitM )
        gotFruitM = false;
    else {
        segmentsM.pop_back();
        if( segmentsM.size() > 1 ) {
            for(auto& vertex : segmentsM.back() )
                vertex.texCoords += {0,32};
        }
    }
    //segmentsM.front().move( velocityM * dt );

    //const auto newPos = static_cast<sf::Vector2i>(segmentsM.front().getPosition() ) + sf::Vector2i{windowSizeC.x, windowSizeC.y};
    //segmentsM.front().setPosition( newPos.x%windowSizeC.x, newPos.y%windowSizeC.y );

    oldDirectionM = directionM;
}

void Snake::init(const sf::Texture& texture_)
{
    textureM = &texture_;
    setSegmentTexture(segmentsM.front(), snakeHead1);
    animationFrameM = 1;
}

Snake::Snake(Core::InputManager& input_) :
    segmentsM(1),
    inputM{input_}
{
    const sf::Vector2f middlePos = {totalSectionN.x/2 * blockSize, totalSectionN.y/2 * blockSize};
    setSegment( segmentsM.front(), middlePos, segmentSize );
    //auto& segment = segmentsM.front();
    //segment.setSize( segmentSize );
    //segment.setFillColor( sf::Color::Green );
    //segment.setPosition( totalSectionN.x/2 * blockSize, totalSectionN.y/2 * blockSize );
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    const sf::Vertex* vertexPtr =  segmentsM.front().data();
    const size_t vertexCount = segmentsM.size() * quadVertexN;
    target.draw(vertexPtr,vertexCount,sf::Triangles,textureM);
}

} //end of namespace SnakeGame
