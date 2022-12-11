# CS-225-Team-NMB-Final-Project

# Data
We are using the dataset from https://www.smogon.com/stats/, a website which contents data for pokemon. And we use this version of the data:
https://www.smogon.com/stats/2022-10/gen8ou-1825.txt
https://www.smogon.com/stats/2022-10/moveset/gen8ou-1825.txt
. Mainly focusing on the percentage and possibility of one pokemon being on a team with another, and their usage percent as an individual. 

# Repo Structure

# Deliverables

Datasets are stored as txt files.
Tests are in /tests
Project Proposal, Contract, etc can be found in /documents
The major files that contains our function is placed with src

# Running Instructions
The code can be ran inside Docker, and if you need help setting it up, you can go here.

# Executable
To use the pokemon team generator program that we wrote, you would need to mkdir build, cd build and cmake .. to make the build file before run make , then ./main. 
We call all the functions in main.cpp for you (through a fleshed-out utils.cpp that will print clear instructions on what your user input should be). The required inputs for each of the functionality are as follows:

DFS 	
Input: The index of pokemon that we are starting at and index of the second pokemon that we are trying to reach
Output: a boolean that determines whether there is a path between these two pokemons, or whether they are connected.

Floyd Warshall
Input: None
Output: None 
Functionality: This function is a void function, and the purpose of this function is to build the 2D vector of the weights of the pokemons. 

Force Directed Graph Drawing 
Input: 
The adjacency list
The length of the line
The threshold of the force
The cooling factor 
Output: 
The coordinates of the pokemons on the graph.
 
# Tests
To run the test cases, run make test then ./test in the root directory.
We constructed different dataset, going from small to large, for which we wrote test cases on. We broke down the larger dataset into a small one, where we used to test the functions and debug. The test cases mainly focus on parsing the dataset, Depth First Search, Floyd Warshall algorithm, and Force Directed Graph Drawing algorithm. 
Team

Ming Yi(myi22)
Zhuoyuan Li(zl70)
Nobt Komolkhetruck (tk14)
