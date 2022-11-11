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
    bfs(const std::string name);
    floydWarshall();
    
  
  Private:
};
