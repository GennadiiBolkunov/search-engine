//Child class is used to specialize std::set constructor for unique words collecting task

#ifndef SEARCH_ENGINE_REQUEST_WORD_SET_H
#define SEARCH_ENGINE_REQUEST_WORD_SET_H

#include <set>
static inline bool isWordChar(char s){
    return s>='A' && s<='Z' || s>='a' && s <='z' || s>='0' && s<='9' || s=='\'';
}

class RequestWordSet : public std::set<std::string>{

public:
    RequestWordSet(const std::string &request){
        std::string word;
        for (char i : request) {
            char letter{i};
            if (isWordChar(letter)) {
                if (letter>='A' && letter <='Z')
                    letter+=32;
                word += letter;
            }
            else {
                if (!word.empty()){
                    this->insert(word);
                    word.clear();
                }
            }
        }
        if (!word.empty()){
            this->insert(word);
            word.clear();
        }
    }
};

#endif //SEARCH_ENGINE_REQUEST_WORD_SET_H
