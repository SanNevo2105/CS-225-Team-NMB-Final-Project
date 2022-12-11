#include <catch2/catch_test_macros.hpp>
#include "teammaker.cpp"
#include "teammaker.h"


#include <iostream>
#include <string>



TEST_CASE("Parsingdataset", "[parsing]") {
    std::string teamFile = "/workspaces/CS-225-Team-NMB-Final-Project/gen8ou-1825-moveset.txt";
    std::string usageFile = "/workspaces/CS-225-Team-NMB-Final-Project/gen8ou-1825-usage.txt";
    TeamMaker* tm = new TeamMaker(teamFile, usageFile); 
    std::cout<< "teammatesParser testing" << std::endl;
    
    assert((tm->index_.size() == tm->usage_.size()) && (tm->usage_.size() == tm->teammates_.size()) && (tm->teammates_.size() == tm->viability_.size()));

}

TEST_CASE("Floyd-warshall", "[fw]") {
    const double EPSILON = std::pow(2.22045, -16);
    std::string teamFile = "/workspaces/CS-225-Team-NMB-Final-Project/test-moveset.txt";
    std::string usageFile = "/workspaces/CS-225-Team-NMB-Final-Project/test-usage.txt";
    TeamMaker* tm = new TeamMaker(teamFile, usageFile); 
    std::cout<< "Floyd-warshall testing" << std::endl;
    for (auto m: tm->mons_) {
        std::cout << "_"<< m <<"_"<< std::endl;
    }
    assert(tm->mons_[0] == "landorus-therian");
    assert(tm->mons_[1] == "dragapult");
    assert(tm->mons_[2] == "heatran");
    assert(tm->mons_[3] == "clefable");
    assert(tm->mons_[4] == "crobat");

    //Lando's entries
    assert(std::abs(tm->weights_[0][0]-1) < EPSILON);
    assert(std::abs(tm->weights_[0][1]-0.36741) < EPSILON);
    assert(std::abs(tm->weights_[0][2]-0.40126) < EPSILON);
    std::cout << tm->weights_[0][3] << " compared to " << std::pow(0.14649 * 0.36741, 4) << std::endl;
    assert(std::abs(tm->weights_[0][3] - std::pow(0.14649 * 0.36741, 4)) < EPSILON);
    assert(std::abs(tm->weights_[0][4]-0) < EPSILON);
    /*
    //use 2.22045e-016
    //Dragapult's entries
    std::cout << tm->weights_[1][0] << " compared to " << 0.57344 << std::endl;
    assert(unsigned(tm->weights_[1][0] * 100000) == 57344);
    assert(tm->weights_[1][1] == 1);
    assert(tm->weights_[1][2] == 0.28261);
    std::cout << std::to_string(tm->weights_[1][3]) << " compared to " << "0.14649" << std::endl;
    assert(tm->weights_[1][3] == 0.146490);
    assert(tm->weights_[1][4] == 0);

    //Heatran's entries
    assert(tm->weights_[2][0] == 0.73876);
    assert(tm->weights_[2][1] == 0.33338);
    assert(tm->weights_[2][2] == 1);
    assert(unsigned(tm->weights_[2][3] * 1000000) == unsigned(std::pow(0.14649 * 0.33338, 4) * 1000000));
    assert(tm->weights_[2][4] == 0);

    //Clefable's entries
    assert(tm->weights_[3][0] == 0.31143);
    assert(tm->weights_[3][1] == 0.24477);
    assert(tm->weights_[3][2] == 0.24534);
    assert(tm->weights_[3][3] == 1);
    assert(tm->weights_[3][4] == 0);

    //Crobat's entries
    for (unsigned i = 0; i < 4; i++) {
        assert(tm->teammates_[i].find(4) == tm->teammates_[i].end());
        assert(tm->teammates_[4].find(i) == tm->teammates_[4].end());
        assert(tm->weights_[i][4] == 0);
    }
    */
}

TEST_CASE("depthfirstsearch", "[dfs]") {
    std::string teamFile = "../test-moveset.txt";
    std::string usageFile = "../test-usage.txt";
    TeamMaker* tm = new TeamMaker(teamFile, usageFile); 
    assert(tm->mons_[0] == "landorus-therian");
    assert(tm->mons_[1] == "dragapult");
    assert(tm->mons_[2] == "heatran");
    assert(tm->mons_[3] == "clefable");
    assert(tm->mons_[4] == "crobat");

    for(unsigned i=0; i < 4; i ++){
        for(unsigned j =0; j < 4; j ++ ){
            if(i != j){
                REQUIRE(tm->dfs(i, j));
            }
        }
    }
    for(unsigned i=0; i < 4; i ++){
        REQUIRE(tm->dfs(4, i) == false);
    }
}
