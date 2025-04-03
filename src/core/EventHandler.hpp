#pragma once

#include "math.hpp"
#include "slog.hpp"
#include "types.hpp"
#include <SDL_events.h>
#include <queue>
#include "secs/util/InputData.hpp"

namespace sle {

/**
 * @brief This struct is for any data that the @ref Engine may need to know.
 */
struct EngineData {
    bool quit = false;
};

/**
 * The EventManager is responsible for polling all SDL events
 */
class EventHandler {
public:
    EventHandler();
    ~EventHandler() = default;

    /**
     * @brief This reads in all SDL_Events and updates its state accordingly. Will return false
     * if the @ref Window should be closed and true otherwise.
     */
    void pollEvents();

    /// @brief Returns a struct of all event data that is needed by the current state.
    const secs::InputData &inputData() const { return m_inputData; }

    /// @brief Returns a struct of all engine relevant data.
    const EngineData &engineData() const { return m_engineData; }

private:
    /// @brief The event used for polling events. Prevents creating a new event each tick.
    SDL_Event m_event;
    /// @brief The struct used to store any data about direct user input for the current state.
    secs::InputData m_inputData;
    /// @brief The struct used to store any data for the engine (such as SDL_Quit).
    EngineData m_engineData;
};

} // namespace sle
