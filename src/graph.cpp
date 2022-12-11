#include "graph.h"
#include <cmath>
#include <assert.h>

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
    // for (unsigned i = 0; i < graph_.size(); i++) {
    //     std::cout << i << ": ";
    //     for (auto g:graph_[i]) {
    //         std::cout << g << ", ";
    //     }
    //     std::cout << std::endl;
    // }
    pos_ = pos();
}

cs225::PNG & Graph::drawImage(cs225::PNG & pic){
    std::vector<int> x_axis;
    std::vector<int> y_axis;
    for(auto p: pos_){
        x_axis.push_back(p.first);
        y_axis.push_back(p.second);
    }
     //randomly assign coordinate to these pokemons
    std::vector<int> length_for_layer = {6,5,4,3,2,1};
    //HSLAPixel & cur_pixel = HSLAPixel();
    for(size_t i = 0; i < graph_.size(); i ++){                         //draw these pokemons first;
        pic.getPixel(x_axis[i], y_axis[i]).l = 0;
        //cur_pixel.l = 0;   
        for(int k = 1; k < 7; k ++){
            if(x_axis[i]+k <= 1800){
                for(int w = length_for_layer[k - 1]; w > 0; w-- ){
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
                for(int w = length_for_layer[k - 1]; w > 0; w-- ){
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
            int y_diff, x_diff;
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
                
            int A = 2 * y_diff;
            int B = A - 2 * x_diff;
            int P = A - x_diff;
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
    std::vector<std::pair<double, double>> output;
    //1800, 1200
    //std::cout << "size: " << graph_.size() << std::endl;
    for (unsigned i = 0; i < graph_.size(); i++) {
        double x = rand() % 1800;
        double y = rand() % 1200;
        output.push_back(std::make_pair(x, y));
    }
    unsigned t = 0;
    double xNeg = 0;
    double yNeg = 0;
    while (t < limit_) {
        //std::cout << "enter loop" << std::endl;
        double maxForce = 0;
        xNeg = 0;
        yNeg = 0;
        std::vector<std::pair<double, double>> temp;
        for (unsigned start = 0; start < graph_.size(); start++) {
            double xForce = 0;
            double yForce = 0;
            //std::cout << graph_[start].size() << std::endl;
            for (auto end: graph_[start]) {
                //std::cout << "end: " << end << std::endl;
                std::pair<double, double> force = getForce(output[start], output[end]);
                //std::cout << "start: " << output[start].first << ", " << output[start].second << std::endl;
                //std::cout << "end: " << output[end].first << ", " << output[end].second << std::endl;
                xForce += force.first;
                yForce += force.second;
                //std::cout << "force: " << force.first << ", " << force.second << std::endl;
            }
            double mag = getMag(xForce, yForce);
            if (mag > maxForce) {
                maxForce = mag;
            }
            //std::cout << mag << std::endl;
            double xPos = output[start].first + (cooling_*xForce);
            double yPos = output[start].second + (cooling_*yForce);
            if (xPos < xNeg) {
                xNeg = xPos;
            }
            if (yPos < yNeg) {
                yNeg = yPos;
            }
            temp.push_back(std::make_pair(xPos, yPos));
        }
        output = temp;
        if (maxForce < threshold_) {
            break;
        }
        //break;
        t++;
    }
    std::vector<std::pair<unsigned, unsigned>> result;
    double multiplier = 1;
    for (unsigned i = 0; i < output.size(); i++) {
        auto p = output[i];
        output[i]=std::make_pair(p.first - xNeg, p.second - yNeg);
        if (1500/(p.first - xNeg) < multiplier) {
            multiplier = 1500/(p.first - xNeg);
        }
        if (1000/(p.second - yNeg) < multiplier) {
            multiplier = 1000/(p.second - yNeg);
        }
    }
    //std::cout << "multiplier: " << multiplier << std::endl;
    for (auto p:output) {
        result.push_back(std::make_pair(100+p.first * multiplier, 50+p.second * multiplier));
        //std::cout << p.first * multiplier << ", " << p.second * multiplier << std::endl;
    }
    return result;
}
std::vector<std::pair<unsigned, unsigned>> Graph::getPos() const{
    return pos_;
}

std::pair<double, double> Graph::getForce(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end) const{
    double distance = getDistance(start, end);
    if (distance == 0) {
        return std::make_pair(0, 0);
    }
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
    //std::cout << "start: " << start.first << ", " << start.second << std::endl;
    //std::cout << "end: " << end.first << ", " << end.second << std::endl;
    
    int x = start.first - end.first;
    int y = start.second - end.second;
    //std::cout << "x: " << x << ", y: " << y << std::endl;
    double distance = getMag(x, y);
    //assert(distance > 0);
    return distance;
}
double Graph::getMag(double x, double y) const {
    unsigned xSquared = x * x;
    unsigned ySquared = y * y;
    assert(xSquared >= 0);
    assert(ySquared >= 0);
    //std::cout << xSquared << ", " << ySquared << std::endl;
    return std::pow(double(xSquared + ySquared), 0.5);
}
std::pair<double, double> Graph::getUnitVec(const std::pair<unsigned, unsigned>& start, const std::pair<unsigned, unsigned>& end, double distance) const{
    double x = double(start.first - end.first)/distance;
    double y = double(start.second - end.second)/distance;
    return std::make_pair(x, y);
}

