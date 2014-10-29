#ifndef AlgDs_huffman_h
#define AlgDs_huffman_h
#include "../bitmap/bitmap.h"
#include "../tree/binary_tree.h"
#include "../dictionary/hashtable.h"
#include "../priority_queue/complete_binary_heap.h"
#include "../priority_queue/left_heap.h"

typedef Bitmap HuffCode;

struct HuffChar {
    char m_ch;
    int m_weight;
    HuffChar(char c = '^', int w = 0) : m_ch(c), m_weight(w) {
        
    }
    
    bool operator == (HuffChar const & hc) {
        return hc.m_weight == this->m_weight;
    }
    
    bool operator < (HuffChar const& hc) {
        return hc.m_weight > this->m_weight;
    }
    
};

typedef BinTree<HuffChar> HuffTree;
typedef HashTable<char, char*> HuffTable;
typedef PQ_Complheap<HuffTree>* HuffForest1;
typedef PQ_LeftHeap<HuffTree>* HuffForest2;


#endif
