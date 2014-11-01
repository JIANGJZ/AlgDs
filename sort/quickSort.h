#ifndef AlgDs_quickSort_h
#define AlgDs_quickSort_h

#include "../vector/vector.h"

#include <utility>
//左闭右开
template <typename T>
int partition1(int lo, int hi, Vector<T>& vec) {
    swap(vec[lo], vec[lo + rand()%(hi-lo+1)]);
    T pivot = vec[lo];
    while (lo < hi) {
        while ((lo < hi) && (pivot <= vec[hi])) {
            hi--;
        }
        vec[lo] = vec[hi];
        while (lo < hi && vec[lo] <= pivot) {
            lo++;
        }
        vec[hi] = vec[lo];
    }
    
    vec[lo] = pivot;
    
    return lo;
}

template <typename T>
int partition1_1(int lo, int hi, Vector<T>& vec) {
    swap(vec[lo], vec[lo + rand()%(hi-lo+1)]);
    T pivot = vec[lo];
    while (lo < hi) {
        while ((lo < hi) && pivot < vec[hi]) {
            hi--;
        }
        if (lo < hi) {
            vec[lo] = vec[hi];
            lo++;
        }
        while (lo < hi && vec[lo] < pivot) {
            lo++;
        }
        
        if (lo < hi) {
            vec[hi] = vec[lo];
            hi--;
        }
    }
}

template <typename T>
void quickSort1(int lo, int hi, Vector<T>& vec) {
    if (hi - lo <= 1) {
        return;
    }
    int mid = partition1<int>(lo, hi-1, vec);
    quickSort1(lo, mid, vec);
    quickSort1(mid+1, hi-1, vec);
}


//左右都是闭区间
template <typename T>
int partition2(int lo, int hi, Vector<T>& vec) {
    swap(vec[lo], vec[lo + rand()%(hi-lo+1)]);
    int index = lo;
    int pivot = vec[index];
    swap(vec[index], vec[hi]);
    for (int i = lo; i < hi; i++) {
        if (vec[i] > pivot) {
            swap(vec[index++], vec[i]);
        }
    }
    swap(vec[hi], vec[index]);
    return index;
}

template <typename T>
void quickSort2(int lo, int hi, Vector<T>& vec) {
    if (hi <= lo) {
        return;
    }
    
    int mid = partition2<int>(lo, hi, vec);
    quickSort2(lo, mid-1, vec);
    quickSort2(mid+1, hi, vec);
}

#endif
