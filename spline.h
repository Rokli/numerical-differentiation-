#ifndef SPLIEN_H
#define SPLIEN_H
#include <iostream>
#include <vector>
#include <Models/PassingIteration.h>
using namespace std;
class Spline
{
private:
    vector<float> x, y, a, b, c, d;
    vector<vector<float>> m;
public:
    void CreateSpline(vector<float> x, vector<float> y)
    {
        this->x = x;
        this->y = y;
        a = y;
        int n = (int)x.size();
        vector<float> h;
        h.resize(n - 1 );
        for(int i = 0; i < n -1; i++){
            h[i] = x[i+1] - x[i];
        }
        vector<float> alpha;
        alpha.resize(n);
        for(int i = 1; i < n - 1; i++){
            alpha[i] = (3 / h[i]) * (a[i + 1] - a[i]) - (3 / h[i - 1]) * (a[i] - a[i - 1]);
        }
        vector<float> l;
        l.resize(n);
        vector<float> mu;
        mu.resize(n);
        vector<float> z;
        z.resize(n);
        l[0] = 1;
        mu[0] = 0;
        z[0] = 0;
        for(int i = 1; i < n - 1; i++ ){
            l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
            mu[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
        }
        l[n - 1] = 1;
        z[n - 1] = 0;

        c.resize(n);
        b.resize(n);
        d.resize(n);
        GetM(alpha,h);
        for(int j = n - 2; j >= 0; j--){
            c[j] = (float)(z[j] - mu[j] * c[j + 1]);
            b[j] = (float)(((a[j + 1] - a[j]) / h[j]) - (h[j] * (c[j + 1] + 2 * c[j]) / 3));
            d[j] = (float)((c[j + 1] - c[j]) / (3 * h[j]));
        }
    }
    void GetM(vector<float> alpha, vector<float> h){
        vector<vector<float>> matrix(c.size());
        for(int i = 0; i < (int)c.size();i++){
            matrix[i].resize(c.size());
        }
        vector<float> freeNumbers;
        freeNumbers.resize(c.size());
        int rowIndex = 1;
        matrix[0][0] = 1;

        for(int i = 1; i < (int)c.size(); i++){
            matrix[rowIndex][ i -1] = h[i -1];
            matrix[rowIndex][i] = 2 * (h[i-1] + h[i]);
            if(i+1 != (int)c.size() - 1)
                matrix[rowIndex][i+1] = h[i];
            freeNumbers[rowIndex] = alpha[rowIndex];
            rowIndex++;
        }
        PassingMethod passingMethod;
        m = passingMethod.Start(matrix,freeNumbers);
    }
    vector<vector<float>> GetMatrix(){
        return m;
    }
    double Interpolat(double xi)
    {
        int j = 0;
        while (j < (int)x.size() - 1 && xi > x[j + 1])
        {
            j++;
        }
        double dx = xi - x[j];

        return a[j] + b[j] * dx + c[j] * dx * dx + d[j] * dx * dx * dx;
    }
};

#endif // SPLIEN_H
