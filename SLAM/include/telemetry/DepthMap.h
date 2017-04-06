#ifndef SLAM_DEPTHMAP_H
#define SLAM_DEPTHMAP_H
#define UNKNOWN_DEPTH -1.0

#include <stdio.h>
#include <vector>
#include <iostream>

namespace slam {
    
    class DepthMap{
        
    public:
        DepthMap(unsigned short x, unsigned short y);
        void setDepth(unsigned short x, unsigned short y, float depth);
        double getDepth(unsigned short x, unsigned short y);
        std::vector< std::vector <float> > m_depth; //vector of vector of floats

    };
    
}
#endif /* SLAM_DEPTHMAP_H */
