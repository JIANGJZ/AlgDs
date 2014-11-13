#ifndef AlgDs_huffman_h
#define AlgDs_huffman_h
#include "../bitmap/bitmap.h"
#include "../tree/binary_tree.h"
#include "../dictionary/hashtable.h"
#include "../priority_queue/complete_binary_heap.h"
#include "../priority_queue/left_heap.h"
#include "../list/list.h"

#include <iostream>

using namespace std;

#define CHAR_NUM 46

typedef Bitmap HuffCode;

struct HuffChar {
    char m_ch;
    int m_weight;
    HuffChar(char c = '^', int w = 0) : m_ch(c), m_weight(w) {
        
    }
    
    bool operator == (HuffChar const & hc) {
        return hc.m_weight == this->m_weight;
    }
    //故意写相反，这样就构造了一个小顶堆
    bool operator < (HuffChar const& hc) {
        return hc.m_weight > this->m_weight;
    }
    
};

typedef BinTree<HuffChar> HuffTree;
typedef HashTable<char, char*> HuffTable;
typedef PQ_Complheap<HuffTree*> HuffForest1;
typedef PQ_LeftHeap<HuffTree*> HuffForest2;
typedef List<HuffTree*> HuffForest3;

int* statistics(char* sample_text_file) {
    int* freq = new int[CHAR_NUM];
    memset(freq, 0, sizeof(int)*CHAR_NUM);
    FILE* fp = fopen(sample_text_file, "r");
    for (char ch; fscanf(fp, "%c", &ch);) {
        if (ch >= 0x20) {
            freq[ch - 0x20]++;
        }
    }
    fclose(fp);
    return freq;
}

HuffForest3* initForest_list(int* freq) {
    HuffForest3* forest = new HuffForest3();
    for(int i = 0; i < CHAR_NUM; i++) {
        forest->insertAsLast(new HuffTree);
        forest->last()->m_data->insertAsRoot(HuffChar(0x20+i, freq[i]));
    }
    return forest;
}

HuffForest2* initForest_PQ_left(int* freq) {
    HuffForest2* forest = new HuffForest2();
    for (int i = 0; i < CHAR_NUM; i++) {
        BinTree<HuffChar>* tree = new BinTree<HuffChar>();
        tree->insertAsRoot(HuffChar(0x20+i, freq[i]));
        forest->insert(tree);
    }
    return forest;
}

HuffForest1* initForest_PQ_Complheap(int* freq) {
    HuffForest1* forest = new HuffForest1();
    for(int i = 0; i < CHAR_NUM; i++) {
        BinTree<HuffChar>* tree = new BinTree<HuffChar>();
        tree->insertAsRoot(HuffChar(0x20+i, freq[i]));
        forest->insert(tree);
    }
    return forest;
}

HuffTree* minChar(HuffForest3* forest) {
    ListNode<HuffTree*>* p = forest->first();
    ListNode<HuffTree*>* minChar = p;
    int minWeight = p->m_data->m_root->m_data.m_weight;
    while ((p = p->m_succ) != forest->last()) {
        if (minWeight > p->m_data->m_root->m_data.m_weight) {
            minWeight = p->m_data->m_root->m_data.m_weight;
            minChar = p;
        }
    }
    return forest->remove(minChar);
}

HuffTree* generateTree(HuffForest3* forest) {
    while (1 < forest->size()) {
        HuffTree* s1 = minChar(forest);
        HuffTree* s2 = minChar(forest);
        
        HuffTree* s = new HuffTree();
        s->insertAsRoot(HuffChar('^', s1->m_root->m_data.m_weight + s2->m_root->m_data.m_weight));
        s->attachAsLC(s->m_root, s1);
        s->attachAsLC(s->m_root, s2);
        forest->insertAsLast(s);
    }
 
    return forest->first()->m_data;
}

HuffTree* generateTree(HuffForest1* forest) {
    while (1 < forest->size()) {
        HuffTree* s1 = forest->delMax();
        HuffTree* s2 = forest->delMax();
        HuffTree* s = new HuffTree();
        s->insertAsRoot(HuffChar('^', s1->m_root->m_data.m_weight + s2->m_root->m_data.m_weight));
        s->attachAsLC(s->m_root, s1);
        s->attachAsRC(s->m_root, s2);
        forest->insert(s);
    }
    
    HuffTree* tree = forest->delMax();
    
    return tree;
}

static void generateTableEntry(Bitmap* code, int length, HuffTable* table,  BinNode<HuffChar>* v) {
    if (isLeaf(*v)) {
        table->put(v->m_data.m_ch, code->bits2string(length));
        return;
    }
    if (hasLChild(*v)) {
        code->clear(length);
        generateTableEntry(code, length+1, table, v->m_lchild);
    }
    if (hasRChild(*v)) {
        code->set(length);
        generateTableEntry(code, length+1, table, v->m_rchild);
    }
}

HuffTable* generateTable(HuffTree* tree) {
    HuffTable* table = new HuffTable();
    Bitmap* code = new Bitmap;
    generateTableEntry(code, 0, table, tree->m_root);
    release(code);
    return table;
}

void decode(HuffTree* tree, Bitmap* code, int n) {
    BinNode<HuffChar>* x = tree->m_root;
    for (int i = 0; i < n; i++) {
        x = code->test(i) ? x->m_rchild : x->m_lchild;
        if (isLeaf(*x)) {
            cout << x->m_data.m_ch;
            x = tree->m_root;
        }
    }
    
    if (x != tree->m_root) {
        cout << "..." << endl;
    }
}

int encode(HuffTable* table, Bitmap* codeString, char* s) {
    int n = 0;
    int m = (int)strlen(s);
    for (int i = 0; i < m; i++) {
        char** pCharCode = table->get(s[i]);
        if (!pCharCode) {
            pCharCode = table->get(s[i] + 'A' - 'a');
        }
        
        if(!pCharCode) {
            pCharCode = table->get(' ');
        }
        
        for (int m = (int)strlen(*pCharCode), j = 0; j < m; j++) {
            '1' == *(*pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
        }
        
    }
    cout << endl;
    return n;
}


int main(int argc, char* argv[]) {
    int* freq = statistics(argv[1]);
    HuffForest1* forest = initForest_PQ_Complheap(freq);
    HuffTree* tree = generateTree(forest);
    release(freq);
    
    HuffTable* table = generateTable(tree);
    for (int i = 2; i < argc; i++) {
        Bitmap* codeString = new Bitmap();
        int n = encode(table, codeString, argv[i]);
        cout << codeString->bits2string(n);
        
        decode(tree, codeString, n);
        release(codeString);
    }
    
    release(table);
    release(tree);
    return 0;
    
}

#endif
