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
    std::vector<double> usageParser(const std::string& fileName, unsigned size);
  
    //destructor
    ~TeamMaker();
  
    //dfs for finding whether a pokemon is connected to another one or not, if not, then the team sucks
    bool dfs(unsigned start, unsigned key);
  
    //floyd warshall for finding the weight between each pokemon
    std::vector<std::vector<double>> floydWarshall();
  
    //the function for generating the team, taking in a string of pokemon names separated by comma and space
    //use helper function pokemonsToVector to turn the string of pokemons into a vector of pokemons
    std::vector<std::string> generateTeam(const std::string& pokemons);
    
  private:
    //map mapping pokemon with its index
    std::map<std::string, unsigned> index_;
  
    //vector of its usage percentage, with index representing a pokemon
    std::vector<double> usage_;
  
    //vector representing map of index of pokemon and its teammates percentage
    std::vector<std::map<unsigned, double>> teammates_;
  
    //vector representing the viability ceiling of each pokemon
    std::vector<double> viability_;
  
    //2d vector of weights generated by floyd warshall
    std::vector<std::vector<double>> weights_;
  
    //helper function for generateTeam for turning a string of pokemon names to a vector of pokemons
    std::vector<std::string> pokemonsToVector(const std::string& pokemons);
};
