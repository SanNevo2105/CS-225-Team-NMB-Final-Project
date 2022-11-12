#pragma once
#include <string>
#include <vector>
#include <map>
#include <tuple>

class TeamMaker{
  public:
    //constructor taking in the teammate percentage data and individual usage percentage data
    TeamMaker(const std::string& teamFile, const std::string& usageFile);
    //parser for teammates data set, return a vector of tuple containing Pokemon name, 
    //map of teammate and its percentage, and viability ceiling
    std::vector<std::tuple<std::string, std::map<std::string, double>, double>> teammatesParser(const std::string& fileName);
    //parser for usage data set, returns a map of Pokemon name and its usage percentage
    std::map<std::string, double> usageParser(const std::string& fileName);
    //destructor
    ~TeamMaker();
    //dfs for finding whether a pokemon is connected to another one or not, if not, then the team sucks
    bool dfs(const std::string start, const std::string key);
    //floyd warshall for finding the weight between each pokemon, with 0 representing no connection
    std::vector<std::vector<double>> floydWarshall();
    std::vector<std::string> generateTeam(const std::string& pokemons);
    
  private:
    std::map<std::string, unsigned> index_;
    std::vector<double> usage_;
    std::vector<std::map<unsigned, double>> teammates_;
    
    std::vector<double> viability_;
};
