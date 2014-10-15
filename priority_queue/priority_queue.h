#ifndef AlgDs_priority_queue_h
#define AlgDs_priority_queue_h

template <typename T>
class PQ {
    virtual void insert(T) = 0;
    
    virtual T getMax() = 0;
    
    virtual T delMax() = 0;
};


#endif
