#ifndef EVENTDATA_H
#define EVENTDATA_H

#include "matchEventData.h"
#include "storyEventData.h"

#include <variant>

using EventData = std::variant<MatchEventData, StoryEventData>;

#endif // EVENTDATA_H
