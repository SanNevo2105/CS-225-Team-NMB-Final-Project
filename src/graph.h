#pragma once
#include <string>
#include <vector>
#include <map>
#include"cs225/PNG.h"

class Graph {
  public: 
    Graph(std::map<std::string, std::vector<std::string>>& adjList, double length, double threshold, unsigned limit, double cooling);
    std::vector<std::pair<unsigned, unsigned>> pos();
    std::vector<std::pair<unsigned, unsigned>> getPos() const;
    cs225::PNG & drawImage(cs225::PNG & pic);
  private:
    std::vector<std::vector<unsigned>> graph_;
    double length_;
    double threshold_;
    unsigned limit_;
    double cooling_;
    std::vector<std::string> mons_;
    std::vector<std::pair<unsigned, unsigned>> pos_;

    std::pair<double, double> getForce(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end) const;
    std::pair<double, double> getRep(const std::pair<double, double>& unitVec, double distance) const;
    std::pair<double, double> getAttr(const std::pair<double, double>& unitVec, double distance) const;
    double getDistance(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end) const;
    double getMag(double x, double y) const;
    std::pair<double, double> getUnitVec(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end, double distance) const;
};
