#include "GameStateMachine.hpp"

namespace sle {

void GameStateMachine::update() { m_currentState->update(); }

void GameStateMachine::draw() { m_currentState->draw(); }

void GameStateMachine::setState(GameStateType type) {
    for (const auto state : m_states) {
        if (state->toEnum() == type) {
            transition(state);
        }
    }
}

void GameStateMachine::registerState(ref<IGameStateMachine> &newState) { m_states.insert(newState); }

void GameStateMachine::deregisterState(GameStateType type) {
    for (const auto &state : m_states) {
        if (state->toEnum() == type)
            m_states.erase(state);
    }
}

void GameStateMachine::setWindow(ref<Window> &win) {
    for (auto state : m_states) {
        state->setWindow(win);
    }
}

void GameStateMachine::transition(const ref<IGameStateMachine> &state) { m_currentState = state; }

} // namespace sle