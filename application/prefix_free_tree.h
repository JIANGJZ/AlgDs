#ifndef AlgDs_prefix_free_tree_h
#define AlgDs_prefix_free_tree_h
#include "../tree/binary_tree.h"
#include "../vector/vector.h"
#include "../dictionary/skiplist.h"
#include "../bitmap/bitmap.h"

#include <iostream>

using namespace std;

typedef BinTree<char> PFCTree;

typedef Vector<PFCTree*> PFCForest;

typedef Skiplist<char, char*> PFCTable;

#define N_CHAR (0x80 - 0x20)

PFCForest* initForest() {
    PFCForest* forest = new PFCForest;
    
    for (int i = 0; i < N_CHAR; i++) {
        forest->insert(i, new PFCTree());
        (*forest)[i]->insertAsRoot(0x20 + i);
    }
    
    return forest;
}

PFCTree* generateTree(PFCForest* forest) {
    srand((unsigned int)time(NULL));
    
    while ( 1 < forest->size()) {
        PFCTree* s = new PFCTree;
        s->insertAsRoot('^');
        int rank1 = rand() % forest->size();
        s->attachAsLC(s->m_root, (*forest)[rank1]);
        forest->remove(rank1);
        int rank2 = rand() % forest->size();
        s->attachAsRC(s->m_root, (*forest)[rank2]);
        forest->remove(rank2);
        forest->insert(forest->size(), s);
        
        cout << s->m_root->m_lchild->m_data << " and "
        << s->m_root->m_rchild->m_data << " merge." << endl;
    }
    
    return (*forest)[0];
    
}

void generateTableEntry(Bitmap* code, int length, PFCTable* table, BinNode<char>* node) {
    if (isLeaf(*node)) {
        table->put(node->m_data, code->bits2string(length));
    }
    if (hasLChild(*node)) {
        code->clear(length);
        generateTableEntry(code, length+1, table, node->m_lchild);
    }
    
    if (hasRChild(*node)) {
        code->set(length);
        generateTableEntry(code, length+1, table, node->m_rchild);
    }
}

PFCTable* generateTable(PFCTree* tree) {
    PFCTable* table = new PFCTable();
    Bitmap* code = new Bitmap();
    generateTableEntry(code, 0, table, tree->m_root);
    release(code);
    return table;
}


int encode(PFCTable* table, Bitmap& codeString, char* s) {
    int n = 0;
    size_t len1 = strlen(s);
    for (int i = 0; i < len1; i++) {
        char**pCharCode = table->get(s[i]);
        if (!pCharCode) {
            pCharCode = table->get(s[i] + 'A' - 'a');
        }
        
        if (!pCharCode) {
            pCharCode = table->get(' ');
        }
        
        size_t len2 = strlen(*pCharCode);
        for (int j = 0; j < len2; j++) {
            '1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);
        }
    }
    return n;
}


void decode(PFCTree* tree, Bitmap& code, int n) {
    BinNode<char>* x = tree->m_root;
    for (int i = 0; i < n; i++) {
        x = code.test(i) ? x->m_rchild : x->m_lchild;
        if (isLeaf(*x)) {
            cout << x->m_data;
            x = tree->m_root;
        }
    }
    
    if(x != tree->m_root) {
        cout << "code seems to be incomplete..." << endl;
    }
}


#endif
