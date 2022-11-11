#pragma once
#include <string>
#include <vector>
#include <map>

class TeamMaker{
  public:
    TeamMaker(const std::string& teamFile, const std::string& usageFile);
    std::map<std::string, std::map<std::string, double>> teammatesParser(const std::string& fileName);
    std::map<std::string, double> usageParser(const std::string& fileName);
    ~TeamMaker();
    bool dfs(const std::string start, const std::string key);
    std::vector<std::vector<double>> floydWarshall();
    std::vector<std::string> generateTeam(const std::string& pokemons);
    
  private:
    std::vector<double> usage_;
    std::vector<std::map<unsigned, double>> teammates_;
    std::map<std::string, unsigned> index_;
};
