#ifndef AlgDs_maxR_h
#define AlgDs_maxR_h

#include <climits>
#include <algorithm>

int maxR_i(int A[], int n);

int maxR_i(int A[], int n) {
    int m = INT_MIN;
    for (int i = 0; i < n; i++) {
        m = std::max(m, A[i]);
    }
    return m;
}

int maxR_r(int A[], int n);

int maxR_r(int A[], int n) {
    if (n == 2) {
        return std::max(A[n], A[n - 1]);
    } else {
        return std::max(maxR_r(A, n - 1), A[n - 1]);
    }
}

int maxR_d(int A[], int lo, int hi);
//区间左闭右开
int maxR_d(int A[], int lo, int hi) {
    if (hi - lo <= 1) {
        return A[lo];
    } else {
        int mid = lo + (hi - lo) / 2;
        return std::max(maxR_d(A, lo, mid), maxR_d(A, mid, hi));
    }
}



#endif
