
#ifndef STATE_MACHINE_HPP_58
#define STATE_MACHINE_HPP_58

#include <memory>
#include <stack>

#include "state.hpp"

namespace Core {

typedef std::unique_ptr<GameState> GameStateRef;

class GameStateMachine {
public:
    void addState( GameStateRef newState_, bool isReplacing = true );
    void removeState();
    void processStateChanges();
    GameStateRef& getActiveState();
private:
    std::stack<GameStateRef> statesM;
    bool isReplacingM = false;
    bool isAddingM = false;
    bool isRemovingM = false;
    GameStateRef newStateM;
};

} //end of namespace Core

#endif //STATE_MACHINE_HPP_58
