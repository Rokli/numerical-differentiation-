#ifndef WORKINGWITHDERIVATIVES_H
#define WORKINGWITHDERIVATIVES_H
#include <math.h>
class WorkingWithDerivatives{
public:
    float FirstDerivatives(float prevY, float y, float step){
        return (y - prevY) / (2 * step);
    }
    float SecondDerivatives(float prevTwoY,float nextTwoY, float y, float step){
        return (nextTwoY-2*y+prevTwoY) / (4 * pow(step, 2));
    }
};

#endif // WORKINGWITHDERIVATIVES_H
