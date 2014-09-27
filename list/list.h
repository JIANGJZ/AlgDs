#ifndef __AlgDs__list__
#define __AlgDs__list__
typedef int Rank;

template <typename T>
struct ListNode {
    ListNode() {};
    ListNode(T const &e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr)
            : m_data(e), m_prev(p), m_succ(s) {};
    
    ListNode<T>* insert_as_prev(T const& e);
    
    ListNode<T>* insert_as_succ(T const& e);
    
    T m_data;
    ListNode<T>* m_prev;
    ListNode<T>* m_succ;
};

template <typename T>
class List {
private:
    int m_size;
    ListNode<T>* m_header;
    ListNode<T>* m_tailer;
    
protected:
    void init();
    
    void copy_nodes(ListNode<T>* p, int num);
    
public:
    List () {
        init();
    }
    
    ~List() {
        clear();
        delete m_header;
        m_header = nullptr;
        delete m_tailer;
        m_tailer = nullptr;
    }
    
    List(List<T> const& L) {
        copy_nodes(L.first(), L.m_size);
    }
    
    List<T>(List<T> const& L, Rank r, int num) {
        assert(0 <= r < L.m_size);
        copy_nodes(L[r], num);
    }
    
    Rank size() const {
        return m_size;
    }
    
    bool empty() const {
        return m_size <= 0;
    }
    
    ListNode<T>* first() const {
        if (m_size == 0) {
            return nullptr;
        }
        return m_header->m_succ;
    }
    
    ListNode<T>* last() const {
        if (m_size == 0) {
            return nullptr;
        }
        return m_tailer->m_prev;
    }
    
    T& operator [](Rank r) const;
    
    ListNode<T>* insert_as_first(T const &e);
    
    ListNode<T>* insert_as_last(T const &e);
    
    ListNode<T>* insert_before(ListNode<T>* p, T const &e);
    
    ListNode<T>* insert_after(ListNode<T>* p, T const &e);
    
    T remove(ListNode<T>* p);
    
    int clear();
    
    /// \brief 保证 0 < n < Rank(p) < m_size
    ListNode<T>* find(T const &e, int n, ListNode<T> *p) const;
    
    ListNode<T>* find(T const &e) const;
    
    /// \breif search 在链表中和find的复杂度相同
    ListNode<T>* search(T const &e, int n, ListNode<T> *p) const;
    
    ListNode<T>* search(T const &e) const;
    
    ListNode<T>* select_max(int n, ListNode<T> *p) const;
    
    ListNode<T>* select_max() const;
    
    int deduplicate();
    
    /// \brief uniquify 的复杂度在链表中和search 的复杂度也不相同
    int uniquify();
    
    void traverse(void (*visit)(T &));
    
    template<typename VST> void traverse(VST &visit);
    
    /// \brief 双向链表的逆转方式可以比单向链表简单
    void reverse();
    
    void sort(ListNode<T>* p, int n);
    
    void sort();
};


template <typename T>
ListNode<T>* ListNode<T>::insert_as_prev(const T &e){
    ListNode<T>* new_node = new ListNode(e, m_prev, this);
    m_prev->m_succ = new_node;
    m_prev = new_node;
    return new_node;
}

template <typename T>
ListNode<T>* ListNode<T>::insert_as_succ(const T &e){
    ListNode<T>* new_node = new ListNode(e, this, m_succ);
    m_succ->m_prev = new_node;
    m_succ = new_node;
    return new_node;
}

template <typename T>
void List<T>::init() {
    m_header = new ListNode<T>();
    m_tailer = new ListNode<T>();
    
    m_header->m_succ = m_tailer;
    m_tailer->m_prev = m_header;
    
    m_header->m_prev = nullptr;
    m_tailer->m_succ = nullptr;
    
    m_size = 0;
}

template <typename T>
T& List<T>::operator[](Rank r) const {
    assert(0 <= r < m_size);
    ListNode<T>* p = m_header->m_succ;
    while (0 < r--) {
        p = p->m_succ;
    }
    return p->m_data;
}

template <typename T>
ListNode<T>* List<T>::insert_as_first(const T &e) {
    m_size++;
    return m_header->insert_as_succ(e);
}

