#ifndef TEXT_H
#define TEXT_H

#include <nlohmann/json.hpp>
#include <string_view>

/**
 * @brief Lightweight text lookup service backed by a JSON file.
 *
 * Text loads a JSON document at construction time and provides read-only
 * access to string values by key. It is intended for externalized game text
 * such as UI labels, messages, or descriptions.
 *
 * The underlying data is immutable after construction.
 */
class Text
{
  public:
    /**
     * @brief Loads text data from the JSON source.
     *
     * The JSON file is parsed during construction and stored internally.
     */
    Text();

    /**
     * @brief Returns the text associated with the given key.
     *
     * @param key Null-terminated string key used to look up the text.
     * @return Reference to the stored string value.
     *
     * @throws If the key is not present in the underlying JSON data.
     */
    const std::string& getText(const char* key) const;

  private:
    nlohmann::json m_data{}; ///< Parsed JSON document containing text entries.
};

#endif