#include "iotext.h"


void IOText::println(std::string_view msg){
    m_out << msg <<"\n";
}

void IOText::print(std::string_view msg){
    m_out << msg;
}

void IOText::getln(std::string& line){
    std::getline(m_in, line);
}

void IOText::promptln(std::string& line, std::string_view prompt){
    print(prompt);
    getln(line);
}