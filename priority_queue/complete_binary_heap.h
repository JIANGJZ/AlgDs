#ifndef AlgDs_complete_binary_heap_h
#define AlgDs_complete_binary_heap_h

#include "vector.h"
#include "priority_queue.h"

#define Inheap(n, i) (((-1) < (i))&&((i) < (n)))

#define Parent(i) ((i - 1) >> 1)

#define LChild(i) (1 + ((i) << 1))

#define RChild(i) ((1 + (i)) << 1)

#define ParentValid(i) (0 < i)

#define LChildValid(n, i) Inheap(n, LChild(i))

#define RChildValid(n, i) Inheap(n, RChild(i))

#define Biggger(PQ, i, j) (PQ[i] > PQ[j] ? i : j)

#define LastInternal(n) Parent(n - 1)

#define ProperParent(PQ, n, i) \
        (RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
        (LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
        ) \
        )

template <typename T>
class PQ_Complheap : public PQ<T>, public Vector<T> {
protected:
    int down(int n, int i);
    
    int up(int i);
    
    void heapify(int n);
public:
    PQ_Complheap(T* array, int n) {
        Vector<T>::_copy_from(array, 0, n);
        heapify(n);
    }
    
    PQ_Complheap() {}
    
    ~PQ_Complheap() {}
    
    void insert(T val);
    
    T getMax() {
        return Vector<T>::m_element[0];
    }
    
    T delMax();
};

template <typename T>
int PQ_Complheap<T>::down(int n, int i) {
    int j;
    while (i != (j = ProperParent(Vector<T>::m_element, n, i))) {
        swap(Vector<T>::m_element[i], Vector<T>::m_element[j]);
        i = j;
    }
    return i;
}

template <typename T>
int PQ_Complheap<T>::up(int i) {
    while (ParentValid(i)) {
        int j = Parent(i);
        if (less(Vector<T>::m_element[i], Vector<T>::m_element[j])) {
            break;
        }
        swap(Vector<T>::m_element[i], Vector<T>::m_element[j]);
        i = j;
    }
    return i;
}

template <typename T>
void PQ_Complheap<T>::heapify(int n) {
    for (int i = LastInternal(n); Inheap(n, i); i--) {
        down(n, i);
    }
}

template <typename T>
void PQ_Complheap<T>::insert(T val) {
    Vector<T>::insert(val);
    up(Vector<T>::size() - 1);
}

template <typename T>
T PQ_Complheap<T>::delMax() {
    T maxElem = Vector<T>::m_element[0];
    swap(Vector<T>::m_element[0], Vector<T>::m_element[Vector<T>::size()-1]);
    Vector<T>::remove(Vector<T>::size()-1);
    down(Vector<T>::size(), 0);
    return maxElem;
}


#endif
