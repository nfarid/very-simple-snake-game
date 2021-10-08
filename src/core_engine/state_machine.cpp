
#include "state_machine.hpp"

namespace Core {

void GameStateMachine::addState( GameStateRef newState_, bool replacing ) {
    isReplacingM = replacing;
    isAddingM = true;
    newStateM = std::move(newState_);
}

void GameStateMachine::removeState() {
    isRemovingM = true;
}

void GameStateMachine::processStateChanges() {
    if( isRemovingM && !statesM.empty() ) {
        statesM.pop();
        if( !statesM.empty() )
            statesM.top()->resume();
        isRemovingM = false;
    }
    if( isAddingM ) {
        if( !statesM.empty() ) {
            if( isReplacingM )
                statesM.pop();
            else
                statesM.top()->pause();
        }
        statesM.push( std::move(newStateM) );
        statesM.top()->init();
        isReplacingM = false;
        isAddingM = false;
    }
}

GameStateRef& GameStateMachine::getActiveState() {
    return statesM.top();
}

} //end of namespace Core
