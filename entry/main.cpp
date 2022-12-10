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

    // std::cout << "inputting Lando, expecting a balanced overused team" << std::endl; 

    // //inputting the most popular mon gives out the most generic team
    // std::cout << "inputting Lando, expecting a balanced overused team" << std::endl; 
    // std::vector<std::string> team1 = tm->generateTeam("Landorus-Therian");

    // std::cout << std::endl;

    // //inputting stall-mons give out stall team
    // std::cout << "inputting Pyukumuku and corviknight, expecting a stall team" << std::endl; 
    // std::vector<std::string> team2 = tm->generateTeam("Pyukumuku, corviknight");

    // std::cout << std::endl;

    // //inputting rain-mons give out rain team
    // std::cout << "inputting Pelipper, expecting a normal rain team" << std::endl;
    // std::vector<std::string> team3 = tm->generateTeam("pelipper");

    // std::cout << std::endl;

    
    // std::cout << "inputting kingdra and politoed, expecting very different rain team" << std::endl;
    // std::vector<std::string> team10 = tm->generateTeam("kingdra, politoed");

    // std::cout << std::endl;

    // //inputting some random stuff doesn't give meta team
    // std::cout << "inputting Marowak-Alola and Slowbro, expecting weird off-meta team" << std::endl;
    // std::vector<std::string> team4 = tm->generateTeam("Marowak-Alola, slowbro");

    // std::cout << std::endl;

    // //inputting some unsynergystic mons give out warning message, meaning dfs works
    // std::cout << "inputting Tentacruel and Golisopod, expecting message saying it's a bad choice" << std::endl;
    // std::vector<std::string> team5 = tm->generateTeam("tentacruel, golisopod");

    // std::cout << std::endl;
    // //inputting rain-mons give out rain team
    // std::cout << "inputting pelipper and polteageist, expecting some weird rain-mon" << std::endl;
    // std::vector<std::string> team6 = tm->generateTeam("pelipper, Polteageist");

    // std::cout << std::endl;

    
    // std::cout << "inputting blissey, expecting a stall team without dragapult and lele, should not have chansey" << std::endl;
    // std::vector<std::string> team7 = tm->generateTeam("blissey");

    // std::cout << std::endl;


    // std::cout << "inputting excadrill, expecting a sand team with tyranitar or hippowdon" << std::endl;
    // std::vector<std::string> team8 = tm->generateTeam("excadrill");

    // std::cout << std::endl;

    // std::cout << "inputting slowbro, lando, rillaboom, and melmetal, expecting xurkitree" << std::endl;
    // std::vector<std::string> team9 = tm->generateTeam("slowbro, landorus-therian, rillaboom, melmetal");

    
    // std::cout << std::endl;
    // std::cout << "inputting less-related mon (zapdos and bulu) just to see what happens" << std::endl;
    // std::vector<std::string> team11 = tm->generateTeam("zapdos, tapu bulu");

    // //inputting invalid mon cause error
    // std::vector<std::string> die = tm->generateTeam("joe biden");
    return 1;
}
