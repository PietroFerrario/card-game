#include "text.h"

#include <fstream>


using json = nlohmann::json;

Text::Text(){
    // Add throwable exceptions
    std::ifstream f("data/text.json");
    m_data = json::parse(f);
}

const std::string& Text::getText(const char* key) const{

    const auto& textRef = m_data.at(key).get_ref<const std::string &>();
    return textRef;
}