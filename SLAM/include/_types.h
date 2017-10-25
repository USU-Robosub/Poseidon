//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_EXTRAS_H
#define SLAM_EXTRAS_H

#include <chrono>
#include <thread>
#include <string>
#include <iostream>

namespace slam {

    /**
     * An alias for std::chrono::steady_clock::time_point
     * */
    typedef std::chrono::steady_clock::time_point chrono;

    /**
     * A one-byte unsigned integer
     * Range: 0 to 255
     * */
    typedef uint8_t uchar;

    /**
     * A two-byte unsigned integer
     * Range: 0 to 65,535
     * */
    typedef uint16_t ushort;

    /**
     * A four-byte unsigned integer
     * Range: 0 to 4,294,967,295
     * */
    typedef uint32_t uint;

    /**
     * An eight-byte unsigned integer
     * Range: 0 to 18,446,744,073,709,551,615
     * */
    typedef uint64_t ulong;

    inline std::ostream& operator <<(std::ostream& os, const uchar it) {
        os << (int)it;
        return os;
    }

    class Output3DWrapper {}; //TODO: remove this and replace usages with the real dso::Output3DWrapper

}

#endif //SLAM_EXTRAS_H
