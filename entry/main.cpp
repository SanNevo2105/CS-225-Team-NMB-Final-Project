#include "teammaker.h"
#include <iostream>

int main(){
    std::cout << "ree" << std::endl;
    TeamMaker* tm = new TeamMaker("/workspaces/CS-225-Team-NMB-Final-Project/gen8ou-1825.txt", "/workspaces/CS-225-Team-NMB-Final-Project/dataset.csv"); 
    std::vector<std::tuple<std::string, std::map<std::string, double>, double>> teammates = tm->teammatesParser("/workspaces/CS-225-Team-NMB-Final-Project/gen8ou-1825.txt");
    for (auto entry:teammates) {
        std::string name = std::get<0>(entry);
        std::map<std::string, double> pt = std::get<1>(entry);
        double vc = std::get<2>(entry);
        std::cout<< name << "'s viability ceiling: " << vc <<std::endl;
        for (auto t:pt) {
            std::cout<< "   " << t.first << ": " << t.second <<std::endl;
        }
    }
    std::cout << "usageParser testing" << std::endl;
    TeamMaker* team = new TeamMaker("/workspaces/CS-225-Team-NMB-Final-Project/gen8ou-1825.txt", "/workspaces/CS-225-Team-NMB-Final-Project/dataset.csv"); 
    std::map<std::string, double> individual = team->usageParser("/workspaces/CS-225-Team-NMB-Final-Project/dataset.csv");
    for(auto entry:individual){
        std::string name = std::get<0>(entry);
        double vc = std::get<1>(entry);
        std::cout<< name << " " << vc <<std::endl;
    }
    return 1;
}