template <typename T>
ListNode<T>* List<T>::insert_as_last(const T &e){
    m_size++;
    return m_tailer->insert_as_prev(e);
}

template <typename T>
ListNode<T>* List<T>::insert_before(ListNode<T> *p, const T &e){
    m_size++;
    return p->insert_as_prev(e);
}

template <typename T>
ListNode<T>* List<T>::insert_after(ListNode<T> *p, const T &e) {
    m_size++;
    return p->insert_as_succ(e);
}

template <typename T>
T List<T>::remove(ListNode<T> *p) {
    T e = p->m_data;
    p->m_prev->m_succ = p->m_succ;
    p->m_succ->m_prev = p->m_prev;
    m_size--;
    delete p;
    return e;
}

template <typename T>
int List<T>::clear() {
    int old_size = m_size;
    while (0 < m_size) {
        remove(m_header->m_succ);
    }
    return old_size;
}

template <typename T>
void List<T>::copy_nodes(ListNode<T> *p, int num) {
    init();
    while (0 < num--) {
        insert_as_Last(p->m_data);
        p = p->m_succ;
    }
}

template <typename T>
ListNode<T>* List<T>::find(T const&e, int n, ListNode<T>* p) const {
    while (0 < n--) {
        p = p->m_prev;
        if (e == (p->m_data)) {
            return p;
        }
    }
    return nullptr;
}

template <typename T>
ListNode<T>* List<T>::find(const T &e) const {
    return find(e, m_size, m_tailer);
}

template <typename T>
ListNode<T>* List<T>::search(const T &e, int n, ListNode<T> *p) const {
    while (0 < n--) {
        p = p->m_prev;
        if (p->m_data <= e) {
            break;
        }
    }
    return p;
}

template <typename T>
ListNode<T>* List<T>::search(const T &e) const {
    return search(e, m_size, m_tailer);
}

template <typename T>
ListNode<T>* List<T>::select_max(int n, ListNode<T> *p) const {
    assert(0 <= n <= m_size);
    ListNode<T> *max = p->m_succ;
    ListNode<T> *curr = p->m_succ;
    while (0 < n--) {
        if (curr->m_data < curr->m_succ->m_data) {
            max = curr->m_succ;
        }
        curr = curr->m_succ;
    }
    return max;
}

template <typename T>
ListNode<T>* List<T>::select_max() const {
    return select_max(m_size, m_header);
}


template <typename T>
int List<T>::deduplicate() {
    if (m_size < 2) {
        return 0;
    }
    int old_size = m_size;
    ListNode<T>* p = m_header;
    Rank r = 0;
    while (p != m_tailer) {
        p = p->m_succ;
        ListNode<T>* q = find(p->m_data, r, p);
        (q == nullptr) ? r++ : remove(q);
    }
    return old_size - m_size;
}

template <typename T>
int List<T>::uniquify() {
    if (m_size < 2) {
        return 0;
    }
    int old_size = m_size;
    ListNode<T>* p = m_header;
    while (p != m_tailer) {
        ListNode<T>* q = p->m_succ;
        if (p->m_data != q->m_data) {
            p = q;
        } else {
            remove(q);
        }
    }
    return old_size - m_size;
}

template <typename T>
void List<T>::traverse(void (*visit)(T &)) {
    for (ListNode<T>* p = m_header->m_succ; p != m_tailer; p = p->m_succ) {
        visit(p->m_data);
    }
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit) {
    for (ListNode<T>* p = m_header->m_succ; p != m_tailer; p = p->m_succ) {
        visit(p->m_data);
    }
}

template <typename T>
void List<T>::reverse() {
    if (m_size < 2) {
        return;
    }
    ListNode<T>* p = m_header;
    ListNode<T>* q = m_tailer;
    for (int i = 1; i < m_size; i += 2) {
        swap((p = p->m_succ)->m_data, (q = q->m_prev)->m_data);
    }
    return;
}


template <typename T>
void List<T>::sort(ListNode<T> *p, int n) {
    
}

template <typename T>
void List<T>::sort() {
    
}


#endif
