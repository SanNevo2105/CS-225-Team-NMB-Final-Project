#include"Image.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace cs225;

Image & drawImage(std::vector<std::vector<int>> vect, Image & pic){
    std::vector<int> x_axis;
    int x = 100;
    for(size_t i = 0; i < 54; i++){
        x = (x + rand() * rand()) % 1800;
        x_axis.push_back(x);
    }
    std::random_shuffle( x_axis.begin(), x_axis.end());

    std::vector<int> y_axis;
    int y = 100;
    for(size_t j = 0; j < 54; j ++){
        y = (y + rand() * rand()) % 1200;
        y_axis.push_back(y);
    }
    std::random_shuffle( y_axis.begin(), y_axis.end());

    //HSLAPixel & cur_pixel = HSLAPixel();
    for(size_t i = 0; i < 54; i ++){
        HSLAPixel & cur_pixel = pic.getPixel(x_axis[i], y_axis[i]);
        cur_pixel.l = 0;
        if(x_axis[i]+1 < 1800){
            cur_pixel = pic.getPixel(x_axis[i]+1, y_axis[i]);
            cur_pixel.l = 0;
        }
        if(x_axis[i]-1 > 0){
            cur_pixel = pic.getPixel(x_axis[i]-1, y_axis[i]);
            cur_pixel.l = 0;
        }
        if(y_axis[i]+1 < 1200){
            cur_pixel = pic.getPixel(x_axis[i], y_axis[i]+1);
            cur_pixel.l = 0;
        }
        if(y_axis[i]-1 > 0){
            cur_pixel = pic.getPixel(x_axis[i], y_axis[i]-1);
            cur_pixel.l = 0;
        }
    }

    for(int i = 0; i < 54; i ++){
        for(int j = 0; j < 54; j++){
            if(vect[i][j] == 1){
                HSLAPixel & cur_pixel = pic.getPixel(x_axis[i], y_axis[i]);
                HSLAPixel & target_pixel = pic.getPixel(x_axis[j], y_axis[j]);
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
                for(int i=start_x; i < x_diff; i ++){
                    if(P < 0){
                        P = A + P;
                        pic.getPixel(start_x + 1, start_y).l = 0;
                    }
                    else{
                        P = B + P;
                        pic.getPixel(start_x + 1, start_y + 1).l = 0;
                    }
                }
            }
        }
    }
    pic.writeToFile("../myImage.png");
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
