#include "graph.h"
#include <cmath>

Graph::Graph(std::map<std::string, std::vector<std::string>>& adjList, double length, double threshold, unsigned limit, double cooling)
: length_(length), threshold_(threshold), limit_(limit), cooling_(cooling){
    std::map<std::string, unsigned> indexes;
    unsigned i = 0;
    for (auto mon:adjList) {
        mons_.push_back(mon.first);
        indexes[mon.first] = i;
        i++;
    }
    for (auto mon:adjList) {
        std::vector<unsigned> neighbours;
        for (auto n:mon.second) {
            if (n != mon.first) {
                neighbours.push_back(indexes[n]);
            }
        }
        graph_.push_back(neighbours);
    }
    pos_ = pos();
}

cs225::PNG & Graph::drawImage(cs225::PNG & pic, std::vector<std::pair<unsigned, unsigned>> pos){
    std::vector<unsigned> x_axis;
    std::vector<unsigned> y_axis;
    for(auto p: pos){
        x_axis.push_back(p.first);
        y_axis.push_back(p.second);
    }
     //randomly assign coordinate to these pokemons
    std::vector<unsigned> length_for_layer = {6,5,4,3,2,1};
    //HSLAPixel & cur_pixel = HSLAPixel();
    for(size_t i = 0; i < 54; i ++){                         //draw these pokemons first;
        pic.getPixel(x_axis[i], y_axis[i]).l = 0;
        //cur_pixel.l = 0;   
        for(unsigned k = 1; k < 7; k ++){
            if(x_axis[i]+k <= 1800){
                for(unsigned w = length_for_layer[k - 1]; w > 0; w-- ){
                    if(y_axis[i]+w <= 1200){
                        pic.getPixel(x_axis[i]+k, y_axis[i]+w).l = 0;
                    }
                    if(y_axis[i]-w > 0){
                        pic.getPixel(x_axis[i]+k, y_axis[i]-w).l = 0;
                    }
                }
                pic.getPixel(x_axis[i]+k, y_axis[i]).l = 0;
            }

            if(x_axis[i]-k > 0){
                for(unsigned w = length_for_layer[k - 1]; w > 0; w-- ){
                    if(y_axis[i]-w > 0){
                        pic.getPixel(x_axis[i]-k, y_axis[i]-w).l = 0;
                    }
                    if(y_axis[i]+w <= 1200){
                        pic.getPixel(x_axis[i]-k, y_axis[i]+w).l = 0;
                    }
                }
                pic.getPixel(x_axis[i]-k, y_axis[i]).l = 0;     
            }
            if(y_axis[i]+k <= 1200){
                pic.getPixel(x_axis[i], y_axis[i]+k).l = 0;
            }
            if(y_axis[i]-k > 0){
                pic.getPixel(x_axis[i], y_axis[i]-k).l = 0;
            }
        }        
    }                   
    for (unsigned i = 0; i < graph_.size(); i++){
        for (unsigned j: graph_[i]){
                                        //draw line if there is connection
            //HSLAPixel & cur_pixel = pic.getPixel(x_axis[i], y_axis[i]);
            //HSLAPixel & target_pixel = pic.getPixel(x_axis[j], y_axis[j]);
            size_t start_x = x_axis[i];
            size_t start_y = y_axis[i];
            unsigned y_diff, x_diff;
            if(y_axis[i] > y_axis[j]){
                y_diff = (y_axis[i] - y_axis[j]);
            }
            else{
                y_diff = (y_axis[j] - y_axis[i]);
            }
            if(x_axis[i] > x_axis[j]){
                x_diff = (x_axis[i] - x_axis[j]);
                start_x = x_axis[j];
                start_y = y_axis[j];
            }
            else{
                x_diff = (x_axis[j] - x_axis[i]);     
            }
                
            unsigned A = 2 * y_diff;
            unsigned B = A - 2 * x_diff;
            unsigned P = A - x_diff;
            size_t final_x = start_x + x_diff;
            for(size_t i=start_x; i < final_x; i ++){
                if(P < 0){
                    P = A + P;
                    pic.getPixel(start_x + 1, start_y).l = 0;
                    start_x++;
                }
                else{
                    P = B + P;
                    pic.getPixel(start_x + 1, start_y - 1).l = 0;
                    start_x++;
                    start_y--;
                }
            }
        }
    }
    return pic;

/*One way that a computer can know which pixels to colour, is with Brensenham’s
Line Algorithm. It follows these simple rules:
A = 2× change in Y value
B = A − 2× change in X value
P = A− change in X value
Fill the starting pixel. Then for every position along the X axis:
• if P is less than 0, draw the new pixel on the same line as the last pixel,
and add A to P.
• if P was 0 or greater, draw the new pixel one line higher than the last
pixel, and add B to P.
• continue this process until we reach the end of the line.
Without using a ruler, use Bresenham’s Line Algorithm to draw a straight
line from A to B:*/

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
                unsigned end = neighbour;
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

