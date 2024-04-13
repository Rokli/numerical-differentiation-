#ifndef SORTING_H
#define SORTING_H
#include <vector>
using namespace std;
class Sorting{
public:
    static float VectorMaxToFloat(vector<float> tmp){
        float max = 0;
        for(float n : tmp){
            if(max < n)
                max = n;
        }

        return max;
    }
    static float VectorMinToFloat(vector<float> tmp){
        float min = 999;
        for(int i = 0; i < (int) tmp.size(); i++){
            if(min > tmp[i]){
                min = tmp[i];
            }
        }
        return min;
    }
};

#endif // SORTING_H
