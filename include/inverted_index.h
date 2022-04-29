
#ifndef SEARCH_ENGINE_INVERTED_INDEX_H
#define SEARCH_ENGINE_INVERTED_INDEX_H

#include <vector>
#include <map>
#include <string>

struct Entry{
    size_t doc_id, count;

    bool operator==(const Entry &other) const{
        return (doc_id==other.doc_id && count==other.count);
    }

    bool operator<(const Entry &other) const{
        return count<=other.count;
    }
};

class InvertedIndex{
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;

public:
    void UpdateFreqDictionary(const std::string &doc, int index);

    void UpdateDocumentBase(const std::vector<std::string> &input_docs);

    std::vector<Entry> GetWordCount(const std::string &word);

    InvertedIndex() = default;
};

#endif //SEARCH_ENGINE_INVERTED_INDEX_H
