#include <cmath> //for round()
#include <algorithm> //for sort()

#include "search_server.h"
#include "request_word_set.h"
#include "converter_json.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> result;
    for (auto &request : queries_input){ //reading each request
        RequestWordSet currentRequestWords(request);

        std::map<size_t, size_t> docRelevance; //count each doc relevance (summary for each word in request)
        for (auto &w: currentRequestWords){
            auto wordCount = _index.GetWordCount(w);
            if (!wordCount.empty()){
                for (auto &d : wordCount){
                    docRelevance[d.doc_id]+=d.count;
                }
            }
        }
        if (docRelevance.empty()){
            result.emplace_back();
            continue;
        }

        size_t maxRelevance{docRelevance.begin()->second}; //find max relevance from all
        for (auto &d : docRelevance){
            if (d.second>maxRelevance)
                maxRelevance=d.second;
        }
        ConverterJSON conv;
        int responseNumber = conv.GetResponsesLimit();
        if (docRelevance.size()<responseNumber)
            responseNumber=docRelevance.size();
        std::vector<RelativeIndex> this_request_index;//calculating a rank and collecting indexes
        this_request_index.reserve(responseNumber);
        for (auto &d: docRelevance){
            auto str = std::to_string(round((double)d.second*1000/(double)maxRelevance)/1000);
            str.resize(5);
            double rank= std::stod(str);
            //double rank=(double)d.second/(double)maxRelevance;
            this_request_index.push_back({d.first, rank});
        }

        std::sort(this_request_index.begin(), this_request_index.end(), std::greater{});
        this_request_index.resize(responseNumber);
        result.push_back(this_request_index);
    }
    return result;
}
