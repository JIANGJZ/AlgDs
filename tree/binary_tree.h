#ifndef AlgDs_binary_tree_h
#define AlgDs_binary_tree_h

#include "v_stack.h"
#include "l_queue.h"
#include "../util/cleaner.h"

#include <algorithm>
#include <stdlib.h>

/// BinNode状态与性质的判断
#define isRoot(x) (!((x).m_parent))
#define isLChild(x) (!isRoot(x) && (&(x) == (x).m_parent.m_lchild))
#define isRChild(x) (!isRoot(x) && (&x == (x).m_parent.m_rchild))
#define hasParent(x) (!(isRoot(x)))
#define hasLChild(x) (!((x).m_lchild))
#define hasRChild(x) (!((x).m_rchild))
#define hasChild(x)  (hasLChild(x) || hasRChild(x))
#define hasBothChild(x) (hasLChild(x) && hasRChild(x))
#define isLeaf(x) (!hadChild)

/// 与BinNode具有特定关系的节点和指针
#define sibling(p)  \
    (isLChild(*p) ? (p)->m_parent->m_rchild : (p)->m_parent->m_lchild)

#define uncle(x)    \
    (isLChild(*(p.->m_parent)) ? (p)->m_parent->m_parent->m_rchild : (p)->m_parent->m_parent->m_lchild)



typedef enum {
    RB_RED,
    RB_BLACK
}RBColor;

template <typename T>
struct BinNode {
    BinNode() {}
    
    BinNode(T const& e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
    m_data(e), m_parent(p), m_lchild(lc), m_rchild(rc), m_height(h), m_npl(l), m_color(c){}

    
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
    void travPre_I1(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travPre_I2(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travIn_R(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travIn_I(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void travPost_R(BinNode<T>* node, VST &visit);
    
    static void gotoHLVFL(VStack<BinNode<T>>* &S);
    
    template<typename VST>
    void travPost_I(BinNode<T>* node, VST &visit);
    
    template<typename VST>
    void visitAlongLeftBranch(BinNode<T>* node, VST &visit, VStack<BinNode<T>*> &stk);
    
    template<typename VST>
    void visitAlongLeftBranch(BinNode<T>* node, VStack<BinNode<T>*> &stk);
    
    T m_data;
    BinNode* m_parent;
    BinNode* m_lchild;
    BinNode* m_rchild;
    int m_height;
    
    int m_npl;
    RBColor m_color;
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
    switch (rand() % 3) {
        case 0:
            travPre_R(this, visit);
            break;
        case 1:
            travPre_I1(this, visit);
            break;
        case 2:
            travPre_I2(this, visit);
            break;
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
    LQueue<BinNode<T>> *queue;
    queue->enqueue(this);
    while (!queue->empty()) {
        BinNode<T>* node = queue->dequeue();
        visit(node->m_data);
        
        if(hasLChild(*node)) {
            queue->enqueue(node->m_lchild);
        }
        
        if (hasRChild(*node)) {
            queue->enqueue(node->m_rchild);
        }
    }
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
void BinNode<T>::travPre_I1(BinNode<T>* node, VST &visit) {
    VStack<BinNode<T>*> stk;
    if (node != nullptr) {
        stk.push(node);
    }
    while (!stk.empty()) {
        BinNode<T>* x = stk.pop();
        
        visit(x->m_data);
        
        if(hasRChild(*x)) {
            stk.push(x->m_rchild);
        }
        
        if (hasLChild(*x)) {
            stk.push(x->m_lchild);
        }
    }
    
}

template <typename T>
template <typename VST>
void BinNode<T>::visitAlongLeftBranch(BinNode<T>* node, VST &visit, VStack<BinNode<T>*> &stk){
    while (node) {
        visit(node->m_data);
        if (node->hasRChild) {
            stk.push(node->m_rchild);
        }
        node = node->m_lchild;
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travPre_I2(BinNode<T>* node, VST &visit) {
    VStack<BinNode<T>*> stk;
    while (true) {
        visitAlongLeftBranch(node, visit, stk);
        if (stk.empty()) {
            break;
        }
        node = stk.pop();
    }
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
void BinNode<T>::visitAlongLeftBranch(BinNode<T> *node, VStack<BinNode<T> *> &stk) {
    while (node) {
        stk.push(node);
        node = node->m_lchild;
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn_I(BinNode<T>* node, VST &visit){
    VStack<BinNode<T>*> stk;
    while (true) {
        visitAlongLeftBranch(node, stk);
        if (node->empty()) {
            break;
        }
        visit(stk.pop());
        node = node->m_rchild;
    }
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
void BinNode<T>::gotoHLVFL(VStack<BinNode<T>> *&S) {
    
}

template <typename T>
template <typename VST>
void BinNode<T>::travPost_I(BinNode<T>* node, VST &visit){
    
}



template <typename T>
class BinTree {
public:
    int m_size;
    BinNode<T>* m_root;
    
    virtual int updateHeight(BinNode<T>* x) {
        return x->m_height = 1 + std::max(x->m_lchild->height(),
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
    
    BinTree<T>* getSubTree(BinNode<T>* node);
    
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
    release(sub_tree);
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
    release(sub_tree);
    sub_tree = nullptr;
    
    return node;
}

template <typename T>
int BinTree<T>::remove(BinNode<T> *node) {
    BinNode<T>* node_parent = node->m_parent;
    if (node_parent->m_rchild == node) {
        node_parent->m_rchild = nullptr;
    } else {
        node_parent->m_lchild = nullptr;
    }
    updateHeightAbove(node_parent);
    int n = removeAt(node);
    m_size -= n;
    return n;
}

template <typename T>
int BinTree<T>::removeAt(BinNode<T> *node) {
    if (!node) {
        return 0;
    }
    int n = 1 + removeAt(node->m_lchild) + removeAt(node->m_rchild);
    release(node->m_data);
    release(node);
    return n;
}

template <typename T>
BinTree<T>* BinTree<T>::getSubTree(BinNode<T> *node) {
    BinNode<T>* node_parent = node->m_parent;
    if (node_parent->m_rchild == node) {
        node_parent->m_rchild = nullptr;
    } else {
        node_parent->m_lchild = nullptr;
    }
    updateHeightAbove(node_parent);
    BinTree<T>* sub_tree = new BinTree<T>();
    sub_tree->m_root = node;
    sub_tree->m_root->m_parent = nullptr;
    sub_tree->m_size = node->size();
    m_size -= sub_tree->m_size;
    return sub_tree;
}

#endif
