#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "counting_dictionary.h"
#include "inverted_index.h"

std::mutex dict_access;

void InvertedIndex::UpdateFreqDictionary(const std::string &doc, int index) {
    CountingDictionary this_doc_dictionary (doc);
    dict_access.lock();
    for (auto &word : this_doc_dictionary)
        freq_dictionary[word.first].push_back({static_cast<size_t>(index), static_cast<size_t>(word.second)});
    dict_access.unlock();
}

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string> &input_docs) {
    docs.reserve(input_docs.size());
    for (auto &doc : input_docs)
        docs.push_back(doc);
    std::vector<std::thread> threads;
    threads.reserve(docs.size());
    for (int i=0; i<docs.size(); ++i){
        threads.emplace_back(&InvertedIndex::UpdateFreqDictionary, this, docs[i], i);
    }
    for (auto &thread : threads)
        thread.join();
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    if (freq_dictionary.find(word)==freq_dictionary.end())
        return std::vector<Entry> {};
    return freq_dictionary[word];
}

