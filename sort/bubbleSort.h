#ifndef AlgDs_bubbleSort_h
#define AlgDs_bubbleSort_h

#include <algorithm>

template <typename T>
bool bubble1(T* element, int lo, int hi) {
    bool sorted = true;
    while (++lo < hi) {
        if (element[lo - 1] > element[lo]) {
            sorted = false;
            std::swap(element[lo - 1], element[lo]);
        }
    }
    return sorted;
}

template<typename T>
void bubbleSort1(T* elememt, int lo, int hi) {
    while (!bubble1(elememt, lo, hi--));
}

template <typename T>
int bubble2(T* element, int lo, int hi) {
    int last_swap = lo;
    while (++lo < hi) {
        if (element[lo - 1] > element[lo]) {
            last_swap = lo;
            std::swap(element[lo - 1], element[lo]);
        }
    }
    return last_swap;
}

template<typename T>
void bubbleSort2(T* elememt, int lo, int hi) {
    while (lo < (hi = bubble2(elememt, lo, hi)));
}


#endif
