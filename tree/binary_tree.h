#ifndef AlgDs_binary_tree_h
#define AlgDs_binary_tree_h

#include <algorithm>

#include <stdlib.h>


template <typename T>
struct BinNode {
    BinNode() {}
    
    BinNode(T const& e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr, int h = 0) :
    m_data(e), m_parent(p), m_lchild(lc), m_rchild(rc), m_height(h) {}
    
    BinNode<T>* insertAsLchild(T const& data);
    
    BinNode<T>* insertAsRchild(T const& data);
    
    bool operator < (BinNode const &node) {
        return m_data < node.m_data;
    }
    
    bool operator == (BinNode const &node) {
        return m_data == node.m_data;
    }
    
    /// \breif 节点的size 需要通过动态递归获取， tree的size是静态保存
    int size();
    
    int height();
    
    template<typename VST>
    void travPre(VST &visit);
    
    template<typename VST>
    void travIn(VST &visit);
    
    template<typename VST>
    void travPost(VST &visit);
    
    template<typename VST>
    void travLevel(VST &visit);
    
    template<typename VST>
    void travPre_R(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travPre_I(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travIn_R(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travIn_I(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travPost_R(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travPost_I(BinNode<T>* node, VST &visit);
    
    T m_data;
    BinNode* m_parent;
    BinNode* m_lchild;
    BinNode* m_rchild;
    int m_height;
};


template <typename T>
BinNode<T>* BinNode<T>::insertAsLchild(T const& data) {
    return this->m_lchild = new BinNode<T>(data, this);
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRchild(T const& data) {
    return this->m_rchild = new BinNode<T>(data, this);
}

template <typename T>
int BinNode<T>::size() {
    int ret = 1;
    if (m_lchild) {
        ret += m_lchild->size();
    }
    if (m_rchild) {
        ret += m_rchild->size();
    }
    return ret;
}

template <typename T>
int BinNode<T>::height() {
    return m_height;
}

template <typename T>
template <typename VST>
void BinNode<T>::travPre(VST &visit){
    switch (rand() % 2) {
        case 0:
            travPre_R(this, visit);
            break;
        case 1:
            travPre_I(this, visit);
        default:
            break;
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST &visit){
    switch (rand() % 2) {
        case 0:
            travPre_R(this, visit);
            break;
        case 1:
            travPre_I(this, visit);
            break;
        default:
            break;
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travPost(VST &visit){
    switch (rand() % 2) {
        case 1:
            travPost_I(this, visit);
            break;
        case 2:
            travPost_R(this, visit);
            break;
        default:
            break;
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST &visit){
    
}

template <typename T>
template <typename VST>
void BinNode<T>::travPre_R(BinNode<T>* node, VST &visit){
    if (node == nullptr) {
        return;
    }
    visit(node->m_data);
    travPre_R(node->m_lchild, visit);
    travPre_R(node->m_lchild, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::travPre_I(BinNode<T>* node, VST &visit) {
    
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn_R(BinNode<T>* node, VST &visit){
    if (node == nullptr) {
        return;
    }
    travPre_R(node->m_lchild, visit);
    visit(node->m_data);
    travPre_R(node->m_lchild, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn_I(BinNode<T>* node, VST &visit){

}

template <typename T>
template <typename VST>
void BinNode<T>::travPost_R(BinNode<T>* node, VST &visit){
    if (node == nullptr) {
        return;
    }
    travPre_R(node->m_lchild, visit);
    travPre_R(node->m_lchild, visit);
    visit(node->m_data);
}

template <typename T>
template <typename VST>
void BinNode<T>::travPost_I(BinNode<T>* node, VST &visit){
    
}



template <typename T>
class BinTree {
private:
    int m_size;
    BinNode<T>* m_root;
    
    virtual int updateHeight(BinNode<T>* x) {
        return x->m_height = 1 + max(x->m_lchild->height(),
                                     x->m_rchild->height());
    }
    
    void updateHeightAbove(BinNode<T>* x) {
        while (x) {
            updateHeight(x);
            x = x->m_parent;
        }
    }
public:
    
    const BinNode<T>* getRoot() const {
        return m_root;
    }
    
    bool empty() const {
        bool result = (m_root == nullptr);
        return result;
    }
    
    int size() const{
        return m_size;
    }
    
    /// \breif 每个节点都会保存height, 但是height也需要根据插入不断更新
    int height(BinNode<T>* p) {
        if (p) {
            return p->height();
        }
        return -1;
    }
    
    BinNode<T>* insertAsRoot(T const &e);
    
    BinNode<T>* insertAsLC(BinNode<T>* node, T const &e);
    
    BinNode<T>* insertAsRC(BinNode<T>* node, T const &e);
    
    BinNode<T>* attachAsLC(BinNode<T>* node, BinTree<T>* &sub_tree);
    
    BinNode<T>* attachAsRC(BinNode<T>* node, BinTree<T>* &sub_tree);
    
    int remove(BinNode<T>* node);
    
    int removeAt(BinNode<T>* node);
    
    BinNode<T>* getSubTree(BinNode<T>* node);
    
    template <typename VST>
    void travelPre(VST &visit) {
        if (m_root) {
            m_root->travPre(visit);
        }
    }
    
    template <typename VST>
    void travelIn(VST &visit) {
        if (m_root) {
            m_root->travIn(visit);
        }
    }
    
    template <typename VST>
    void travelPost(VST &visit) {
        if (m_root) {
            m_root->travPost(visit);
        }
    }
    
    template <typename VST>
    void travelLevel(VST &visit) {
        if (m_root) {
            m_root->travLevel(visit);
        }
    }
};

template <typename T>
BinNode<T>* BinTree<T>::insertAsRoot(const T &e) {
    m_size++;
    m_root = new BinNode<T>(e);
    return m_root;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T> *node, const T &e) {
    m_size++;
    node->insertAsLC(e);
    updateHeightAbove(node);
    return node->m_rchild;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T> *node, const T &e) {
    m_size++;
    node->insertAsRC(e);
    updateHeightAbove(node);
    return node->m_lchild;
}

template <typename T>
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T> *node, BinTree<T> *&sub_tree) {
    node->m_lchild = sub_tree->getRoot();
    node->m_lchild->m_parent = node;
    
    this->m_size += sub_tree->size();
    updateHeightAbove(node);
    
    sub_tree->m_root = nullptr;
    sub_tree->m_size = 0;
    delete sub_tree;
    sub_tree = nullptr;
    
    return node;
}

template <typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T> *node, BinTree<T> *&sub_tree) {
    node->m_rchild = sub_tree->getRoot();
    node->m_rchild->m_parent = node;
    
    this->m_size += sub_tree->size();
    updateHeightAbove(node);
    
    sub_tree->m_root = nullptr;
    sub_tree->m_size = 0;
    delete sub_tree;
    sub_tree = nullptr;
    
    return node;
}

template <typename T>
int BinTree<T>::remove(BinNode<T> *node) {
    return 0;
}

template <typename T>
int BinTree<T>::removeAt(BinNode<T> *node) {
    return 0;
}

template <typename T>
BinNode<T>* BinTree<T>::getSubTree(BinNode<T> *node) {
    return nullptr;
}

#endif
