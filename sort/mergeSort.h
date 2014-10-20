#ifndef AlgDs_mergeSort_h
#define AlgDs_mergeSort_h

template <typename T>
void merge1(T* element, int lo, int mid, int hi) {
    T* A = element + lo;
    int lb = mid - lo;
    T* B = new T[lb];
    for (int i = 0; i < lb; i++) {
        B[i] = A[i];
    }
    int lc = hi - mid;
    T* C = element + mid;
    for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
        if ((j < lb) && (lc <= k || (B[j] <= C[k]))) {
            A[i++] = B[j++];
        }
        
        if ((k < lc) && (lb <= j || (C[k] < B[j]))) {
            A[i++] = C[k++];
        }
    }
    delete []B;
}

template <typename T>
void mergeSort1(T* element, int lo, int hi) {
    if (hi - lo < 2) {
        return;
    }
    int mid = lo + (hi - lo)/2;
    mergeSort1(element, lo, mid);
    mergeSort1(element, mid, hi);
    merge1(element, lo, mid, hi);
}

template <typename T>
void merge2(T* element, int lo, int mid, int hi) {
    T* A = element + lo;
    int lb = mid - lo;
    T* B = new T[lb];
    for (int i = 0; i < lb; i++) {
        B[i] = A[i];
    }
    int lc = hi - mid;
    T* C = element + mid;
    for (int i = 0, j = 0, k = 0; j < lb; ) {
        if (lc <= k || B[j] <= C[k]) {
            A[i++] = B[j++];
        }
        
        if ((k < lc) && (C[k] < B[j])) {
            A[i++] = C[k++];
        }
    }
    
    delete []B;
}

template <typename T>
void mergeSort2(T* element, int lo, int hi) {
    if (hi - lo < 2) {
        return;
    }
    int mid = lo + (hi - lo)/2;
    mergeSort2(element, lo, mid);
    mergeSort2(element, mid, hi);
    merge2(element, lo, mid, hi);
}


#endif
