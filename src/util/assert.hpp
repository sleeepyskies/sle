#pragma once

#include "slog.hpp"

#define sle_assert(cond, msg)                                                                                          \
    if (!cond) {                                                                                                       \
        err("Assertion failed: {}", msg);                                                                              \
        std::abort();                                                                                                  \
    }                                                                                                                  \
    \