#ifndef structDepthMap_hpp
#define structDepthMap_hpp
#define UNKNOWN_DEPTH -1.0

#include <stdio.h>
#include <vector>
#include <iostream>

namespace slam {
class StructDepthMap{
public:
    StructDepthMap(unsigned short x, unsigned short y);
    void setDepth(unsigned short x, unsigned short y, float depth);
    double getDepth(unsigned short x, unsigned short y);
    std::vector< std::vector <float> > m_depth; //vector of vector of floats

private:
    
};
}
#endif /* structDepthMap_hpp */