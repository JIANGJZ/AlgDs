#ifndef __AlgDs__vector__
#define __AlgDs__vector__

#include "vector.h"
#include "fibonacci.h"

#include <cassert>
#include <algorithm>

const int g_default_capacity = 3;
typedef int Rank;

template <typename T>
class Vector {
public:
    
    Vector(int c = g_default_capacity, int s = 0, int v = 0) : m_capacity(c), m_size(s){
        m_element = new T[m_capacity];
        for (m_size = 0; m_size < s; m_size++) {
            m_element[m_size] = v;
        }
    }
    
    Vector(T const * A, Rank lo, Rank hi) {
        _copy_from(A, lo, hi);
    }
    
    Vector(Vector<T> const& V, Rank lo, Rank hi) {
        _copy_from(V.m_element, lo, hi);
    }
    
    Vector(Vector<T> const& V) {
        _copy_from(V.m_element, 0, V.m_size);
    }
    
    ~Vector() {
        delete []m_element;
    }
    
    Rank size() const {
        return m_size;
    }
    
    bool empty() const {
        return (m_size == 0);
    }
    
    /// \brief operator []替代了get, put的功能
    T & operator [](Rank r) const;
    
    Rank insert(Rank r, T e);
    
    T remove(Rank r);
    
    int remove(Rank lo, Rank hi);
    
    void unsort(Rank lo, Rank hi);
    
    void unsort();
    
    void sort(Rank lo, Rank hi);
    
    void sort();
    
    Rank find(T const &e, Rank lo, Rank hi) const;
    
    Rank find(T const &e) const;
    
    /// \breif 如何保证语义一致性，返回不大于e的最后一个元素
    ///        查找到但是有多个返回最大秩,查找不到的情况
    Rank search(T const &e, Rank lo, Rank hi) const;
    
    Rank search(T const& e) const;
    
    int deduplicate();
    
    int disordered();
    
    int uniquify();
    
    void traverse(void (*visit)(T &));
    
    template<typename VST> void traverse(VST &visit);
    
protected:
    /// \brief 复制区间为[lo, hi)
    void _copy_from(T const * A, Rank lo, Rank hi);
    
    void _expand();
    
    void _shrink();
    
    Rank _bi_search(T const &e, Rank lo, Rank hi) const;
    
    Rank _fib_search(T const &e, Rank lo, Rank hi) const;
    
private:
    Rank m_size;
    int m_capacity;
    T *m_element;
};


template <typename T>
void Vector<T>::_copy_from(T const * A, Rank lo, Rank hi) {
    m_capacity = (hi - lo) * 2;
    m_size = 0;
    m_element = new T[m_capacity];
    while (lo < hi) {
        m_element[m_size++] = A[lo++];
    }
}

template <typename T>
void Vector<T>::_expand() {
    if (m_size < m_capacity) {
        return;
    }
    
    m_capacity = std::max(m_capacity, g_default_capacity);
    
    T* old_elem = m_element;
    m_element = new T[m_capacity << 1];
    
    for (int i = 0; i < m_size; i++) {
        m_element[i] = old_elem[i];
    }
    
    delete []old_elem;
}

template <typename T>
void Vector<T>::_shrink() {
    if (m_size < g_default_capacity) {
        return;
    }
    if (m_size << 2 > m_capacity) {
        return;
    }
    T *old_elem = m_element;
    m_element = new T[m_capacity >> 1];
    for (int i = 0; i < m_size; i++) {
        m_element[i] = old_elem[i];
    }
    
    delete []old_elem;
    
}

template <typename T>
T & Vector<T>::operator[](Rank r) const{
    assert(0 <= r);
    assert(r < m_size);
    return m_element[r];
}

template <typename T>
Rank Vector<T>::insert(Rank r, T e) {
    assert(0 <= r);
    assert(r <= m_size);
    _expand();
    for (int i = m_size; i > r; i--) {
        m_element[i] = m_element[i - 1];
    }
    m_size++;
    m_element[r] = e;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    assert(lo <= hi);
    assert(0 <= lo);
    assert(hi <= m_size);
    if (lo == hi) {
        return 0;
    }
    while (hi <= m_size) {
        m_element[lo++] = m_element[hi++];
        m_size--;
    }
    _shrink();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r) {
    assert(0 <= r);
    assert(r < m_size);
    T e = m_element[r];
    remove(r, r + 1);
    return e;
}

template<typename T>
void Vector<T>::unsort() {
    unsort(0, m_size);
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    T *elem = m_element + lo;
    for (int i = hi - lo; i > 0; i--) {
        swap(elem[i - 1], elem[rand() % i]);
    }
}

template<typename T>
void Vector<T>::sort() {
    sort(0, m_size);
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    
}

template<typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const {
    while (lo < hi-- && e != m_element[hi]);
    return hi;
}

template<typename T>
Rank Vector<T>::find(const T &e) const {
    return find(e, 0, m_size);
}

template<typename T>
Rank Vector<T>::_bi_search(T const &e, Rank lo, Rank hi) const {
    while (lo < hi) {
        Rank mid = lo + (hi - lo) / 2;
        (e < m_element[mid]) ? hi = mid : lo = mid + 1;
    }
    return lo--;
}

template<typename T>
Rank Vector<T>::_fib_search(T const &e, Rank lo, Rank hi) const {
    while (lo < hi) {
        Fib fib(hi - lo);
        while (hi - lo < fib.get()) {
            fib.prev();
        }
        Rank mid = lo + fib.get() - 1;
        (e < m_element[mid]) ? hi = mid : lo = mid + 1;
    }
    return lo--;
}

template<typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const {
    return (rand() % 2) ? _bi_search(e, lo, hi)
    : _fib_search(e, lo, hi);
}

template<typename T>
Rank Vector<T>::search(T const &e) const {
    return search(e, 0, m_size);
}

template <typename T>
int Vector<T>::deduplicate() {
    int old_size = m_size;
    for (Rank i = 1; i < m_size;) {
        find(m_element[i], 0, i) < 0 ?
        i++ : remove(i);
    }
    return old_size - m_size;
}


template <typename T>
int Vector<T>::disordered() {
    int n = 0;
    for (int i = 1; i < m_size; i++) {
        if (m_element[i - 1] > m_element[i]) {
            n++;
        }
    }
    return n;
}

template <typename T>
int Vector<T>::uniquify() {
    Rank i = 0;
    Rank j = 0;
    while (++j < m_size) {
        if (m_element[i] != m_element[j]) {
            m_element[++i] = m_element[j];
        }
    }
    m_size = ++i;
    _shrink();
    return j - i;
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < m_size; i++) {
        visit(m_element[i]);
    }
}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &visit) {
    for (int i = 0; i < m_size; i++) {
        visit(m_element[i]);
    }
}



#endif
