#include "graph.h"
#include <cmath>

// graph(TeamMaker* teammate, const std::string& pokemons) {
// std::vector<std::string> team = teammate->generateTeam(pokemons);
// std::vector<std::vector<std::string>> all_pokemon_with_neighbor;
// std::vector<std::string> pokemon_with_neighbor;
// //used to get the neighbors for the pokemons in the team. 
// // first, get the index of the pokemon from index[pokemon], then do teammates[index] to get a map of the neighbours 
// //create the 2d vector that holds the pokemon and its neighbors
// for(unsigned int i = 0; i < team.size(); i++) {
//     std::string current_pokemon = team.at(i);
//     pokemon_with_neighbor.push_back(current_pokemon);
//     // how to find the neighbor 
//     // run through a loop, then push it back to pokemon_with_neighbor
//     auto currIdx = teammate->index_[current_pokemon];
//     auto neighbors = teammate->teammates_[currIdx];
//     // for(int j =0 ; j < neighbor.size();j++) {
//     //   pokemon_with_neighbor.push_back(neighbor.at(j));
//     // }
//     for(auto x : neighbors) {
//         pokemon_with_neighbor.push_back(teammate->mons_[x.first]);
//     }
//     all_pokemon_with_neighbor.push_back(pokemon_with_neighbor);
//   // push pokemon_with_neightbor into al_pokemon_with_neighbor
//     pokemon_with_neighbor.clear();
// }

// // populate the matrix to how it should be 
// // set of pokemons inside the all_pokemon_with_neighbor, and include everything in the team
//  for(int i = 0; i < all_pokemon_with_neighbor.size(); i++) {
//       for(int j = 0; j < all_pokemon_with_neighbor.at(i).size(); j++) {
//         // We know that the result from generated team are for sure neighbors && we know that 
//         // first 6 element in all_pokemon_with_neighbot[0][j] are neighbors
//           std::vector<int> inner;
//        }
//     }  
// }

Graph::Graph(std::vector<std::map<unsigned, double>> teammate, double length, double threshold, unsigned limit, double cooling)
: graph_(teammate), length_(length), threshold_(threshold), limit_(limit), cooling_(cooling){
    pos_ = pos();
}

std::vector<std::pair<unsigned, unsigned>> Graph::pos(){
    std::vector<std::pair<unsigned, unsigned>> output(graph_.size());
    for (unsigned i = 0; i < graph_.size(); i++) {
        output.push_back(std::make_pair(i, i));
    }
    unsigned t = 0;
    while (t < limit_) {
        double maxForce = 0;
        std::vector<std::pair<unsigned, unsigned>> temp(graph_.size());
        for (unsigned start = 0; start < graph_.size(); start++) {
            double xForce = 0;
            double yForce = 0;
            for (auto neighbour: graph_[start]) {
                unsigned end = neighbour.first;
                std::pair<double, double> force = getForce(output[start], output[end]);
                xForce += force.first;
                yForce += force.second;
            }
            double mag = getMag(xForce, yForce);
            if (mag > maxForce) {
                maxForce = mag;
            }
            unsigned xPos = output[start].first + (cooling_*xForce);
            unsigned yPos = output[start].second + (cooling_*yForce);
            temp.push_back(std::make_pair(xPos, yPos));
        }
        output = temp;
        if (maxForce < threshold_) {
            break;
        }
        t++;
    }
    return output;
}
std::vector<std::pair<unsigned, unsigned>> Graph::getPos() const{
    return pos_;
}

std::pair<double, double> Graph::getForce(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end) const{
    double distance = getDistance(start, end);
    std::pair<double, double> unitVec = getUnitVec(start, end, distance);
    std::pair<double, double> rep = getRep(unitVec, distance);
    std::pair<double, double> attr = getAttr(unitVec, distance);
    return std::make_pair(rep.first + attr.first, rep.second + attr.second);
}
std::pair<double, double> Graph::getRep(const std::pair<double, double>& unitVec, double distance) const{
    double multiplier = (length_ * length_)/distance;
    return std::make_pair(unitVec.first * multiplier, unitVec.second * multiplier);
}
std::pair<double, double> Graph::getAttr(const std::pair<double, double>& unitVec, double distance) const{
    double multiplier = -(distance * distance)/length_;
    return std::make_pair(unitVec.first * multiplier, unitVec.second * multiplier);
}

double Graph::getDistance(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end) const{
    unsigned x = start.first - end.first;
    unsigned y = start.second - end.second;
    return getMag(x, y);
}
double Graph::getMag(double x, double y) const {
    unsigned xSquared = std::pow(x, 2);
    unsigned ySquared = std::pow(y, 2);
    return std::pow(double(xSquared + ySquared), 0.5);
}
std::pair<double, double> Graph::getUnitVec(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end, double distance) const{
    double x = double(start.first - end.first)/distance;
    double y = double(start.second - end.second)/distance;
    return std::make_pair(x, y);
}

