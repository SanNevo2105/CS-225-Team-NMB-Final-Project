#include"Image.h"
#include <iostream>
#include <algorithm>
using namespace cs225;

Image & drawImage(vector<vector<int>> vect, Image & pic);{
    std::vector<int> x_axis;
    int x = 100;
    for(size_t i = 0; i < 54; j++){
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

    HSLAPixel & cur_pixel;
    for(size_t i = 0; i < 54; i ++){
        cur_pixel = pic.getPixel(x_axis[i], y_axis[i]);
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
            if(vect[i][j] = 1){
                cur_pixel = pic.getPixel(x_axis[i], y_axis[i]);
                HSLAPixel & target_pixel = pic.getPixel(x_axis[j], y_axis[j]);
                size_t start_x = x_axis[i];
                size_t start_y = y_axis[i];
                if(y_axis[i] > y_axis[j]){
                    int y_diff = (y_axis[i] - y_axis[j]);
                }
                else{
                    int y_diff = (y_axis[j] - y_axis[i]);
                }
                if(x_axis[i] > x_axis[j]){
                    int x_diff = (x_axis[i] - x_axis[j]);
                    start_x = x_axis[j];
                    start_y = y_axis[j];
                }
                else{
                    int x_diff = (x_axis[j] - x_axis[i]);     
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
    result.writeToFile("../myImage.png");
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



void Image::darken(){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 1; i < w ; i++){
        for(unsigned int j = 1; j < h ; j++){
            if((this->getPixel(i,j).l - 0.1 > 0) && (this->getPixel(i,j).l - 0.1 < 1)) {
                this->getPixel(i,j).l = this->getPixel(i,j).l - 0.1;
            }
            else{
                this->getPixel(i,j).l = 0;
            }
        }
    }   
}

void Image::darken(double amount){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            
            if((this->getPixel(i,j).l - amount > 0) && (this->getPixel(i,j).l - amount < 1)) {
                this->getPixel(i,j).l = this->getPixel(i,j).l - amount;
            }
            else{
                this->getPixel(i,j).l = 0;
            }
        }
    }    
}	

void Image::desaturate(){
    unsigned int w = width();
    unsigned int h = height();
   
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            
            if((this->getPixel(i,j).s - 0.1 > 0) && (this->getPixel(i,j).s - 0.1 < 1)) {
                this->getPixel(i,j).s = this->getPixel(i,j).s - 0.1;
            }
            else{
                this->getPixel(i,j).s = 0;
            }
        }
    }    
}

void Image::desaturate(double amount){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            
            if((this->getPixel(i,j).s - amount > 0) && (this->getPixel(i,j).s - amount < 1)) {
                this->getPixel(i,j).s = this->getPixel(i,j).s - amount;
            }
            else{
                this->getPixel(i,j).s = 0;
            }
        }
    }    
}	

void Image::grayscale(){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            this->getPixel(i,j).s = 0;
        }
    }    
}


void Image::illinify(){
    unsigned int w = width();
    unsigned int h = height();
    
    double orange;
    double blue;
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            
            orange = this->getPixel(i,j).h - 11;
            if(orange < 0){
                orange = orange * -1;
            }
            blue = this->getPixel(i,j).h - 216;
            if(blue < 0){
                blue = blue * -1;
            }
            if(orange > blue) {
                this->getPixel(i,j).h = blue;
            }
            else{
                this->getPixel(i,j).h = orange;
            }
        }
    }    
}	


void Image::lighten(){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 0; i < w ; i++){
        for(unsigned int j = 0; j < h ; j++){
            if((this->getPixel(i,j).l + 0.1 > 0) && (this->getPixel(i,j).l + 0.1 < 1)) {
                this->getPixel(i,j).l = this->getPixel(i,j).l + 0.1;
            }
            else{
                this->getPixel(i,j).l = 1;
            }
        }
    }   
}	


