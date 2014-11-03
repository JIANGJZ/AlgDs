#ifndef AlgDs_bin_search_tree_h
#define AlgDs_bin_search_tree_h

template <typename T>
class BST : public BinTree<T> {
public:
    virtual BinNode<T>* search(const T & value);
    
    virtual BinNode<T>* insert(const T & value);
    
    virtual bool remove(const T& value);
    
    static BinNode<T>* succ(BinNode<T>* node);
    
private:
    BinNode<T>* m_hot;
    
    BinNode<T>* rotate(BinNode<T>* node);
    
    BinNode<T>* connect34();
    
};

template <typename T>
static bool equal(T e, BinNode<T>* node) {
    return ((!node) || (e) == (node)->m_data);
}

template <typename T>
static BinNode<T>* & searchIn_i(BinNode<T>* &node, const T& value, BinNode<T>* &hot = NULL) {
    if (equal(value, node)) {
        return node;
    }
    while (1) {
        BinNode<T>* & c = ((value < hot->m_data) ? hot->m_lchild : hot->m_rchild);
        if (equal(value, node)) {
            return node;
        }
        hot = c;
    }
}


template <typename T>
static BinNode<T>* searchIn_r(BinNode<T>* &node, const T& value, BinNode<T>* &hot = NULL) {
    if (!node || value == node->m_data) {
        return node;
    }
    hot = node;
    if (value < node->m_data) {
        return searchIn(node->m_lchild, value, hot);
    } else {
        return searchIn(node->m_rchild, value, hot);
    }
}

template <typename T>
BinNode<T>* BST<T>::search(const T& value) {
    return searchIn_r(this->m_root, value, m_hot);
}

template <typename T>
BinNode<T>* BST<T>::insert(const T& value) {
    BinNode<T>* & x = search(value);
    if (!x) {
        x = new BinNode<T>(value, m_hot);
        this->m_size++;
        this->updateHeight(x);
    }
    return x;
}

template <typename T>
BinNode<T>* succ(BinNode<T>* node) {
    BinNode<T>* s = node;
    if (s->m_rchild) {
        s = s->m_rchild;
        while (hasLChild(*s)) {
            s = s->m_lchild;
        }
    }else {
        while (isRChild(*s)) {
            s = s->m_parent;
        }
        s = s->m_parent;
    }
    return s;
}

template <typename T>
bool BST<T>::remove(const T& value) {
    BinNode<T>* &x = search(value);
    if (!x) {
        return false;
    }
    removeAt(x, m_hot);
    this->m_size--;
    this->updateHeight(x);
    return true;
}

template <typename T>
static BinNode<T>* removeAt(BinNode<T>* &x, BinNode<T>* &m_hot) {
    BinNode<T>* &w = x;
    BinNode<T>* &succ = NULL;
    if (!hasLChild(*x)) {
        succ = x = x->m_rchild;
    } else if(!hasRChild(*x)) {
        succ = x= x->m_lchild;
    } else {
        w = BST<T>::succ(w);
        swap(x->m_data, w->m_data);
        BinNode<T>* u = w->m_parent;
        ((u == x)? u->m_rchild : u->m_lchild) = succ = w->rchild;
    }
    m_hot = w->m_parent;
    if (succ) {
        succ->m_parent = m_hot;
    }
    release(w->m_data);
    release(w);
    return succ;
}



#endif
