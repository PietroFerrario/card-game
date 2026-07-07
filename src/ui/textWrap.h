#ifndef TEXTWRAP_H
#define TEXTWRAP_H

#include <string>
#include <string_view>
#include <vector>

std::vector<std::string> wrapText(std::string_view text, int maxWidth);

#endif // TEXTWRAP_H