void Image::lighten(double amount){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 0; i < w ; i++){
        for(unsigned int j = 0; j < h ; j++){
            if((this->getPixel(i,j).l + amount > 0) && (this->getPixel(i,j).l + amount < 1)) {
                this->getPixel(i,j).l = this->getPixel(i,j).l + amount;
            }
            else{
                this->getPixel(i,j).l = 1;
            }
        }
    }    
}	


void Image::rotateColor(double degrees){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            
            if(this->getPixel(i,j).h + degrees > 360){
                this->getPixel(i,j).h = this->getPixel(i,j).h + degrees - 360; 
            }
            else if(this->getPixel(i,j).h + degrees < 0){
                this->getPixel(i,j).h = this->getPixel(i,j).h + degrees + 360;
            }
            else if((this->getPixel(i,j).h + degrees < 360)&&(this->getPixel(i,j).h + degrees > 0)){
                this->getPixel(i,j).h = this->getPixel(i,j).h + degrees;
            }
        }
    }    
}	


void Image::saturate(){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            
            if((this->getPixel(i,j).s + 0.1 > 0) && (this->getPixel(i,j).s + 0.1 < 1)) {
                this->getPixel(i,j).s = this->getPixel(i,j).s + 0.1;
            }
            else{
                this->getPixel(i,j).s = 1;
            }
        }
    }    
}	


void Image::saturate(double amount){
    unsigned int w = width();
    unsigned int h = height();
    
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            
            if((this->getPixel(i,j).s + amount > 0) && (this->getPixel(i,j).s + amount < 1)) {
                this->getPixel(i,j).s = this->getPixel(i,j).s + amount;
            }
            else{
                this->getPixel(i,j).s = 1;
            }
        }
    }    
}	


void Image::scale(double factor){
    unsigned int oldw = width();
    unsigned int oldh = height();
    unsigned int w = width() * factor;
    unsigned int h = height() * factor;
    HSLAPixel * oldImageData = new HSLAPixel[width() * height()];
    for(unsigned int i =0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & oldPixel = this->getPixel(i, j);
            HSLAPixel & copyPixel = oldImageData[ (i + (j * width())) ];
            copyPixel = oldPixel;
        }
    }
    
    
    resize(w, h);
    for(unsigned int m = 0; m < w; m++){                        //m is width, n is height
        for(unsigned int n = 0; n < h; n++){
            
            int originwidth = m/factor;
            int originheight = n/factor;

            double exactwidth = m/factor;
            double exactheight = n/factor;

            if(exactwidth - originwidth > originwidth + 1 - exactwidth){
                
                if(exactheight - originheight > originheight + 1 - exactheight){
                    this->getPixel(m, n) = oldImageData[(originwidth + originheight * oldw)];
                    //HSLAPixel & fitone = oldImageData[(originwidth + originheight * oldw)];
                    //this->getPixel(m, n).h = fitone.h;
                    //this->getPixel(m, n).l = fitone.l;
                    //this->getPixel(m, n).s = fitone.s;
                    //this->getPixel(m, n).a = fitone.a;                   
                }
                
                else{
                    this->getPixel(m, n) = oldImageData[(originwidth + (originheight+1) * oldw)];
                }
                
            }
            
            else{
                if(exactheight - originheight > originheight + 1 - exactheight){
                    this->getPixel(m, n) = oldImageData[(originwidth + 1 + originheight * oldw)];                   
                }
                else{
                    //if((originwidth + 1 + (originheight+1) * oldw)>=){
                        //std::cout<<"hello";
                    //}
                    //this->getPixel(m, n) = oldImageData[(originwidth + 1 + (originheight+1) * oldw)];
                    this->getPixel(m, n) = oldImageData[(originwidth + (originheight) * oldw)];
                }
            }
            
            //HSLAPixel & copyPixel = oldImageData[ (i + (j * width())) ];
        }
    }
    delete[] oldImageData;
}	


void Image::scale(unsigned w, unsigned h){
    unsigned int oldw = width();
    unsigned int oldh = height();
    
    double factorh = (double) h/ (double) height();   
    double factorw = (double) w/(double) width();

    if(factorw>factorh){
        scale(factorh);
    }
    else{
        scale(factorw);
    }
}

