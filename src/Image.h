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
            Image & drawImage(std::vector<std::vector<unsigned>> vect, Image & pic, std::vector<std::pair<unsigned, unsigned>> pos);
        private:
        //nothing in private
    };
}

