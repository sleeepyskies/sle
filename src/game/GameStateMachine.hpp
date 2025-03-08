#pragma once

#include "../graphics/Window.hpp"
#include "types.hpp"
#include <unordered_set>

namespace sle {

/**
 * @brief This enum is used to indicate as a return value from the transition method, what
 * GameState should be active next. Be sure to also add new enums here when adding new @ref GameState.
 */
enum class GameStateType { Game, MapEditor };

/**
 * @brief The GameState Interface is used for handling the active state of the engine. Any class
 * using this must implement its methods.
 */
class IGameStateMachine {
public:
    /// @brief Make sure any classes that implement this have a destructor.
    virtual ~IGameStateMachine() = default;

    /// @brief This function should update the current GameStates state.
    virtual void update() = 0;

    /// @brief This function should be used to draw/render the current GameState.
    virtual void draw() = 0;

    /// @brief Returns the current GameState as its corresponding enum.
    virtual GameStateType toEnum() = 0;

    /// @brief Updates the states window.
    void setWindow(ref<Window> &win) { m_window = win; }

    /**
     * @brief Indicates to @ref Engine what the next state should be. Since transitions may happen
     * either during @ref update() or @ref input(), a separate function has been provided which is
     * to be called after all other functions have been called in a tick.
     */
    virtual GameStateType transition() = 0;
private:
    /// @brief The window that should be rendered to.
    ref<Window> m_window;
};

class GameStateMachine {
public:
    GameStateMachine() = default;
    ~GameStateMachine() = default;

    /// @brief Handles updating the current state.
    void update();
    /// @brief Handles rendering/drawing the current state to the screen.
    void draw();

    /// @brief Registers a new state into the state machine.
    void registerState(ref<IGameStateMachine> &newState);
    /// @brief De-Registers a state from the state machine, if it is currently present.
    void deregisterState(GameStateType type);

    /// @brief Will force set the current state to the given state, if present. May cause unforeseen issues!
    void setState(GameStateType type);

    /// @brief Updates all states window member.
    void setWindow(ref<Window> &win);

private:
    /// @brief The active @ref IGameState of the engine, ie where all functions are called for this tick.
    ref<IGameStateMachine> m_currentState;
    /// @brief A set containing all registered states. Theses are all inactive and will not be used this tick.
    std::unordered_set<ref<IGameStateMachine>> m_states;

    /// @brief Changes the state to the given state.
    void transition(const ref<IGameStateMachine> &state);
};
} // namespace sle
