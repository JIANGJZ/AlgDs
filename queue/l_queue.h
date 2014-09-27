#ifndef AlgDs_l_queue_h
#define AlgDs_l_queue_h

#include "list.h"

#include <cassert>

template <typename T>
class LQueue : protected List<T>{
public:
    void enqueue(T const &e) {
        List<T>::insert_as_last(e);
    }
    
    T dequeue() {
        assert(empty() != true);
        return List<T>::remove(List<T>::first());
    }
    
    T& front() {
        assert(empty() != true);
        return List<T>::first()->m_data;
    }
    
    bool empty() {
        return List<T>::empty();
    }
    
    int size() {
        return List<T>::size();
    }
    
    void traverse(void (*visit)(T &)) {
        List<T>::traverse(visit);
    }
};

#endif
