#ifndef CARDDISPOSALMODE_H
#define CARDDISPOSALMODE_H

#include <string_view>
#include <unordered_map>

enum class CardDisposalMode
{
    Discard,
    Destroy,
    ExhaustUntilEndOfMatch
};

namespace card
{
inline const std::unordered_map<std::string_view, CardDisposalMode> cardDisposalModeMap{
    {
        "discard",
        CardDisposalMode::Discard,
    },
    {
        "destroy",
        CardDisposalMode::Destroy,
    },
    {
        "exhaustUntilEndOfMatch",
        CardDisposalMode::ExhaustUntilEndOfMatch,
    }};
}

#endif // CARDDISPOSALMODE_H
