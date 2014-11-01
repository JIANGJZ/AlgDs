#ifndef AlgDs_bin_search_tree_h
#define AlgDs_bin_search_tree_h

template <typename T>
class BST : public BinTree<T> {
public:
    virtual BinNode<T>* search(const T & value);
    
    virtual BinNode<T>* insert(const T & value);
    
    virtual bool remove(const T& value);
    
private:
    BinNode<T>* m_hot;
    
    BinNode<T>* rotate(BinNode<T>* node);
    
    BinNode<T>* connect34();
    
};

template <typename T>
static BinNode<T>* searchIn(BinNode<T>* &node, const T& value, BinNode<T>* &hot = NULL) {
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
    return searchIn(this->m_root, value, m_hot);
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
static BinNode<T>* removeAt(BinNode<T>* &x, BinNode<T>* &xm_hot) {
    return NULL;
}

#endif
