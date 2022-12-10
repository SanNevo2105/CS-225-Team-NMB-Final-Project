#include "Image.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace cs225;

Image & Image::drawImage(std::vector<std::vector<unsigned>> vect, Image & pic, std::vector<std::pair<unsigned, unsigned>> pos){
    std::vector<unsigned> x_axis;
    std::vector<unsigned> y_axis;
    for(auto p: pos){
        x_axis.push_back(p.first);
        y_axis.push_back(p.second);
    }
    std::random_shuffle( x_axis.begin(), x_axis.end());

    
    unsigned y = 100;
    for(size_t j = 0; j < 1100; j = j + 20){
        y_axis.push_back(j);
    }
    std::random_shuffle( y_axis.begin(), y_axis.end());      //randomly assign coordinate to these pokemons
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

    for(unsigned i = 0; i < 3; i ++){                             //change to 2 in order to debug
        for(unsigned j = 0; j < 3; j++){
            if(vect[i][j] == 1){                              //draw line if there is connection
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
