#pragma once

#include "slog"
#define SLE_ASSERT(cond, msg)                                                                                          \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            err("Assertion failed: {}", msg);                                                                          \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (0)
