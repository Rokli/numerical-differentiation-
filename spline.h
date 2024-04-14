#ifndef SPLIEN_H
#define SPLIEN_H
#include <iostream>
#include <vector>
using namespace std;
class Spline
{
private:
    vector<float> x, y, a, b, c, d;

public:
    void CreateSpline(vector<float> x, vector<float> y)
    {
        this->x = x;
        this->y = y;
        a = y;
        int n = (int)x.size();
        vector<double> h;
        h.resize(n - 1 );
        for(int i = 0; i < n -1; i++){
            h[i] = x[i+1] - x[i];
        }
        vector<double> alpha;
        alpha.resize(n);
        for(int i = 1; i < n - 1; i++){
            alpha[i] = (3 / h[i]) * (a[i + 1] - a[i]) - (3 / h[i - 1]) * (a[i] - a[i - 1]);
        }
        vector<double> l;
        l.resize(n);
        vector<double> mu;
        mu.resize(n);
        vector<double> z;
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
        for(int j = n - 2; j >= 0; j--){
            c[j] = (float)(z[j] - mu[j] * c[j + 1]);
            b[j] = (float)(((a[j + 1] - a[j]) / h[j]) - (h[j] * (c[j + 1] + 2 * c[j]) / 3));
            d[j] = (float)((c[j + 1] - c[j]) / (3 * h[j]));
        }
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
