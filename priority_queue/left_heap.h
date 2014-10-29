#ifndef AlgDs_left_heap_h
#define AlgDs_left_heap_h

#include "priority_queue.h"
#include "../tree/binary_tree.h"

#include <algorithm>
using namespace std;

template <typename T>
static BinNode<T>* merge(BinNode<T>* a, BinNode<T>* b) {
    if(!a) {
        return a;
    }
    
    if(!b) {
        return b;
    }
    
    if (a->m_data < b->m_data) {
        swap(a, b);
    }
    
    a->m_rchild = merge(a->m_rchild, b);
    a->m_rchild->m_parent = a;
    
    if (!a->m_lchild || a->m_lchild->m_npl < a->m_rchild->m_npl) {
        swap(a->m_lchild, a->m_rchild);
    }
    a->m_npl = (a->m_rchild ? a->m_rchild->m_npl + 1 : 1);
    
    return a;
}


template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T> {
public:
    PQ_LeftHeap() {};
    
    PQ_LeftHeap(T* E, int n) {
        for (int i = 0; i < n; i++) {
            insert(E[i]);
        }
    }
    
    void insert(T e);
    
    T getMax();
    T delMax();
};

template <typename T>
void PQ_LeftHeap<T>::insert(T e) {
    BinNode<T> *new_node = new BinNode<T>(e);
    BinTree<T>::m_root = merge(BinTree<T>::m_root, new_node);
    BinTree<T>::m_root->m_parent = nullptr;
    
    BinTree<T>::m_size++;
}


template <typename T>
T PQ_LeftHeap<T>::delMax() {
    BinNode<T>* lHeap = BinTree<T>::getRoot()->m_lchild;
    BinNode<T>* rHeap = BinTree<T>::getRoot()->m_rchild;
    
    T e = BinTree<T>::m_root->m_data;
    delete BinTree<T>::m_root;
    BinTree<T>::m_size--;
    
    BinTree<T>::m_root = nullptr;
    
    BinTree<T>::m_root = merge(lHeap, rHeap);
    
    return e;
}


template <typename T>
T PQ_LeftHeap<T>::getMax() {
    return BinTree<T>::m_root->m_data;
}

#endif
