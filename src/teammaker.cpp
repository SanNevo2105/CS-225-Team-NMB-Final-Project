#include "teammaker.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

TeamMaker::TeamMaker(const std::string& teamFile, const std::string& usageFile){}

std::vector<std::tuple<std::string, std::map<std::string, double>, double>> TeamMaker::teammatesParser(const std::string& fileName){
    std::ifstream textFile(fileName);
    std::string line;
    std::vector<std::tuple<std::string, std::map<std::string, double>, double>> result;
    unsigned plusCount = 0;
    if (textFile.is_open()){
        std::string name;
        double viabilityCeiling = 0;
        while (getline(textFile, line)) {
            if (line[0] == '+') {
                plusCount++;
                //once found the name line
                if (plusCount%9 == 1) {
                    getline(textFile, line);
                    unsigned i = 0;
                    while (line[i] == '|' || line[i] == ' ') {
                        i++;
                    }
                    unsigned j = name.size();
                    while (name[j-1] == ' ') {
                        j--;
                    }
                    name = line.substr(i, j-i);
                }
                //once found the viability ceiling
                if (plusCount%9 == 2) {
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
                    getline(textFile, line);
                    std::map<std::string, double> teammates;
                    while (line[0] != '+') {
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
                        std::string pokemon = line.substr(3, i-3);
                        teammates[pokemon] = percent;
                        getline(textFile, line);
                    }
                    plusCount++;
                    result.push_back(std::make_tuple(name, teammates, viabilityCeiling));
                }
            }
        }
    } else {
        std::__throw_runtime_error("cannot open file");
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
