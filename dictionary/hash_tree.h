#ifndef AlgDs_hash_tree_h
#define AlgDs_hash_tree_h

#include "dictionary.h"

#include <iostream>
using namespace std;

const int SIZE = 32;

const int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

template <typename K, typename V>
class HashNode
{
public:
    HashNode();
    
    HashNode(K key, V val);
    
    ~HashNode();
    
    K m_key;
    V m_val;
    bool m_occupied;
    HashNode* m_child[SIZE];
};

template <typename K, typename V>
HashNode<K, V>::HashNode()
{
    m_occupied = false;
    for (int i = 0; i < SIZE; i++) {
        m_child[i] = nullptr;
    }
}

template <typename K, typename V>
HashNode<K, V>::HashNode(K key, V val)
{
    m_key = key;
    m_val = val;
    m_occupied = false;
    for (int i = 0; i < SIZE; i++) {
        m_child[i] = nullptr;
    }
}

template <typename K, typename V>
HashNode<K, V>::~HashNode()
{
    
}

template <typename K, typename V>
class HashTree : public Dictionary<K, V>
{
public:
    HashTree();
    
    ~HashTree();
    
    bool put(K key, V val);
    
    V* get(K key) const = 0;
    
    bool remove(K key);
    
private:
    HashNode<K, V>* m_root;
    
    void insert(HashNode<K, V>* hash_node, int level, K key, V val);
  
    V* find(HashNode<K, V>* hash_node, int level, K key);
    
    void deleteNode(HashNode<K, V>* hash_node, int level, K key);
};


template <typename K, typename V>
HashTree<K, V>::HashTree()
{
    m_root = new HashNode<K, V>();
}

template <typename K, typename V>
HashTree<K, V>::~HashTree()
{
    
}

template <typename K, typename V>
bool HashTree<K, V>::put(K key, V val)
{
    insert(m_root, 0, key, val);
    return true;
}

template <typename K, typename V>
void insert(HashNode<K, V>* hash_node, int level, K key, V val)
{
    if (hash_node->m_occupied == false){
        hash_node->m_key = key;
        hash_node->m_value = val;
        hash_node->m_occupied = true;
        return;
    }
    
    int index = key % prime[level];
    if (hash_node->m_child[index] == nullptr){
        hash_node->m_child[index] = new HashNode<K, V>;
    }
    
    level += 1;
    insert(hash_node->m_child[index], level, key, val);
    
}

template <typename K, typename V>
V* HashTree<K, V>::get(K key) const
{
    return find(m_root, 0, key);
}

template <typename K, typename V>
V* HashTree<K, V>::find(HashNode<K, V> *hash_node, int level, K key)
{
    if (hash_node->m_occupied == true) {
        if (hash_node->m_key == key) {
            return &hash_node->m_val;
        }
    }
    
    int index = key % prime[level];
    if (hash_node->m_child[index] == nullptr) {
        return nullptr;
    }
    
    level += 1;
    return find(hash_node->m_child[index], level, key);
}

template <typename K, typename V>
void HashTree<K, V>::deleteNode(HashNode<K, V>* hash_node, int level, K key)
{
    if (hash_node->m_occupied == true) {
        if (hash_node->m_key == key) {
            hash_node->m_occupied = false;
            return;
        }
    }
    
    int index = key % prime[level];
    
    if(hash_node->m_child[index] == nullptr) {
        return;
    }
    
    level += 1;
    deleteNode(hash_node->m_child[index], 0, key);
}

template <typename K, typename V>
bool HashTree<K, V>::remove(K key)
{
    deleteNode(m_root, 0, key);
    return true;
}

#endif
