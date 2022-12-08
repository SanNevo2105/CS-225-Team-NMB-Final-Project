/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include <string>
using std::string;

//#include"/workspaces/CS225/release-f22-main/mp_stickers/lib/cs225/PNG.h"   //when grading on pl, what should this be?
//#include"PNG.h"
#include"cs225/PNG.h"

namespace cs225 {
    class Image : public PNG{
        public:
            void darken();
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
            void scale(unsigned w, unsigned h);

        private:
        //nothing in private
    };
}
