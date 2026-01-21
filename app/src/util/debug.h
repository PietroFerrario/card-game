#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

// Debug logic for debug builds

#ifdef CARDGAME_DEBUG

#define DEBUG_LOG(msg)                               \
    do                                               \
    {                                                \
        std::cerr << "[DEBUG] " << msg << std::endl; \
    } while (0)

#else

#define DEBUG_LOG(msg) \
    do                 \
    {                  \
    } while (0)

#endif

#endif // DEBUG_H