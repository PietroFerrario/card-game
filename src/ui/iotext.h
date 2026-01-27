#ifndef IOTEXT_H
#define IOTEXT_H

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class IOText
{

  public:
    IOText(std::ostream& out, std::istream& in) : m_out{out}, m_in{in} {}

    void println(std::string_view msg);
    void print(std::string_view msg) const;

    void getln(std::string& line);
    void promptln(std::string& line, std::string_view prompt);

    void printCard(const std::vector<std::string>& cardToPrintGrid);

  private:
    std::ostream& m_out;
    std::istream& m_in;
};

#endif // IOTEXT_H