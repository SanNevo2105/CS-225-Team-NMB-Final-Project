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

