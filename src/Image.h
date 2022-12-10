/**
 * @file Image.h
 * Contains declaration of the interface for the Image class.
 */

#pragma once

#include <string>
using std::string;
#include <vector>
#include"cs225/PNG.h"

namespace cs225 {
    class Image : public PNG{
        public:
            Image & drawImage(std::vector<std::vector<int>> vect, Image & pic);
        private:
        //nothing in private
    };
}

