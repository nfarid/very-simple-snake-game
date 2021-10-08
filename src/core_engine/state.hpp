
#ifndef STATE_HPP_97
#define STATE_HPP_97

#include "no_copy_move.hpp"
#include "clock.hpp"

namespace Core {

class GameState : public NoCopy, public NoMove {
public:
    virtual void handleInput() = 0;
    virtual void update(fSeconds dt) = 0;
    virtual void draw( float dtRatio ) = 0;
    virtual void pause() {}
    virtual void resume() {}
    virtual void init() {}
    virtual ~GameState() = default;
};

} //end of Core namespace

#endif // STATE_HPP_97

/*
void handleInput() override;
void update(Core::fSeconds dt) override;
void draw( float dtRatio ) override;
void pause() override;
void resume() override;
void init() override;
*/
