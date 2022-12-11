#include "Image.h"
#include <algorithm>

void Image::lighten () {
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.l + 0.1 <= 1) {
                pixel.l = pixel.l + 0.1;
            } else {
                pixel.l = 1;
            }
        }
    }
}
void Image::lighten (double amount){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.l + amount <= 1 && pixel.l + amount >= 0) {
                pixel.l = pixel.l + amount;
            } else if (pixel.l + amount > 1) {
                pixel.l = 1;
            } else {
                pixel.l = 0;
            }
        }
    }
}
void Image::darken (){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.l - 0.1 >= 0) {
                pixel.l -= 0.1;
            } else {
                pixel.l = 0;
            }
        }
    }
}
void Image::darken (double amount){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.l - amount <= 1 && pixel.l - amount >= 0) {
                pixel.l -= amount;
            } else if (pixel.l - amount < 0) {
                pixel.l = 0;
            } else {
                pixel.l = 1;
            }
        }
    }
}
void Image::saturate (){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.s + 0.1 <= 1) {
                pixel.s += 0.1;
            } else {
                pixel.s = 1;
            }
        }
    }
}
void Image::saturate (double amount){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.s + amount <= 1 && pixel.s + amount >= 0) {
                pixel.s += amount;
            } else if (pixel.s + amount > 1) {
                pixel.s = 1;
            } else {
                pixel.s = 0;
            }
        }
    }
}
void Image::desaturate (){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.s - 0.1 >= 0) {
                pixel.s -= 0.1;
            } else {
                pixel.s = 0;
            }
        }
    }
}
void Image::desaturate (double amount){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.s - amount <= 1 && pixel.s - amount >= 0) {
                pixel.s -= amount;
            } else if (pixel.s - amount < 0) {
                pixel.s = 0;
            } else {
                pixel.s = 1;
            }
        }
    }
}
void Image::grayscale (){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}
void Image::rotateColor (double degrees){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.h += degrees;
            while (pixel.h>360){
                pixel.h=pixel.h-360;
            } 
            while (pixel.h<0){
                pixel.h=pixel.h+360;
            }    
        }
    }
}
void Image::illinify (){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (abs((int)(pixel.h - 11)) < abs((int)(pixel.h - 216))) {
                pixel.h = 11;
            } else {
                pixel.h = 216;
            }
        }
    }
}
void Image::scale (double factor){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    unsigned int width_new = width * factor;
    unsigned int height_new = height * factor;
    cs225::HSLAPixel* tmp = new cs225::HSLAPixel[width * height];
    for (unsigned int y = 0; y < height; y++){
        for (unsigned int x = 0; x < width; x++){
            unsigned index = x + (y * width);
            double h = getPixel(x, y).h;
            double s = getPixel(x, y).s;
            double l = getPixel(x, y).l;
            double a = getPixel(x, y).a;
            tmp[index] = cs225::HSLAPixel(h,s,l,a);
        }
    }
    resize(width_new, height_new);
    for (unsigned int y = 0; y < height_new; y++){
        for (unsigned int x = 0; x < width_new; x++){
        unsigned int x_factor = (unsigned int )(x/factor);
        unsigned int y_factor = (unsigned int )(y/factor);
        unsigned index = x_factor + (y_factor  * width);
        double h = tmp[index].h;
        double s = tmp[index].s;
        double l = tmp[index].l;
        double a = tmp[index].a;
        getPixel(x,y) = cs225::HSLAPixel(h,s,l,a);
        }
    }
    delete[] tmp;
}
void Image::scale (unsigned w, unsigned h){
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    double factor = std::min((double)w/(double)width, (double)h/(double)height);
    scale(factor);
}
  
