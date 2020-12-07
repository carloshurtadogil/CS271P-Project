#include "../Common/Node.h"
#include <iostream>
#include <vector>

// g++ SLS/main.cpp Common/Node.cpp 

using namespace std;

int n;
typedef vector<float> VEC;
vector<VEC> e;

float evaluation(const VEC &x) {
    float  ret = 0;
    for(int i = 1; i < n; i++)
        ret += e[x[i-1]][x[i]];
    ret += e[x[n-1]][x[0]];
    return ret;
}

VEC SA(const vector<VEC> &e, float  alpha) {
    float T = 100;

}

int main(int argc, char **argv) {
    FILE* file = fopen(argv[1], "r");
    fscanf(file, "%d", &n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            float x;
            fscanf(file, "%f", &x);
            e[i].push_back(x);
        }
    VEC ans = SA(e, 0.9);
}
