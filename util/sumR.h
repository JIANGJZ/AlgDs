#ifndef AlgDs_sumR_h
#define AlgDs_sumR_h

int sumR_i(int arr[], int n);

int sumR_i(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int sumR_r(int arr[], int n);

int sumR_r(int arr[], int n) {
    if (n == 0) {
        return 0;
    } else {
        return sumR_r(arr, n - 1) + arr[n - 1];
    }
    
}

int sumR_d(int arr[], int lo, int hi);

int sumR_d(int arr[], int lo, int hi) {
    if (hi - lo <= 1) {
        return arr[lo];
    } else {
        int mid = lo + (hi - lo) / 2;
        return sumR_d(arr, lo, mid) + sumR_d(arr, mid, hi);
    }
}


#endif
