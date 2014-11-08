#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

class LRUCache
{
public:
    struct CacheNode
    {
        int m_key;
        int m_value;
        CacheNode(int key, int value) : m_key(key), m_value(value) {}
    };
    
    LRUCache(int size) : m_capacity(size) {}
    
    int get(int key);
    
    void set(int key, int value);
    
private:
    int m_capacity;
    list<CacheNode> m_list;
    unordered_map<int, list<CacheNode>::iterator> m_hash;
};

int LRUCache::get(int key) {
    if (m_hash.find(key) == m_hash.end()) {
        return -1;
    }
    
    m_list.splice(m_list.begin(), m_list, m_hash[key]);
    m_hash[key] = m_list.begin();
    
    return m_hash[key]->m_value;
}

void LRUCache::set(int key, int value) {
    if (m_hash.find(key) == m_hash.end()) {
        if (m_capacity <= m_list.size()) {
            m_hash.erase(m_list.back().m_key);
            m_list.pop_back();
        }
        m_list.push_front(CacheNode(key, value));
        m_hash[key] = m_list.begin();
    } else {
        m_hash[key]->m_value = value;
        m_list.splice(m_list.begin(), m_list, m_hash[key]);
        m_hash[key] = m_list.begin();
    }
    
}

/*
int main()
{
    LRUCache cache(5);
    cache.set(1, 1);
    cache.set(2, 2);
    cache.set(3, 3);
    cache.set(4, 4);
    cache.set(5, 5);
    cache.set(6, 6);
    
    cache.get(3);
    cache.get(4);
}
*/