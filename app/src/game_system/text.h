#ifndef TEXT_H
#define TEXT_H

#include <string_view>
#include <nlohmann/json.hpp>

class Text{
    public:
    Text();

    const std::string& getText(const char* key) const;

    private: 

    nlohmann::json m_data;

};

#endif