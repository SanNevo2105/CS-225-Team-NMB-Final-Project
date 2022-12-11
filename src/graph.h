#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include "StickerSheet.h"
#include"/workspaces/CS-225-Team-NMB-Final-Project/lib/cs225/PNG.h"

class Graph {
  public: 
    Graph(std::map<std::string, std::set<std::string>>& adjList, double length, double threshold, unsigned limit, double cooling);
    std::vector<std::pair<unsigned, unsigned>> pos();
    std::vector<std::pair<unsigned, unsigned>> getPos() const;
    Image drawImage(Image & pic, std::vector<std::string> teamStr);
  private:
    std::vector<std::vector<unsigned>> graph_;
    std::map<std::string, unsigned> indexes_;
    double length_;
    double threshold_;
    unsigned limit_;
    double cooling_;
    std::vector<std::string> mons_;
    std::vector<std::pair<unsigned, unsigned>> pos_;

    std::pair<double, double> getForce(const std::pair<double, double>& start, const std::pair<double, double>& end) const;
    std::pair<double, double> getRep(const std::pair<double, double>& unitVec, double distance) const;
    std::pair<double, double> getAttr(const std::pair<double, double>& unitVec, double distance) const;
    double getDistance(const std::pair<double, double>& start, const std::pair<double, double>& end) const;
    double getMag(double x, double y) const;
    std::pair<double, double> getUnitVec(const std::pair<double, double>& start, const std::pair<double, double>& end, double distance) const;
};
