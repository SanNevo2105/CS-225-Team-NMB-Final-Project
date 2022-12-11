#include "StickerSheet.h"
#include <algorithm>

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    pic = new Image(picture);
    cap = max;
    stickers = new Image*[cap];
    xPos = new unsigned[cap];
    yPos = new unsigned[cap];
    for (unsigned i = 0; i < cap; i++) {
        stickers[i] = nullptr;
    }
}
void StickerSheet::_clear(){
    for (unsigned i = 0; i < cap; i++) {
      if (stickers[i] != nullptr) {
        delete stickers[i];
        stickers[i] = nullptr;
      }
    }
    delete[] stickers;
    delete[] xPos;
    delete[] yPos;
    delete pic;
    stickers = nullptr;
    xPos = nullptr;
    yPos = nullptr;
    pic = nullptr;
    cap = 0;
}
void StickerSheet::_copy(const StickerSheet &other){
    pic = new Image(*other.pic);
    cap = other.cap;
    stickers = new Image*[cap];
    xPos = new unsigned[cap];
    yPos = new unsigned[cap];
    for (unsigned i = 0; i < cap; i++) {
        if (other.stickers[i] != nullptr) {
            stickers[i] = new Image(*other.stickers[i]);
        } else {
            stickers[i] = nullptr;
        }
        xPos[i] = other.xPos[i];
        yPos[i] = other.yPos[i];
    }
}
StickerSheet::~StickerSheet (){
    _clear();
}
StickerSheet::StickerSheet (const StickerSheet &other){
    _copy(other);
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    if (this != &other) { 
        _clear();
        _copy(other); 
    }
    return *this;
}
void StickerSheet::changeMaxStickers (unsigned max){
    Image** newStickers = new Image*[max];
    for (unsigned i = 0; i < max; i++) {
        newStickers[i] = nullptr;
    }
    unsigned* newXPos = new unsigned[max];
    unsigned* newYPos = new unsigned[max];
    unsigned m = cap;
    if(cap > max) {
        m = max;
    }
    for (unsigned i = 0; i < m; i++) {
        if (stickers[i] != nullptr) {
            newStickers[i] = new Image(*stickers[i]);
            newXPos[i] = xPos[i];
            newYPos[i] = yPos[i];
        }    
    }
    for (unsigned i = 0; i < cap; i++) {
      if (stickers[i] != nullptr) {
        delete stickers[i];
        stickers[i] = nullptr;
      }
    }
    delete[] stickers;
    delete[] xPos;
    delete[] yPos;
    xPos = newXPos;
    yPos = newYPos;
    cap = max;
    stickers = newStickers;
}
unsigned StickerSheet::lowest_index(){
    for (unsigned i = 0; i < cap; i++) {
        if (stickers[i] == nullptr) {return i;}
    }
    return cap;
}
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
    unsigned index = lowest_index();
    if (index == cap) {
        return -1;
    }
    stickers[index] = new Image(sticker);
    xPos[index] = x;
    yPos[index] = y;
    return index;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
    if (index > cap || stickers[index] == nullptr) {
        return false;
    }
    xPos[index] = x;
    yPos[index] = y;
    return true;
}
void StickerSheet::removeSticker (unsigned index){
    if (index < cap && stickers[index] != nullptr) {
        delete stickers[index];
        stickers[index] = nullptr;
        xPos[index] = 0;
        yPos[index] = 0;
    }
}
Image * StickerSheet::getSticker (unsigned index){
    if (index > cap || stickers[index] == nullptr) {
        return NULL;
    }
    return stickers[index];
}
Image StickerSheet::render () const{
    Image image = Image(*pic);
    unsigned width = pic->width();
    unsigned height = pic->height();
    for (unsigned i = 0; i < cap; i++) {
        if (stickers[i] != nullptr) {
            width = std::max(width, xPos[i] + stickers[i]->width());
            height = std::max(height, yPos[i] + stickers[i]->height());
        }
    }
    if (width != pic->width() || height != pic->height()) {
        image.resize(width, height);
    }

    for (unsigned i = 0; i < cap; i++) {
        if (stickers[i]!=nullptr) {
            for (unsigned y = 0; y < stickers[i]->height(); y++) {
                for (unsigned x = 0; x < stickers[i]->width(); x++) {
                    if (stickers[i]->getPixel(x, y).a != 0) {
                        double h = stickers[i]->getPixel(x, y).h;
                        double s = stickers[i]->getPixel(x, y).s;
                        double l = stickers[i]->getPixel(x, y).l;
                        double a = stickers[i]->getPixel(x, y).a;
                        image.getPixel(xPos[i] + x,yPos[i] + y) = cs225::HSLAPixel(h,s,l,a);
                    }
                }
            }
        }
    }
    return image;
}

