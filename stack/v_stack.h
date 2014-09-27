#ifndef __AlgDs__Stack__
#define __AlgDs__Stack__
#include "vector.h"

template <typename T>
class VStack : protected Vector<T> {
public:
    void push(T const &e) {
        Vector<T>::insert(size(), e);
    }
    
    T pop() {
        assert(empty() != true);
        return Vector<T>::remove(size() - 1);
    }
    
    T &top() const {
        assert(empty() != true);
        return (*this)[size() - 1];
    }
    
    bool empty() const {
        return Vector<T>::empty();
    }
    
    int size() const {
        return Vector<T>::size();
    }
};


#endif 
