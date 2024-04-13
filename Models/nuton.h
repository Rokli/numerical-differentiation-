#ifndef NUTON_H
#define NUTON_H
#include<vector>
using namespace std;
class Nuton
{
public:
    vector<float> divDiff,yV,xV;
    float DividedDifferences(vector<float> x,vector<float> y, int k){
        float result = 0;
        yV = y;
        xV = x;
        for(int j = 0; j < k+1;j++){
            float mul = 1;
            for(int i = 0; i < k+1;i++){
                if(i != j){
                    mul *= x[j] - x[i];
                }
            }
            result += y[j]/mul;
        }
        return result;
    }
    void NewtonPolinominal(vector<float> x, vector<float> y){
        for(int i = 0; i < (int)x.size();i++){
            divDiff.push_back(DividedDifferences(x,y,i));
        }
    }
    float polynominal(float x){
        float result = yV[0];
        for(int k = 0; k < (int)xV.size();k++){
            float mul = 1;
            for(int j = 0; j < k; j++){
                mul *= x - xV[j];
            }
            result += divDiff[k] * mul;
        }
        return result;
    }

};

#endif // NUTON_H
