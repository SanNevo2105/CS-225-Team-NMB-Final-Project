/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include <string>
using std::string;
#include <vector>

//#include"/workspaces/cs225/CS-225-Team-NMB-Final-Project-main/White_full.png"
//#include"PNG.h"
#include"/workspaces/CS-225-Team-NMB-Final-Project/cs225/PNG.h"

namespace cs225 {
    class Image : public PNG{
        public:
            Image & drawImage(std::vector<std::vector<int>> vect, Image & pic);
            /*void darken();
            void darken(double amount);
            void desaturate();
            void desaturate(double amount);
            void grayscale();
            void illinify();
            void lighten();
            void lighten(double amount);
            void rotateColor(double degrees);
            void saturate();
            void saturate(double amount);
            void scale(double factor);
            void scale(unsigned w, unsigned h);*/
            

        private:
        //nothing in private
    };


}
