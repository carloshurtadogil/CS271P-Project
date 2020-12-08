#include "../Common/Node.h"
#include <iostream>
#include <vector>
#include <cmath>

// g++ SLS/main.cpp Common/Node.cpp 

using namespace std;

int n;
typedef vector<int> VEC;
vector<vector<float>> e;

double dshrandom( long input ) {
    static long seed = 3125;
    static long a = 16807;
    static long m = 2147483647;
    static long q = 127773;      /* m div a */
    static long r = 2836;        /* m mod a */
    long lo, hi, test;

    if (input>0) seed = input;
    hi = seed/q;
    lo = seed - (hi*q);
    test = a*lo - r*hi;
    if (test>0) seed = test;
    else        seed = test+m;
    /* seed equally in range 0...2^31 -1  */
    return( ((double)seed)/(double)m );
}

float evaluation(const VEC &x) {
    float  ret = 0;
    for(int i = 1; i < n; i++)
        ret += e[x[i-1]][x[i]];
    ret += e[x[n-1]][x[0]];
    return ret;
}

int rand_idx() {
    double random = dshrandom(0);
    int x = floor(random * n);
    return x == n ? n-1 : x;
}
bool check(const VEC &x) {
    VEC arr(n);
    for(int i = 0; i < n; i++)
        if(arr[x[i]])
            return false;
        else
            arr[x[i]]++;
    return true;
}

void Move(const vector<vector<float>> &e, VEC &cur) {
    double possibility = dshrandom(0);
    if(possibility < 0.4) {
        int i = rand_idx(), j = rand_idx();
        while(i == j)
            j = rand_idx();
        swap(cur[i], cur[j]);
    }
    else if(possibility < 0.8) {
        int i = rand_idx(), j = rand_idx();
        while(i == j)
            j = rand_idx();
        int x = cur[i];
        if(i < j) {
            for (int k = i; k < j; k++)
                cur[k] = cur[k + 1];
            cur[j] = x;
        }
        else {
            for(int k = i; k > j; k--)
                cur[k] = cur[k-1];
            cur[j+1] = x;
        }
    }
    else if(possibility < 0.9) {
        int i = rand_idx(), j = rand_idx(), k = rand_idx();
        while(i == j)
            j = rand_idx();
        while(i == k || j == k)
            k = rand_idx();
        if(i > j) swap(i, j);
        if(i > k) swap(i, k);
        if(j > k) swap(j, k);

        double direction = dshrandom(0);
        if(direction < 0.5) {
            int items = k-j+1;
            VEC temp(items);
            for(int p = j; p <= k; p++)
                temp[p-j] = cur[p];
            for(int p = k; p > i; p--)
                cur[p] = cur[p-items];
            for(int p = i+1; p < i+1+items; p++)
                cur[p] = temp[p-(i+1)];
        }
        else {
            int items = j-i+1;
            VEC temp(items);
            for(int p = i; p <= j; p++)
                temp[p-i] = cur[p];
            for(int p = i; p < k; p++)
                cur[p] = cur[p+items];
            for(int p = 0; p < items; p++)
                cur[k-p] = temp[items-p-1];
        }
    }
    else {
        int i = rand_idx(), j = rand_idx();
        while(i == j)
            j = rand_idx();
        reverse(&cur[i], &cur[j]);
    }
    if(!check(cur))
        cout << possibility << endl;
}

VEC SA(const vector<vector<float>> &e, float  alpha) {
    float T = 100, eps = 1e-3;
    VEC current(n), ans(n);
    float MIN, cur_val;
    for(int i = 0; i < n; i++)
        current[i] = i;
    random_shuffle(current.begin(), current.end());
    ans = current;
    cur_val = MIN = evaluation(current);
    while(T > eps) {
        T *= alpha;
        VEC next(current);
        Move(e, next);
        float val = evaluation(next);
        if(val < MIN) {
            MIN = val;
            ans = next;
        }
        float delta = val - cur_val;
        if(delta < 0 || (delta > 0 && dshrandom(0) < exp(delta/T))) {
            cur_val = val;
            current = next;
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    dshrandom(time(0));
    FILE* file = fopen(argv[1], "r+");
    if(file == NULL) {
        printf("%s\n",argv[1]);
        printf("Error file name\n");
        return 0;
    }
    fscanf(file, "%d", &n);
    for(int i = 0; i < n; i++) {
        e.push_back(vector<float>(n));
        for (int j = 0; j < n; j++) {
            float x;
            fscanf(file, "%f", &x);
            e[i][j] = x;
        }
    }
    VEC ans = SA(e, 0.9);
    cout << evaluation(ans) << endl;
    return 0;
}
