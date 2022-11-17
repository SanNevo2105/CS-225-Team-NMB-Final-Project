#include "teammaker.h"
#include <fstream>

TeamMaker::TeamMaker(const std::string& teamFile, const std::string& usageFile){}

std::vector<std::tuple<std::string, std::map<std::string, double>, double>> TeamMaker::teammatesParser(const std::string& fileName){
    std::ifstream words(fileName);

    if (words.is_open()){

    }
}

std::map<std::string, double> TeamMaker::usageParser(const std::string& fileName){}

TeamMaker::~TeamMaker(){}

bool TeamMaker::dfs(const std::string start, const std::string key){}

std::vector<std::vector<double>> TeamMaker::floydWarshall(){}

std::vector<std::string> TeamMaker::generateTeam(const std::string& pokemons){}
