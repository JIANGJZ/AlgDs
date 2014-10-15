#ifndef AlgDs_hashtable_h
#define AlgDs_hashtable_h

#include "../dictionary/dictionary.h"
#include "../bitmap/bitmap.h"
#include "../util/cleaner.h"
#include "entry.h"

static size_t hashCode(char c) {
    return (size_t)c;
}

static size_t hashCode(int k) {
    return (size_t)k;
}

static size_t hashCode(long long i) {
    return (size_t)((i >> 32) + (int)i);
}

static size_t hashCode(char s[]) {
    int h = 0;
    for (int i = 0; i < strlen(s); i++) {
        h = (h << 5) | (h >> 27);
        h += (int)s[i];
    }
    
    return h;
}

int primeNLT(int c, int n, char* file) {
    Bitmap B(file, n);
    while (c < n) {
        if (B.test(c)) {
            c++;
        } else {
            return c;
        }
    }
    return c;
}

template <typename K, typename V>
class HashTable : public Dictionary<K, V> {
private:
    
    int bucket_num;
    int entry_num;
    Bitmap* lazyRemoval;
    Entry<K, V>** bucket;
    
    void rehash();
    
    inline bool isLazilyRemove(int x) {
        return lazyRemoval->test(x);
    }
    
    inline void markedAsRemove(int x){
        lazyRemoval->set(x);
    }
    
    int prope4Hit(K& key);
    
    int prope4Free(K& key);
    
public:
    HashTable(int c = 5);
    
    ~HashTable();
    
    int size() const;
    
    bool put(K key, V val);
    
    V* get(K key) const;
    
    bool remove(K key);
};

template <typename K, typename V>
HashTable<K, V>::HashTable(int c) {
    bucket_num = primeNLT(c, 1048567, "../prime.txt");
    entry_num = 0;
    bucket = new Entry<K, V>*[bucket_num];
    memset(bucket, 0, sizeof(Entry<K, V>*) * bucket_num);
    lazyRemoval = new Bitmap(bucket_num);
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    for (int i = 0; i < bucket_num; i++) {
        if (bucket[i]) {
            release(bucket[i]);
        }
    }
    release(bucket);
    release(lazyRemoval);
    
}


template <typename K, typename V>
void HashTable<K, V>::rehash() {
    int old_capacity = bucket_num;
    Entry<K, V>** old_bucket = bucket;
    bucket_num = primeNLT(2*bucket_num, 1048576, "../prime.txt");
    entry_num = 0;
    bucket = new Entry<K, V>*[bucket_num];
    memset(bucket, 0, sizeof(Entry<K, V>*)*bucket_num);
    for (int i = 0; i < old_capacity; i++) {
        if (old_bucket[i]) {
            put(old_bucket[i]->key, old_bucket[i]->value);
        }
    }
    release(old_bucket);
}

template <typename K, typename V>
int HashTable<K, V>::prope4Hit(K& key) {
    int r = hashCode(key) % bucket_num;
    while ((bucket[r] && (key != bucket[r]->key)) || ((!bucket[r]) && lazyRemoval(r))) {
        r = (r + 1) % bucket_num;
    }
    return r;
}

template <typename K, typename V>
int HashTable<K, V>::prope4Free(K& key) {
    int r = hashCode(key) % bucket_num;
    
    while (bucket[r]) {
        r = (r + 1) % bucket_num;
    }
    
    return r;
}

template <typename K, typename V>
V* HashTable<K, V>::get(K key) const {
    int r = prope4Hit(key);
    return bucket[r] ? &(bucket[r]) : nullptr;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(K key) {
    int r = prope4Hit(key);
    if (!bucket[r]) {
        return false;
    }
    release(bucket[r]);
    bucket[r] = nullptr;
    markedAsRemove(r);
    entry_num--;
    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::put(K key, V val) {
    if (bucket[prope4Hit(key)]) {
        return false;
    }
    
    int r = prope4Free(key);
    bucket[r] = new Entry<K, V>(key, val);
    entry_num++;
    
    if (entry_num * 2 > bucket_num) {
        rehash();
    }
    
    return true;
}


#endif
