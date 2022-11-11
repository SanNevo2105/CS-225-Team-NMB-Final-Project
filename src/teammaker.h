#pragma once
#include <string>
#include <vector>
#include <map>

class TeamMaker{
  public:
    TeamMaker(const std::string& teamFile, const std::string& indivFile);
    std::map<std::string, std::map<std::string, double>> teammateParser(const std::string& fileName);
    std::map<std::string, double> usageParser(const std::string& fileName);
    ~TeamMaker();
    bool dfs(const std::string start, const std::string key);
    std::vector<std::vector<double>> floydWarshall();
    std::vector<std::string> generateTeam(const std::string& pokemons);
    
    
  
  Private:
};
