#include "teammaker.h"
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <set>

TeamMaker::TeamMaker(const std::string& teamFile, const std::string& usageFile){
    std::vector<std::tuple<std::string, std::map<std::string, double>, double>> result = teammatesParser(teamFile);

    //string corresponds to the get<0> result.at(i);
    //unsinged is just from 0 to vector.size();
    for(unsigned int i = 0; i < result.size(); i++) {
        // populate the index_
        index_[std::get<0> (result[i])] =  i;
        // populating the viability
        viability_.push_back(std::get<2> (result[i]));
        // populate mons
        mons_.push_back(std::get<0> (result[i]));
    }
    // getting the double from the map in result
    // goes through the result vector, then go to the tuples position, then go to the map and obtain the info

    std::vector<double> value_in_teammate;
    // get access to the tuple map 
    // populate the tuple map into a new map 
    // assign new key to the new map
    // push the new map into teammates_ private variable

    
    for(unsigned int i = 0; i < result.size();i++) {
        // get access to the tuple and then the map
        std::map<std::string, double> current_map = std::get<1>(result[i]);
        // loop through current map and insert the element into the new map
        std::map<unsigned, double> new_map;
    
        for (auto entry: current_map) {
            auto found = index_.find(entry.first);
            if (found != index_.end()) {
                new_map[found->second] = entry.second;
            }
            
        }
        teammates_.push_back(new_map);
    }

    // populating usage
    usage_ = usageParser(usageFile, result.size());
    assert((index_.size() == usage_.size()) && (usage_.size() == teammates_.size()) && (teammates_.size() == viability_.size()));

    floydWarshall();

    // for (auto w:weights_) {
    //     for (auto i:w) {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;
    // }
    //testing lines
    // std::cout << "result size:" << result.size() << std::endl;
    // std::cout << "index_ size:" << index_.size() << std::endl;
    // std::cout << "usage_ size:" << usage_.size() << std::endl;
    // std::cout << "teammates_ size:" << teammates_.size() << std::endl;
    // std::cout << "viability_ size:" << viability_.size() << std::endl;
    // for (auto i: index_) {
    //     if (i.second == 0) {
    //         std::cout << "|"<< i.first << "|" << std::endl;
    //     }
    //     //std::cout << i.first << ": " << i.second << std::endl;
    // }
    // for (auto i:index_) {
    //     std::cout << i.first << ", viability: " << viability_[i.second] << " usage: " << usage_[i.second] * 100 << "%" << std::endl;
    //     for (auto team: teammates_[i.second]) {
    //         std::cout << "  " << std::get<0> (result[team.first]) << ": " << team.second << std::endl;
    //     }
    // }
}

std::vector<std::tuple<std::string, std::map<std::string, double>, double>> TeamMaker::teammatesParser(const std::string& fileName){
    std::ifstream textFile(fileName);
    std::string line;
    std::vector<std::tuple<std::string, std::map<std::string, double>, double>> result;
    unsigned plusCount = 0;
    if (textFile.is_open()){
        //initialize these variable first since they have to be retained outside of the while loop
        std::string name;
        double viabilityCeiling = 0;
        //go through each line
        while (getline(textFile, line)) {
            //counting the number of + in front of the line to see which section of the entry it is
            if (line[1] == '+') {
                plusCount++;
                //once found the name line
                if (plusCount%9 == 1) {
                    getline(textFile, line);
                    //i is the starting index of the substring
                    unsigned i = 0;
                    while (line[i] == '|' || line[i] == ' ') {
                        i++;
                    }
                    //j is the ending index of the substring
                    //this will be the convention throughout this function
                    unsigned j = line.size();
                    while (line[j-1] == ' ' || line[j-1] == '|') {
                        j--;
                    }
                    name = line.substr(i, j-i);
                }
                //once found the viability ceiling
                if (plusCount%9 == 2) {
                    //first, skip 3 lines
                    getline(textFile, line);
                    getline(textFile, line);
                    getline(textFile, line);
                    unsigned j = line.size();
                    while (line[j-1] == ' ' || line[j-1] == '|') {
                        j--;
                    }
                    unsigned i = j;
                    while (line[i-1] != ' ') {
                        i--;
                    }
                    
                    viabilityCeiling = std::stod(line.substr(i, j-i)) * 0.01;
                }
                //once found teammates
                if (plusCount%9 == 7) {
                    //skip 2 lines
                    getline(textFile, line);
                    getline(textFile, line);
                    std::map<std::string, double> teammates;
                    while (line[1] != '+') {
                        double percent = 0;
                        unsigned j = line.size();
                        while (line[j-1] == '|' || line[j-1] == '%' || line[j-1] == ' ') {
                            j--;
                        }
                        unsigned i = j;
                        while(line[i-1] != ' ') {
                            i--;
                        }
                        percent = std::stod(line.substr(i, j-i)) * 0.01;
                        i--;
                        while (line[i-1] == ' ') {
                            i--;
                        }
                        std::string pokemon = line.substr(3, i-3);
                        std::transform(pokemon.begin(), pokemon.end(), pokemon.begin(), ::tolower);
                        //std::cout <<"|" << pokemon <<"|" <<std::endl;
                        teammates[pokemon] = percent;
                        getline(textFile, line);
                    }
                    //have to increment the plus count since another + has been spotted
                    plusCount++;
                    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                    result.push_back(std::make_tuple(name, teammates, viabilityCeiling));
                }
            }
        }
    } else {
        std::__throw_runtime_error("cannot open file");
    }
    return result;
}

