#ifndef AlgDs_skiplist_h
#define AlgDs_skiplist_h

#include "entry.h"
#include "../List/list.h"
#include "dictionary.h"

#include <stdlib.h>

template <typename T>
class QuadlistNode {
    T m_entry;
    QuadlistNode<T>* m_pre, m_succ, m_above, m_below;
public:
    QuadlistNode(T e = T(), QuadlistNode<T> pre = nullptr, QuadlistNode<T> succ = nullptr,
                 QuadlistNode<T> above = nullptr, QuadlistNode<T> below = nullptr) :
                 m_entry(e), m_pre(pre), m_succ(succ), m_above(above), m_below(below){ };
    
    QuadlistNode<T>* insertAsSuccAbove(T const& e, QuadlistNode<T> b = nullptr);
};

template <typename T>
QuadlistNode<T>* QuadlistNode<T>::insertAsSuccAbove(T const& e, QuadlistNode<T> b) {
    QuadlistNode<T> new_node = new QuadlistNode<T>(e, this, this->m_succ, nullptr, b);
    m_succ->m_pre = new_node;
    this->m_succ = new_node;
    if (b) {
        b->above = new_node;
    }
    return new_node;
}



template <typename T>
class Quadlist {
private:
    int m_size;
    QuadlistNode<T>* m_header;
    QuadlistNode<T>* m_tailer;
    void init();
    int clear();
public:
    Quadlist() {
        init();
    }
    ~Quadlist() {
        clear();
        delete m_header;
        delete m_tailer;
    }
    
    int size() const {
        return m_size;
    }
    
    bool empty() const {
        return m_size <= 0;
    }
    
    Quadlist<T>* getFirst() {
        return m_header->m_succ;
    }
    
    Quadlist<T>* getLast() {
        return m_tailer->m_pred;
    }
    
    bool valid(Quadlist<T>* p) {
        return p && (m_tailer != p) && (m_header != p);
    }
    
    T remove(QuadlistNode<T>* p);
    
    Quadlist<T>* insertAfterAbove(T const&e, QuadlistNode<T>* p, QuadlistNode<T>* b = nullptr);
    
    void traverse(void(*visit)(T&));
    
    template<typename VST>
    void traverse(VST&);
};

template <typename T>
void Quadlist<T>::init() {
    m_header = new QuadlistNode<T>();
    m_tailer = new QuadlistNode<T>();
    m_header->m_succ = m_tailer;
    m_header->m_pre = nullptr;
    m_tailer->m_pre = m_header;
    m_tailer->m_succ = nullptr;
    m_header->m_above = m_tailer->m_above = nullptr;
    m_tailer->m_below = m_tailer->m_below = nullptr;
    m_size = 0;
}


template <typename T>
Quadlist<T>* Quadlist<T>::insertAfterAbove(const T &e, QuadlistNode<T> *p, QuadlistNode<T>* b) {
    m_size++;
    p->insertAsSuccAbove(e, b);
}

template <typename T>
T Quadlist<T>::remove(QuadlistNode<T>* p) {
    p->m_pre->m_succ = p->m_succ;
    p->m_succ->m_pre = p->m_pre;
    m_size--;
    T e = p->m_entry;
    delete p;
    return e;
}

template <typename T>
int Quadlist<T>::clear() {
    int oldSize = m_size;
    while (0 < m_size) {
        remove(m_header->m_succ);
    }
    return oldSize;
}

template <typename T>
void Quadlist<T>::traverse(void(*visit)(T&)) {
    QuadlistNode<T> p = m_header;
    while ((p = p->m_succ) != m_tailer) {
        visit(p->m_entry);
    }
}

template <typename T>
template <typename VST>
void Quadlist<T>::traverse(VST& visit) {
    QuadlistNode<T>* p = m_header;
    while ((p = p->m_succ) != m_tailer) {
        visit(p->m_entry);
    }
}



