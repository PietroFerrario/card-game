#ifndef NODEDATA_H
#define NODEDATA_H

#include "eventData.h"

#include <string>
#include <vector>

struct EventNodeData
{
    std::string id;
    std::vector<std::string> next;
    std::string previewDescription;
    EventData event;

    int layer{0};
    int column{0};
};

#endif // NODEDATA_H