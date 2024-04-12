#ifndef POINTTOPOINT_H
#define POINTTOPOINT_H

#include <cmath>
using namespace std;
class PointToPoint {
public:
    static float CalculationFormulaRigth(float x, float delta){
        return ((FirstDerivative(x + delta)- FirstDerivative(x))/delta);
    }
    static float CalculationFormulaBoth(float x, float delta){
        return ((FirstDerivative(x + delta)- FirstDerivative(x - delta))/(2 * delta));
    }
    static  float FirstDerivative(float x){
        return 4 * pow(x,2);
    }
    static  float TwoDerivative(float x){
        return 8;
    }
};

#endif // POINTTOPOINT_H