template <typename K, typename V>
class Skiplist : public Dictionary<K, V>, List<Quadlist<Entry<K, V>>* >{
private:
    bool SkipSearch(List<Quadlist<Entry<K, V>>*>* &qlist,
                    QuadlistNode<Entry<K, V>>* &p,
                    K& k);
    
public:
    int size() {
        return List<Quadlist<Entry<K, V>>*>::empty() ? 0 : List<Quadlist<Entry<K, V>>*>::last()->m_data->size();
    }
    
    int level() {
        return List<Quadlist<Entry<K, V>>*>::size();
    }
    
    bool put(K key, V value);
    
    V* get(K k);
    
    bool remove(K k);
};

template <typename K, typename V>
bool Skiplist<K, V>::SkipSearch(List<Quadlist<Entry<K, V>> *> *&qlist, QuadlistNode<Entry<K, V> > *&p, K &k) {
    while(true) {
        while ((p->m_succ != nullptr) && (p->m_entry->key <= k)) {
            p = p->m_succ;
        }
        p = p->m_pre;
        if (p->m_pre && p->m_entry->key == k) {
            return true;
        }
        qlist = qlist->m_succ;
        if (qlist == nullptr) {
            return false;
        }
        
        p = p->m_pre ? p->m_below : qlist->m_data->first();
    }
}

template <typename K, typename V>
bool put(K key, V value) {
    Entry<K, V> e = Entry<K, V>(key, value);
    if (List<Quadlist<Entry<K, V>>*>::empty()) {
        List<Quadlist<Entry<K, V>>*>::insertAsFirst(new Quadlist<Entry<K, V>>());
    }
    List<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first();
    QuadlistNode<Entry<K, V> > *p = qlist->m_data->first();
    if (skipSearch(qlist, p, key)) {
        while (p->m_below != nullptr) {
            p = p->m_below;
        }
    }
    qlist = List<Quadlist<Entry<K, V>>*>::last();
    QuadlistNode<Entry<K, V> >* b = qlist->m_data->insertAfterAbove(e, p);
    
    while (rand() & 1) {
        while (qlist->m_data->valid(p) && !p->m_above) {
            p = p->m_pre;
        }
        
        if (!qlist->m_data->valid(p)) {
            if (qlist == List<Quadlist<Entry<K, V>>*>::first()) {
                List<Quadlist<Entry<K, V>>*>::insertAsFirst(new Quadlist<Entry<K, V>>());
            }
            p = qlist->m_pre->m_data->first()->m_pre;
        }else {
            p = p->m_above;
        }
        qlist = qlist->m_pre;
        b = qlist->m_data->insertAfterAbove(e, p, b);
    }
    
    return true;
}


template <typename K, typename V>
V* Skiplist<K, V>::get(K k) {
    if (List<Quadlist<Entry<K, V>>*>::empty()) {
        return nullptr;
    }
    
    List<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first();
    QuadlistNode<Entry<K, V> > *p = qlist->m_data->first();
    
    return SkipSearch(qlist, p, k) ? &(p->m_entry->value) : nullptr;
}

template <typename K, typename V>
bool Skiplist<K, V>::remove(K k) {
    if (List<Quadlist<Entry<K, V>>*>::empty()) {
        return false;
    }
    List<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first();
    QuadlistNode<Entry<K, V> > *p = qlist->m_data->first();
    if (!SkipSearch(qlist, p, k)) {
        return false;
    }
    
    do {
        QuadlistNode<Entry<K, V>>* lower = p->m_below;
        qlist->m_data->remove(p);
        p = lower;
        qlist = qlist->m_succ;
    }while(p->m_succ != nullptr);
    
    while (!List<Quadlist<Entry<K, V>>*>::empty() && List<Quadlist<Entry<K, V>>*>::first()->m_data->empty()) {
        List<Quadlist<Entry<K, V>>*>::remove(List<Quadlist<Entry<K, V>>*>::first());
    }
    
    return true;
}


#endif
