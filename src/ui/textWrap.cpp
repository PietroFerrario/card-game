#include "textWrap.h"

std::vector<std::string> wrapText(std::string_view text, int maxWidth)
{
    std::vector<std::string> lines;
    if (text.length() <= static_cast<size_t>(maxWidth))
    {
        lines.emplace_back(text);
        return lines;
    }

    std::string currentWord;
    lines.emplace_back();

    auto commitWord = [&](std::string_view word)
    {
        if (word.empty())
            return;

        size_t charNeeded{lines.back().empty() ? word.length()
                                               : word.length() + lines.back().length() + 1};

        if (charNeeded <= static_cast<size_t>(maxWidth))
        {
            if (!lines.back().empty())
                lines.back().push_back(' ');
            lines.back().append(word);
        }
        else
        {
            lines.emplace_back(word);
        }
    };

    for (const auto c : text)
    {
        if (c != ' ')
            currentWord += c;
        else
        {
            commitWord(currentWord);
            currentWord.clear();
        }
    }
    commitWord(currentWord);

    return lines;
}
