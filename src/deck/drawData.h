#ifndef DRAWDATA_H
#define DRAWDATA_H

#include <string_view>
#include <vector>

struct DrawData
{
    std::vector<std::string_view> drawnCardsNames{};
    bool reshuffled = false;
};

#endif // DRAWDATA_H