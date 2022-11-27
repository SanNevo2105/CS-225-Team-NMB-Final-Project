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
    return 1;
}
