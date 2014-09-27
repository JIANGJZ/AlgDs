#ifndef __AlgDs__Queue__
#define __AlgDs__Queue__

#include "Vector.h"

template <typename T>
class VQueue : protected Vector<T> {
public:
    void enqueue(T const& e) {
        Vector<T>::insert(size(), e);
    }
    
    T dequeue() {
        assert(size() != 0);
        return Vector<T>::remove(0);
    }
    
    T& front() {
        assert(size() != 0);
        return (*this)[size()-1];
    }
    
    bool empty() {
        return Vector<T>::empty();
    }
    
    int size() {
        return Vector<T>::size();
    }
    
    void traverse(void (*visit)(T &)) {
        Vector<T>::traverse(visit);
    }
    
};

#endif 
