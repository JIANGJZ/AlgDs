#ifndef AlgDs_sort_h
#define AlgDs_sort_h

#include <cstdlib>

#include "bubbleSort.h"

template <typename T>
void sort(T* elememt, int lo, int hi) {
    switch (rand() % 5) {
        case 1:
            bubbleSort1(elememt, lo, hi);
            break;
        case 2:
            bubbleSort2(elememt, lo, hi);
            break;
        case 3:
            mergeSort1(elememt, lo, hi);
            break;
        case 4:
            mergeSort2(elememt, lo, hi);
            break;
        default:
            break;
    }
}

#endif
