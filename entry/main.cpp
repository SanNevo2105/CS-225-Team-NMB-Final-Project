#include "teammaker.h"
#include <iostream>

int main(){
    std::cout << "ree" << std::endl;
    TeamMaker* tm = new TeamMaker("die", "die");
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
    return 1;
}
