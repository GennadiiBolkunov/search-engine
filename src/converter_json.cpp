#include <fstream>
#include "converter_json.h"
#include "algorithm"

std::vector<std::string> ConverterJSON::GetTextDocuments(const QDir &currentDir) {
    std::ifstream configFile ("../../json_files/config.json");
    std::vector<std::string> result;
    if (configFile.is_open()){
        nlohmann::json config;
        configFile>>config;
        result.reserve(config.size());
        for(auto &fileName : config["files"])
        {
            std::ifstream fileToRead(currentDir.absolutePath().toStdString()+"/"+static_cast<std::string>(fileName));
            std::string text;
            while (fileToRead.is_open() && !fileToRead.eof()){
                std::string line;
                std::getline(fileToRead, line);
                text.append("\n"+line);
            }
            result.push_back(text);
        }
    }
    return result;
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream file ("../../json_files/config.json");
    if (file.is_open()){
        nlohmann::json config;
        file>>config;
        return config["config"]["max_responses"];
    }
    else
        return 0;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream file ("../../json_files/requests.json");
    std::vector<std::string> res;
    if(file.is_open()){
        nlohmann::json requests;
        file>>requests;
        for (auto &r : requests["requests"])
            res.push_back(r);
    }
    return res;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers){
    std::ofstream file("../../json_files/answers.json");
    if (file.is_open()){
        nlohmann::json main;
        int reqNum{1};
        nlohmann::json requests;
        for (auto &req : answers){
            nlohmann::json requestInfo;
            if (!req.empty()){
                requestInfo["result"]=true;
                for (auto &d: req){
                    nlohmann::json relevance;
                    relevance["docid"]=d.doc_id;
                    relevance["rank"]=d.rank;
                    requestInfo["relevance"].push_back(relevance);
                }
            }
            else requestInfo["result"]=false;
            requests["request"+ std::to_string(reqNum)]=requestInfo;
            reqNum++;
        }
        main["answers"]=requests;
        file<<main;
    }
}

void ConverterJSON::setRequest(std::string request) {
    std::ofstream file ("../../json_files/requests.json");
    std::vector<std::string> res;
    if(file.is_open()){
        nlohmann::json requests;
        requests["requests"].push_back(request);
        file<<requests;
    }
}

std::string ConverterJSON::getFileName(size_t doc_id) {
    std::ifstream file ("../../json_files/config.json");
    if(file.is_open()){
        nlohmann::json requests;
        file>>requests;
        return requests["files"][doc_id];
    }
    return "";
}

void ConverterJSON::updateFiles(const QDir &currentDir) {
    std::ifstream fromConfigFile ("../../json_files/config.json");
    if (fromConfigFile.is_open()){
        nlohmann::json config;
        fromConfigFile>>config;
        config["files"].clear();
        auto dirList =currentDir.entryInfoList();

        for(auto &el: dirList){
            if (!el.fileName().isEmpty() && el.isFile())
                config["files"].push_back(el.fileName().toStdString());
        }
        fromConfigFile.close();
        std::ofstream toConfigFile ("../../json_files/config.json");
        if (toConfigFile.is_open()){
            toConfigFile<<config;
        }
    }
}

void ConverterJSON::setMaxResponses(int amount) {
    std::ifstream fromConfigFile ("../../json_files/config.json");
    if (fromConfigFile.is_open()){
        nlohmann::json config;
        fromConfigFile>>config;
        config["config"]["max_responses"]=amount;
        fromConfigFile.close();
        std::ofstream toConfigFile ("../../json_files/config.json");
        if (toConfigFile.is_open()){
            toConfigFile<<config;
        }
    }
}