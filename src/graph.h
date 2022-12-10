#include "teammaker.h"
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <set>
#include <cmath>

class graph {
public: 
std::vector<std::vector<int>> adjMatrix;


graph(TeamMaker* teammate, const std::string& pokemons) {
std::vector<std::string> team = teammate->generateTeam(pokemons);
std::vector<std::vector<std::string>> all_pokemon_with_neighbor;
std::vector<std::string> pokemon_with_neighbor;
//used to get the neighbors for the pokemons in the team. 
// first, get the index of the pokemon from index[pokemon], then do teammates[index] to get a map of the neighbours 
//create the 2d vector that holds the pokemon and its neighbors
for(unsigned int i = 0; i < team.size(); i++) {
    std::string current_pokemon = team.at(i);
    pokemon_with_neighbor.push_back(current_pokemon);
    // how to find the neighbor 
    // run through a loop, then push it back to pokemon_with_neighbor
    auto currIdx = teammate->index_[current_pokemon];
    auto neighbors = teammate->teammates_[currIdx];
    // for(int j =0 ; j < neighbor.size();j++) {
    //   pokemon_with_neighbor.push_back(neighbor.at(j));
    // }
    for(auto x : neighbors) {
        pokemon_with_neighbor.push_back(teammate->mons_[x.first]);
    }
    all_pokemon_with_neighbor.push_back(pokemon_with_neighbor);
  // push pokemon_with_neightbor into al_pokemon_with_neighbor
    pokemon_with_neighbor.clear();
}

// populate the matrix to how it should be 
// set of pokemons inside the all_pokemon_with_neighbor, and include everything in the team
 for(int i = 0; i < all_pokemon_with_neighbor.size(); i++) {
      for(int j = 0; j < all_pokemon_with_neighbor.at(i).size(); j++) {
        // We know that the result from generated team are for sure neighbors && we know that 
        // first 6 element in all_pokemon_with_neighbot[0][j] are neighbors
          std::vector<int> inner;
       }
    }  
}

};
