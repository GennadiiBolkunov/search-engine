#ifndef SEARCH_ENGINE_SEARCH_SERVER_H
#define SEARCH_ENGINE_SEARCH_SERVER_H

#include "inverted_index.h"
#include "relative_index.h"

class SearchServer{
    InvertedIndex _index;

public:
    SearchServer(InvertedIndex &idx) : _index(idx){}

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input);
};

#endif //SEARCH_ENGINE_SEARCH_SERVER_H