std::vector<double> TeamMaker::usageParser(const std::string& fileName, unsigned size){
    std::ifstream textFile(fileName);
    std::string line;
    std::vector<double> usage;
    unsigned plusCount = 0;
    if (textFile.is_open()){
        for (unsigned i = 0; i < 5; i++) {
            getline(textFile, line);
        }
        for (unsigned i = 0; i < size; i++) {
            getline(textFile, line);
            unsigned count = 0;
            unsigned start = 0;
            while (count < 3) {
                if (line[start] == '|') {
                    count++;
                }
                start++;
            }
            start++;
            unsigned end = start;
            while (line[end] != '%') {
                end++;
            }
            usage.push_back(std::stod(line.substr(start, end - start)) * 0.01);
        }
    }else {
        std::__throw_runtime_error("cannot open file");
    }
    return usage;
}

TeamMaker::~TeamMaker(){}

bool TeamMaker::dfs(unsigned start, unsigned key){
    bool* traverse = new bool[index_.size()];
    std::stack<unsigned> pkmnStack;
    pkmnStack.push(start);
    traverse[start] = true;
    while (!pkmnStack.empty()) {
        unsigned curr = pkmnStack.top();
        if (curr == key) {
            return true;
        }
        std::map<unsigned, double> t = teammates_[curr];
        pkmnStack.pop();
        for (auto p:t) {
            if (!traverse[p.first]) {
                traverse[p.first] = true;
                pkmnStack.push(p.first);
            }
        }
    }
    
    return false;
}

void TeamMaker::floydWarshall(){
    unsigned size = usage_.size();
    weights_ = std::vector<std::vector<double>>(size, std::vector<double>(size, 0));
    for (unsigned i = 0; i < size; i++) {
        weights_[i][i] = 1;
        for (auto t:teammates_[i]) {
            weights_[i][t.first] = t.second;
        }
    }

    for (unsigned k = 0; k < size; k++) {
        for (unsigned i = 0; i < size; i++) {
            for (unsigned j = 0; j < size; j++) {
                if (weights_[i][j] < weights_[i][k]*weights_[k][j]) {
                    weights_[i][j] = weights_[i][k]*weights_[k][j];
                }
            }
        }
    }
}

std::vector<std::string> TeamMaker::generateTeam(const std::string& pokemons){
    std::vector<unsigned> team;
    std::vector<std::string> teamStr = pokemonsToVector(pokemons);
    for (auto p: teamStr) {
        auto found = index_.find(p);
        if (found != index_.end()) {
            team.push_back(found->second);
        } else {
            std::string error = "Pokemon " + p + " not found";
            std::__throw_invalid_argument(error.c_str());
        }
    }
    unsigned size = weights_.size();
    std::set<unsigned> available;
    for (unsigned i = 0; i < size; ++i) {
        available.insert(available.end(), i);
    }
    for (auto p:team) {
        available.erase(available.find(p));
    }
    while (team.size() < 6) {
        double maxWeight = 0;
        unsigned index = *available.begin();
        for (auto a:available) {

            double weight = usage_[a] * 0.25;
            //double weight = 0;
            for (unsigned i = 0; i < team.size(); i++) {
                unsigned p = team[i];
                weight += (weights_[p][a]/(1+i));
            }
            weight *= viability_[a];
            if (weight > maxWeight) {
                maxWeight = weight;
                index = a;
            }
        }
        available.erase(available.find(index));
        team.push_back(index);
    }
    std::vector<std::string> result;
    for (auto p:team) {
        result.push_back(mons_[p]);
    }
    return result;
}

std::vector<std::string> TeamMaker::pokemonsToVector(const std::string& str) {
    std::vector<std::string> result;
    std::string pokemons = str;
    std::transform(pokemons.begin(), pokemons.end(), pokemons.begin(), ::tolower);
    unsigned start = 0;
    unsigned end = 0;
    while (end < pokemons.size()) {
        while(end < pokemons.size() && pokemons[end] != ',') {
            end++;
        }
        result.push_back(pokemons.substr(start, end-start));
        while (end < pokemons.size() && (pokemons[end] == ',' || pokemons[end] == ' ')) {
            end++;
        }
        start = end;
    }
    if (result.size() > 6) {
        std::__throw_invalid_argument("you inputted more than 6 Pokemons");
    }
    return result;
}
