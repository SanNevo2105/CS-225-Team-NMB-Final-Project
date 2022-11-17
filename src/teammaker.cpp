#include "teammaker.h"
#include <fstream>
#include <iterator>

TeamMaker::TeamMaker(const std::string& teamFile, const std::string& usageFile){}

std::vector<std::tuple<std::string, std::map<std::string, double>, double>> TeamMaker::teammatesParser(const std::string& fileName){
    std::ifstream textFile(fileName);
    std::string line;
    std::vector<std::tuple<std::string, std::map<std::string, double>, double>> result;
    unsigned plusCount = 0;
    if (textFile.is_open()){
        std::string name;
        double viabilityCeiling;
        while (getline(textFile, line)) {
            if (line[0] == '+') {
                plusCount++;
                if (plusCount%9 == 1) {
                    getline(textFile, line);
                    unsigned i = 0;
                    while (line[i] == '|' || line[i] == ' ') {
                        i++;
                    }
                    while (line[i] != '|') {
                        name += line[i];
                        i++;
                    }
                    unsigned j = name.size();
                    while (name[j-1] == ' ') {
                        j--;
                    }
                    name = name.substr(0, j);
                }
            }
        }
    }
    return result;
}

std::map<std::string, double> TeamMaker::usageParser(const std::string& fileName){
    return std::map<std::string, double>();
}

TeamMaker::~TeamMaker(){}

bool TeamMaker::dfs(const std::string start, const std::string key){
    return true;
}

std::vector<std::vector<double>> TeamMaker::floydWarshall(){
    return std::vector<std::vector<double>>();
}

std::vector<std::string> TeamMaker::generateTeam(const std::string& pokemons){
    return std::vector<std::string>();
}
