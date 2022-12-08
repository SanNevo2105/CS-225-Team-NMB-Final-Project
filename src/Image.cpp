#include"Image.h"
#include <iostream>
using namespace cs225;

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
