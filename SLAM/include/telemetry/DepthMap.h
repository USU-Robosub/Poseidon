#ifndef SLAM_DEPTHMAP_H
#define SLAM_DEPTHMAP_H
#define UNKNOWN_DEPTH -1.0f

#include <stdio.h>
#include <vector>
#include <iostream>

namespace slam {
    
    class DepthMap{

    private:
        std::vector<std::vector<float>> m_depth; //vector of vector of floats
        
    public:
        DepthMap(ushort x, ushort y);
        void setDepth(ushort x, ushort y, float depth);
        double getDepth(ushort x, ushort y);


    };
    
}
#endif //SLAM_DEPTHMAP_H
