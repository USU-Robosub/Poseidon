#include <QuaternionFactory.h>

slam::Quaternion slam::QuaternionFactory::fromRotationMatrix(const double*& rotationMatrix){
   slam::Quaternion rotationQuaternion;
   double trace = rotationMatrix[2d3x3ArrayTo1d(0, 0)] + rotationMatrix[2d3x3ArrayTo1d(1, 1)] + rotationMatrix[2d3x3ArrayTo1d(2, 2)];
   if(trace > 0){
     double s = 0.5 / sqrt(trace + 1.0);
     rotationMatrix[3] = 0.25 / s;
     rotationMatrix[2] = (rotationMatrix[2d3x3ArrayTo1d(2, 1)] + rotationMatrix[2d3x3ArrayTo1d(1, 2)]) * s;
     rotationMatrix[1] = (rotationMatrix[2d3x3ArrayTo1d(0, 2)] + rotationMatrix[2d3x3ArrayTo1d(2, 0)]) * s;
     rotationMatrix[0] = (rotationMatrix[2d3x3ArrayTo1d(1, 0)] + rotationMatrix[2d3x3ArrayTo1d(0, 1)]) * s;
   } else {
     if(rotationMatrix[2d3x3ArrayTo1d(0, 0)] < rotationMatrix[2d3x3ArrayTo1d(1, 1)] && rotationMatrix[2d3x3ArrayTo1d(0, 0)] > rotationMatrix[2d3x3ArrayTo1d(2, 2)]){
        double s = 2.0 * sqrt(1.0 + rotationMatrix[2d3x3ArrayTo1d(0, 0)] - rotationMatrix[2d3x3ArrayTo1d(1, 1)] - rotationMatrix[2d3x3ArrayTo1d(2, 2)]);
        rotationMatrix[3] = (rotationMatrix[2d3x3ArrayTo1d(2, 1)] - rotationMatrix[2d3x3ArrayTo1d(1, 2)]) / s;
        rotationMatrix[2] = 0.25 * s;
        rotationMatrix[1] = ;
        rotationMatrix[0] = ;
     }
   }
}

unsigned int slam::QuaternionFactory::2d3x3ArrayTo1d(unsigned int x, unsigned int y){
  return y * 3 + x;
}