#include "../include/structDepthMap.hpp"

slam::StructDepthMap:: StructDepthMap(unsigned short x, unsigned short y)
{
    for(int i = 0; i < x; i++)
    {
        std::vector <float> temp;
        for(int k = 0; k < y; k++)
        {
            temp.push_back(UNKNOWN_DEPTH);
        }
        m_depth.push_back(temp);
    }
}

void slam::StructDepthMap:: setDepth(unsigned short x, unsigned short y, float depth)
{
    m_depth[x][y] = depth;
}

double slam::StructDepthMap:: getDepth(unsigned short x, unsigned short y)
{
   return m_depth[x][y];
}