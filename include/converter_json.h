#ifndef SEARCH_ENGINE_CONVERTER_JSON_H
#define SEARCH_ENGINE_CONVERTER_JSON_H

#include "nlohmann/json.hpp"
#include "relative_index.h"
#include <QDir>

class ConverterJSON{
public:
    ConverterJSON() = default;
    std::vector<std::string> GetTextDocuments(const QDir &currentDir);

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);

    void setRequest(std::string request);

    std::string getFileName(size_t doc_id);

    void updateFiles(const QDir &currentDir);

    void setMaxResponses(int amount);
};

#endif //SEARCH_ENGINE_CONVERTER_JSON_H
