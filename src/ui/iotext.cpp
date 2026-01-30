#include "iotext.h"
#include "handRenderer.h"

void IOText::println(std::string_view msg) { m_out << msg << "\n"; }

void IOText::print(std::string_view msg) const { m_out << msg << "\n"; }

void IOText::getln(std::string& line) { std::getline(m_in, line); }

void IOText::promptln(std::string& line, std::string_view prompt)
{
    print(prompt);
    getln(line);
}

void IOText::printCards(const std::vector<std::string>& cardToPrintGrid)
{
    for (const auto& line : cardToPrintGrid)
    {
        println(line);
    }
}

void IOText::printHand(const RenderedHand& handToPrint)
{
    if (handToPrint.firstRow.has_value())
    {
        for (const auto& line : *handToPrint.firstRow)
        {
            println(line);
        }
    }

    if (handToPrint.secondRow.has_value())
    {
        print("\n");
        for (const auto& line : *handToPrint.secondRow)
        {
            println(line);
        }
    }
}