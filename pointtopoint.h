#ifndef POINTTOPOINT_H
#define POINTTOPOINT_H

#include <cmath>
using namespace std;
class PointToPoint {
public:
    static float CalculationFormula(float x, float delta){
        return ((Function(x + delta)- Function(x))/delta);
    }
    static  float Function(float x){
        return 4 * pow(x,2);
    }
};

#endif // POINTTOPOINT_H
