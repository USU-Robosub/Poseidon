#pragma once

#include<_tmp.h>

namespace slam{
  
  class QuaternionFactory{
  public:
    static Quaternion fromRotationMatrix(const double*& rotationMatrix);
  private:
    unsigned int 2d3x3ArrayTo1d(unsigned int x, unsigned int y);
  };
  
}