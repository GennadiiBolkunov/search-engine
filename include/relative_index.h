#ifndef SEARCH_ENGINE_RELATIVE_INDEX_H
#define SEARCH_ENGINE_RELATIVE_INDEX_H
#include <string>

struct RelativeIndex{
    size_t doc_id;
    double rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
    bool operator<(const RelativeIndex& other) const {
        if (rank==other.rank)
            return doc_id>other.doc_id; //in case of rank equality smaller element is an element with higher id
        return rank<other.rank;
    }
    bool operator>(const RelativeIndex& other) const {
        if (rank==other.rank)
            return doc_id<other.doc_id; //same thing
        return rank>other.rank;
    }
};

#endif //SEARCH_ENGINE_RELATIVE_INDEX_H
