//
// Created by Kyler Jensen on 3/28/17.
//

#ifndef SLAM_COLORSPACE_H
#define SLAM_COLORSPACE_H

#include <ostream>

namespace slam {

    enum ColorSpace : int {
        GRAYSCALE = 1,
        RGB = 3
    };

    inline std::string to_string(const slam::ColorSpace &it) {
        switch(it) {
            case GRAYSCALE:
                return "GRAYSCALE(" + std::to_string((int)it) + ")";
            case RGB:
                return "RGB(" + std::to_string((int)it) + ")";
            default:
                return "UNSUPPORTED(" + std::to_string((int)it) + ")";
        }
    }

    inline std::ostream& operator <<(std::ostream& os, const slam::ColorSpace &it) {
        os << to_string(it);
        return os;
    }

}

#endif //SLAM_COLORSPACE_H
