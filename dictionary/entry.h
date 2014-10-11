#ifndef AlgDs_entry_h
#define AlgDs_entry_h
template <typename K, typename V>
struct Entry {
    K key;
    V value;
    Entry(K k= K(), V v=V()) : key(k), value(v){
        
    }
    ~Entry() {
        
    }
    bool operator > (Entry<K, V>& e) {
        return key > e.key;
    }
    
    bool operator < (Entry<K, V>& e) {
        return key < e.key;
    }
    
    bool operator == (Entry<K, V>& e) {
        return key == e.key;
    }
    
    bool operator != (Entry<K, V>& e) {
        return key != e.key;
    }
};


#endif
