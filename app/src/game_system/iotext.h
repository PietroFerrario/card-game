#ifndef IOTEXT_H
#define IOTEXT_H

#include <string_view>
#include <iostream>



class IOText{

    private:
    std::ostream& m_out;
    std::istream& m_in;

    public:

    IOText(std::ostream& out, std::istream& in): m_out{out}, m_in{in}{}

    void println(std::string_view msg);
    void print(std::string_view msg) const;

    void getln(std::string& line);
    void promptln(std::string& line, std::string_view prompt);


};

#endif //IOTEXT_H