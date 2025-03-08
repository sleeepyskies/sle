#include "GameStateMachine.hpp"

namespace sle {

void GameStateMachine::update(const InputData &inputData) {
    assert(m_currentState);
    m_currentState->update(inputData);
}

void GameStateMachine::draw() {
    assert(m_currentState);
    m_currentState->draw();
}

void GameStateMachine::stateChange() {
    assert(m_currentState);
    GameStateType nextState = m_currentState->transition();
    if (m_currentState->toEnum() == nextState)
        return;
    for (auto &state : m_states) {
        if (state->toEnum() == nextState) {
            transition(state);
        }
    }
}

void GameStateMachine::setState(GameStateType type) {
    for (const auto state : m_states) {
        if (state->toEnum() == type) {
            transition(state);
        }
    }
}

void GameStateMachine::registerState(ref<IGameState> newState) {
    if (m_states.size() == 0)
        m_currentState = newState;
    m_states.insert(newState);
}

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

void GameStateMachine::transition(const ref<IGameState> &state) { m_currentState = state; }

} // namespace sle