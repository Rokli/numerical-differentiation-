#ifndef WORKINGWITHDERIVATIVES_H
#define WORKINGWITHDERIVATIVES_H
#include <math.h>
class WorkingWithDerivatives{
public:
    static float FirstDerivatives(float prevY, float nextY, float step){
        return (nextY - prevY) / (2 * step);
    }
    static float SecondDerivatives(float prevTwoY,float nextTwoY, float y, float step){
        return (nextTwoY-2*y+prevTwoY) / (4 * pow(step, 2));
    }
};

#endif // WORKINGWITHDERIVATIVES_H
