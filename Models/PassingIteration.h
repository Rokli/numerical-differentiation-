#ifndef PASSINGITERATION_H
#define PASSINGITERATION_H
#include <vector>
using namespace std;
class PassingMethod {
public:
    static vector<float> Start(vector<vector<float>> matrix, vector<float> freeValues){
        for(int i = 1; i < (int)matrix.size(); i++){
            matrix[i][i] -= matrix[i][i-1] * matrix[i-1][i] / (matrix[i-1][i-1]);
            freeValues[i] -= matrix[i][i-1] * freeValues[i-1] / matrix[i-1][i-1];
            matrix[i][i-1] = 0;
        }
        return ReverseStroke(matrix,freeValues);
    }
    static vector<float> ReverseStroke(vector<vector<float>> matrix, vector<float> freeValues){
        double sum = 0;
        for(int i = (int)matrix.size();i >=0 ; i--){
            for(int j = matrix.size()-1;j > i; j--){
                sum += matrix[i][j] * freeValues[j];
            }
            freeValues[i] = i / matrix[i][i] * (freeValues[i] - sum);
            sum = 0;
        }
        return freeValues;
    }
};
#endif // PASSINGITERATION_H
