//Child class is used to specialize std::map constructor for words counting task

#ifndef SEARCH_ENGINE_COUNTING_DICTIONARY_H
#define SEARCH_ENGINE_COUNTING_DICTIONARY_H

#include <map>

static inline bool isWordChar(char s){
    return s>='A' && s<='Z' || s>='a' && s <='z' || s>='0' && s<='9' || s=='\'';
}

class CountingDictionary : public std::map<std::string, int>{

    void collectWord(const std::string &word){
        if (!word.empty()){
            if (this->find(word)==this->end())
                this->operator[](word) = 1;
            else
                this->operator[](word)++;
        }
    }

public:
    CountingDictionary (const std::string &doc){
        std::string word;
        for (char i : doc) {
            char letter{i};
            if (isWordChar(letter)) {
                if (letter>='A' && letter <='Z')
                    letter+=32;
                word += letter;
            }
            else {
                collectWord(word);
                word.clear();
            }
        }
        collectWord(word);
    }
};

#endif //SEARCH_ENGINE_COUNTING_DICTIONARY_H
