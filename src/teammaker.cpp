#include "teammaker.h"
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <cmath>

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
    std::vector<bool> traverse(index_.size(), false);
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
                if (weights_[i][j] < std::pow(weights_[i][k]*weights_[k][j], 4)) {
                    // if (mons_[i] == "politoed" && mons_[j] == "garchomp") {
                    //     std::cout << mons_[i] << " to " << mons_[j] << ": " << weights_[i][j] << std::endl;
                    //     std::cout <<"   but " << mons_[i] << " to " << mons_[k]<< ": " << weights_[i][k] << std::endl;
                    //     std::cout << "   and " << mons_[k] << " to " << mons_[j]<< ": " << weights_[k][j] << std::endl;
                    // }
                    weights_[i][j] = std::pow(weights_[i][k]*weights_[k][j], 4);
                    // if (mons_[i] == "politoed" && mons_[j] == "garchomp") {
                    //     std::cout <<"    thus new weight is " << weights_[i][j] << std::endl;
                    //     std::cout << std::endl;
                    // }
                }
            }
        }
    }
    // for (unsigned i = 0; i < size; i++) {
    //     if (mons_[i] == "politoed" || mons_[i] == "scizor") {
    //         std::cout << mons_[i] << std::endl;
    //         for (unsigned j = 0; j < size; j++) {
    //             if (mons_[j] == "garchomp" || mons_[j] == "kingdra") {
    //                 std::cout << "  " << mons_[j] << ": " << weights_[i][j] << std::endl;
    //             }
                
    //         }
    //     }
        
    // }
}

std::vector<std::string> TeamMaker::generateTeam(const std::string& pokemons){
    std::set<unsigned> team;
    std::vector<unsigned> teamVec = pokemonsToVector(pokemons);
    for (auto p:teamVec) {
        team.insert(p);
    }
    bool teamSucks = false;
    for (auto p: teamVec) {
        for (auto t: teamVec) {
            if (p != t) {
                teamSucks = !(dfs(p, t) || dfs(t, p));
                if (teamSucks) {
                    break;
                }
            }
        }
    }
    if (teamSucks) {
        std::cout << "your input sucks lmao" << std::endl;
    } else {
        std::cout << "your input seems fine" << std::endl;
    }
    unsigned size = weights_.size();
    std::set<unsigned> available;
    for (unsigned i = 0; i < size; ++i) {
        available.insert(available.end(), i);
    }
    
    for (auto p:team) {
        available.erase(available.find(p));
        //std::cout << mons_[p] <<"'s viability is " << viability_[p] << std::endl;
    }
    if (teamVec.size() != 6) {
        double powerConstant = std::log(0.5)/std::log(usage_.back());

        //std::cout << "power constant is " << powerConstant << std::endl;

        double maxWeight = 0;
        unsigned index = 0;
        for (unsigned i = 0; i < size; i++) {

            double weight = viability_[i];
            for (auto p:team) {
                weight *= (weights_[i][p]+1);
            }
            if (weight > maxWeight) {
                maxWeight = weight;
                index = i;
            }
            
        }

        std::cout << "first key mon is " << mons_[index] << std::endl;

        if (team.find(index) == team.end()) {
            teamVec.push_back(index);
            available.erase(available.find(index));
        }
        while(teamVec.size() < 6) {
            std::vector<double> multipliers;
            for (auto p:teamVec) {
                double multiplier = 1;
                for (auto t:teamVec) {
                    if (t != p) {
                        multiplier *= (weights_[p][t]+1);
                    }
                         
                }
                //std::cout << std::pow(multiplier, 5) << std::endl;
                multipliers.push_back(multiplier);
            }
            index = *available.begin();
            maxWeight = 0;
            for (auto a:available) {
               
                double weight = 0;
                for (unsigned i = 0; i < teamVec.size(); i++) {
                    unsigned p = teamVec[i];    
                    weight += multipliers[i] * (weights_[p][a]);
                }   
                weight *= std::pow(usage_[a], powerConstant) * viability_[a];
                if (weight > maxWeight) {
                    maxWeight = weight;
                    index = a;
                }
            
                
            }
            //std::cout << "inserting "<< mons_[index] << ": " << (maxWeight) << std::endl;
            available.erase(available.find(index));
            teamVec.push_back(index);

            //for debugging
            if (teamVec.size() == 6) {
                multipliers = std::vector<double>();
                for (auto p:teamVec) {
                    double multiplier = 1;
                    for (auto t:teamVec) {
                        if (t != p) {
                            multiplier *= (weights_[p][t]+1);
                        }
                    }
                    multipliers.push_back(multiplier);
                }
                double total = 0;
                for (auto m: multipliers) {
                    total+=m;
                }
                for (unsigned i = 0; i < multipliers.size(); i++) {
                    std::cout << mons_[teamVec[i]] << ": " << (multipliers[i]/total)*100 << "%" <<std::endl;
                }
                std::cout << std::endl;
            }
        }
    }
    std::vector<std::string> result;
    for (auto p:teamVec) {
        result.push_back(mons_[p]);
    }
    return result;
}

std::vector<unsigned> TeamMaker::pokemonsToVector(const std::string& str) {
    std::vector<std::string> teamStr;
    std::string pokemons = str;
    std::transform(pokemons.begin(), pokemons.end(), pokemons.begin(), ::tolower);
    unsigned start = 0;
    unsigned end = 0;
    while (end < pokemons.size()) {
        while(end < pokemons.size() && pokemons[end] != ',') {
            end++;
        }
        teamStr.push_back(pokemons.substr(start, end-start));
        while (end < pokemons.size() && (pokemons[end] == ',' || pokemons[end] == ' ')) {
            end++;
        }
        start = end;
    }
    if (teamStr.size() > 6) {
        std::__throw_invalid_argument("you inputted more than 6 Pokemons");
    }
    std::vector<unsigned> teamVec;
    for (auto p: teamStr) {
        auto found = index_.find(p);
        if (found != index_.end()) {
            teamVec.push_back(found->second);
        } else {
            std::string error = "Pokemon " + p + " not found";
            std::__throw_invalid_argument(error.c_str());
        }
    }
    return teamVec;
}

std::map<std::string, std::set<std::string>> TeamMaker::getAdjList(std::vector<std::string> team) {
    std::set<unsigned> pkmnSet;
    for (auto m:team) {
        pkmnSet.insert(index_[m]);
    }
    std::map<std::string, std::set<std::string>> adjList;
    for (auto p:pkmnSet) {
        for (auto n:teammates_[p]) {
            //if (pkmnSet.find(n.first) != pkmnSet.end()) {
                adjList[mons_[n.first]].insert(mons_[p]);
                adjList[mons_[p]].insert(mons_[n.first]);
            //}
        }
    }
    return adjList;
}
