#pragma once
#include <string>
#include <vector>
#include <map>

class Graph {
  public: 
    Graph(std::vector<std::map<unsigned, double>> teammate, double length, double threshold, unsigned limit, double cooling);
    std::vector<std::pair<unsigned, unsigned>> graphicOutput();
    std::vector<std::pair<unsigned, unsigned>> getOutput() const;
  private:
    std::vector<std::map<unsigned, double>> graph_;
    double length_;
    double threshold_;
    unsigned limit_;
    double cooling_;
    std::vector<std::pair<unsigned, unsigned>> graphicOutput_;

    std::pair<double, double> getForce(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end) const;
    std::pair<double, double> getRep(const std::pair<double, double>& unitVec, double distance) const;
    std::pair<double, double> getAttr(const std::pair<double, double>& unitVec, double distance) const;
    double getDistance(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end) const;
    double getMag(double x, double y) const;
    std::pair<double, double> getUnitVec(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end, double distance) const;
};
