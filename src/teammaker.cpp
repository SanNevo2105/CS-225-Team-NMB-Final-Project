#include "teammaker.h"
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <stack>

using namespace std; 

TeamMaker::TeamMaker(const std::string& teamFile, const std::string& usageFile){

std::vector<std::tuple<std::string, std::map<std::string, double>, double>> result = teammatesParser(teamFile);

//string corresponds to the get<0> result.at(i);
//unsinged is just from 0 to vector.size();
for(int i = 0; i < result.size(); i++) {
    // populate the index_
    index_[get<0> (result.at(i))] =  i;
}
// populating the teammates_ private variable
// std::vector<std::map<unsigned, double>> teammates_;
// the unsinged in the map of teammates correponds to the string(key) in the map of index
// converting string to unsinged --- use stoul
// std::vector<std::string> key_in_index;
// for (std::map<std::string, unsigned>::iterator it=index_.begin() ; it != index_.end(); ++it )
// {
// key_in_index.push_back(index_.first)
// }

// std::vector<unsigned int> teammates_key;
// for(unsigned int i = 0; i < key_in_index.size(); i++) {
//     unsigned int x = std::stoul(key_in_index.at(i), nullptr, 0);
//     teammates_key.push_back(x);
// }

// getting the double from the map in result
// goes through the result vector, then go to the tuples position, then go to the map and obtain the info
std::vector<double> value_in_teammate;

// loop through the vector, then get the tuple position, then get the map, insert the map into a new vector of map
// get the value from the vector of map

for(int i = 0; i < result.size(); i++) {
    // gets the tuple position and then the value in the map
    value_in_teammate.push_back(get<1>(result.at(i)).second);
}
// map is a vector of pairs  


// now I have all the info I need to populate teammates_

std::map<unsigned, double> inner;
for(int i = 0; i < value_in_teammate; i++) {
    inner.insert(i,value_in_teammate.at(i));
    teammates_.push_back(inner);
}

// populating the viability 
for(int i = 0; i < result.size(); i++) {
viability_.push_back(get<2> result.at(i));
}

// populating usage
std::map<std::string, double> match = usageParser(usageFile);
// iterates through the map, then push the value into private variable usage
for (std::map<std::string, double>::iterator it=match.begin() ; it != match.end(); ++it )
{
usage.push_back(it.second);
}
}

std::vector<std::tuple<std::string, std::map<std::string, double>, double>> TeamMaker::teammatesParser(const std::string& fileName){
    std::ifstream textFile(fileName);
    std::string line;
    std::vector<std::tuple<std::string, std::map<std::string, double>, double>> result;
    unsigned plusCount = 0;
    if (textFile.is_open()){
        //initialize these variable first since they have to be retained outside of the while loop
        std::string name;
        double viabilityCeiling = 0;
        //go through each line
        while (getline(textFile, line)) {
            //counting the number of + in front of the line to see which section of the entry it is
            if (line[1] == '+') {
                plusCount++;
                //once found the name line
                if (plusCount%9 == 1) {
                    getline(textFile, line);
                    //i is the starting index of the substring
                    unsigned i = 0;
                    while (line[i] == '|' || line[i] == ' ') {
                        i++;
                    }
                    //j is the ending index of the substring
                    //this will be the convention throughout this function
                    unsigned j = line.size();
                    while (line[j-1] == ' ' || line[j-1] == '|') {
                        j--;
                    }
                    name = line.substr(i, j-i);
                }
                //once found the viability ceiling
                if (plusCount%9 == 2) {
                    //first, skip 3 lines
                    getline(textFile, line);
                    getline(textFile, line);
                    getline(textFile, line);
                    unsigned j = line.size();
                    while (line[j-1] == ' ' || line[j-1] == '|') {
                        j--;
                    }
                    unsigned i = j;
                    while (line[i-1] != ' ') {
                        i--;
                    }
                    
                    viabilityCeiling = std::stod(line.substr(i, j-i)) * 0.01;
                }
                //once found teammates
                if (plusCount%9 == 7) {
                    //skip 2 lines
                    getline(textFile, line);
                    getline(textFile, line);
                    std::map<std::string, double> teammates;
                    while (line[1] != '+') {
                        double percent = 0;
                        unsigned j = line.size();
                        while (line[j-1] == '|' || line[j-1] == '%' || line[j-1] == ' ') {
                            j--;
                        }
                        unsigned i = j;
                        while(line[i-1] != ' ') {
                            i--;
                        }
                        percent = std::stod(line.substr(i, j-i)) * 0.01;
                        i--;
                        std::string pokemon = line.substr(3, i-3);
                        teammates[pokemon] = percent;
                        getline(textFile, line);
                    }
                    //have to increment the plus count since another + has been spotted
                    plusCount++;
                    result.push_back(std::make_tuple(name, teammates, viabilityCeiling));
                }
            }
        }
    } else {
        std::__throw_runtime_error("cannot open file");
    }
    return result;
}

std::map<std::string, double> TeamMaker::usageParser(const std::string& fileName){
    std::string line;
    std::ifstream myfile(fileName);
    std::map<std::string, double> match;
    int counter = 0; 
    int end = 0;
    int start = 0;
    if(myfile){
        while(getline(myfile, line)){
            while(line[counter] != ' '){
                counter ++;
            }
            counter ++;
            start = counter;                   //find the name right after the space
            while(line[counter] != ','){
                counter ++;
            }
            int length = counter - start;                 //find the last letter of the name
            std::string pokemon = line.substr(start, length);
            
            while(pokemon[pokemon.length()-1] == ' '){
                pokemon.pop_back();
            }
            start = counter;              //get percentage
            counter++;
            while(line[counter] != ','){
                counter++;
            }
            length = counter - start;
            double usage = std::stod(line.substr(start + 1, length));
            //std::cout<< pokemon <<" "<< usage << std::endl;
            match[pokemon] = usage; 

            counter = 0;
            start = 0;
            end = 0;
        }
        myfile.close();
    }
    else std::cout << "cannot open the file\n";
    return match;
}

TeamMaker::~TeamMaker(){}

bool TeamMaker::dfs(unsigned start, unsigned key){
    bool* traverse = new bool[index_.size()];
    std::stack<unsigned> pkmnStack;
    pkmnStack.push(start);
    traverse[start] = true;
    while (!pkmnStack.empty()) {
        unsigned curr = pkmnStack.top();
        if (curr == key) {
            return true;
        }
        std::map<unsigned, double> t = teammates_[curr];
        pkmnStack.pop();
        for (auto p:t) {
            if (!traverse[p.first]) {
                traverse[p.first] = true;
                pkmnStack.push(p.first);
            }
        }
    }
    
    return false;
}

std::vector<std::vector<double>> TeamMaker::floydWarshall(){
    return std::vector<std::vector<double>>();
}

std::vector<std::string> TeamMaker::generateTeam(const std::string& pokemons){
    return std::vector<std::string>();
}
