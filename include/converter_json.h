#ifndef SEARCH_ENGINE_CONVERTER_JSON_H
#define SEARCH_ENGINE_CONVERTER_JSON_H

#include "nlohmann/json.hpp"
#include "relative_index.h"

class ConverterJSON{
public:
    ConverterJSON() = default;
    std::vector<std::string> GetTextDocuments();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
};

#endif //SEARCH_ENGINE_CONVERTER_JSON_H
