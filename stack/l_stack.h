#ifndef AlgDs_l_stack_h
#define AlgDs_l_stack_h

#include "list.h"

template <typename T>
class LStack : protected List<T> {
public:
    void push(T const &e) {
        List<T>::insert_as_last(e);
    }
    
    T pop() {
        assert(empty() != true);
        return List<T>::remove(List<T>::last());
    }
    
    T& top() const {
        assert(empty() != true);
        return List<T>::last()->m_data;
    }
    
    bool empty() const {
        return List<T>::empty();
    }
    
    int size() const {
        return List<T>::size();
    }
    
};

#endif
