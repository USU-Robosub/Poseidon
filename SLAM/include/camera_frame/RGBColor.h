//
// Created by Kyler Jensen on 2/22/17.
//

#ifndef SLAM_RGBCOLOR_H
#define SLAM_RGBCOLOR_H

#include <iostream>
#include "types.h"

namespace slam {

    struct RGBColor {

        uchar red;
        uchar green;
        uchar blue;

        bool operator ==(const RGBColor other) const {
            return this->red == other.red &&
                   this->blue == other.blue &&
                   this->green == other.green;
        }

        bool operator !=(const RGBColor other) const {
            return !(*this == other);
        }

        /**
         * Returns false if the difference in intensity of
         * any of the 3 color channels is greater than or
         * equal to 2.
         *
         * Returns true for the following pair:
         * @code
         * this: {          other: {
         *   red: 100,        red: 101,
         *   green: 100,      green: 100,
         *   blue: 100        blue: 99
         * }                }
         * @endcode
         * Returns false for the following pair:
         * @code
         * this: {          other: {
         *   red: 100,        red: 100,
         *   green: 100,      green: 102,
         *   blue: 100        blue: 100
         * }                }
         * @endcode
         * */
        bool almostEquals(const RGBColor &other) const {
            return abs((int)this->red - (int)other.red) < 2 &&
                   abs((int)this->blue - (int)other.blue) < 2 &&
                   abs((int)this->green - (int)other.green) < 2;
        }

    };

    inline std::string to_string(const RGBColor &it) {
        return "rgb(" +
                std::to_string((int)it.red) + "," +
                std::to_string((int)it.green) + "," +
                std::to_string((int)it.blue) + ")";
    }

    inline std::ostream& operator <<(std::ostream& os, const RGBColor &it) {
        os << to_string(it);
        return os;
    }

}

#endif //SLAM_RGBCOLOR_H
