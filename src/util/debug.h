#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <iostream>

// Debug logic for debug builds

#ifdef CARDGAME_DEBUG

#define DEBUG_LOG(msg)                                                                             \
    do                                                                                             \
    {                                                                                              \
        std::cerr << "[DEBUG] " << msg << std::endl;                                               \
    } while (0)

#else

#define DEBUG_LOG(msg)                                                                             \
    do                                                                                             \
    {                                                                                              \
        static std::ofstream logFile("cardgame_log.txt", std::ios::trunc);                         \
        if (logFile.is_open())                                                                     \
        {                                                                                          \
            logFile << "[LOG] " << __FILE__ << ":" << __LINE__ << " " << msg << std::endl;         \
        }                                                                                          \
    } while (0)

#endif

#endif // DEBUG_H