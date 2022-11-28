#include "teammaker.h"
#include <iostream>

int main(){
    std::string teamFile = "/workspaces/CS-225-Team-NMB-Final-Project/gen8ou-1825-moveset.txt";
    std::string usageFile = "/workspaces/CS-225-Team-NMB-Final-Project/gen8ou-1825-usage.txt";
    TeamMaker* tm = new TeamMaker(teamFile, usageFile); 
    // std::vector<std::tuple<std::string, std::map<std::string, double>, double>> teammates = tm->teammatesParser(teamFile);
    // for (auto entry:teammates) {
    //     std::string name = std::get<0>(entry);
    //     std::map<std::string, double> pt = std::get<1>(entry);
    //     double vc = std::get<2>(entry);
    //     std::cout<< name << "'s viability ceiling: " << vc <<std::endl;
    //     for (auto t:pt) {
    //         std::cout<< "   " << t.first << ": " << t.second <<std::endl;
    //     }
    // }
    // std::cout << "usageParser testing" << std::endl;
    // std::vector<double> individual = tm->usageParser(usageFile, teammates.size());
    // for(unsigned i = 0; i < individual.size(); i++){
    //     std::string name = std::get<0>(teammates[i]);
    //     double usage = individual[i] * 100;
    //     std::cout<< name << " " << usage << "%" <<std::endl;
    // }

    //inputting the most popular mon gives out the most generic team
    std::vector<std::string> team1 = tm->generateTeam("Landorus-Therian");
    for (auto p:team1) {
        std::cout << p << std::endl;
    }
    std::cout << std::endl;

    //inputting stall-mons give out stall team
    std::vector<std::string> team2 = tm->generateTeam("Pyukumuku, skarmory");
    for (auto p:team2) {
        std::cout << p << std::endl;
    }
    std::cout << std::endl;

    //inputting rain-mons give out rain team
    std::vector<std::string> team3 = tm->generateTeam("pelipper");
    for (auto p:team3) {
        std::cout << p << std::endl;
    }
    std::cout << std::endl;

    //inputting some random stuff doesn't give meta team
    std::vector<std::string> team4 = tm->generateTeam("Marowak-Alola, slowbro");
    for (auto p:team4) {
        std::cout << p << std::endl;
    }
    std::cout << std::endl;

    //inputting some unsynergystic mons give out warning message, meaning dfs works
    std::vector<std::string> team5 = tm->generateTeam("tentacruel, golisopod");
    for (auto p:team5) {
        std::cout << p << std::endl;
    }

    //inputting invalid mon cause error
    std::vector<std::string> die = tm->generateTeam("joe biden");
    return 1;
}
