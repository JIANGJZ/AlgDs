#ifndef AlgDs_dictionary_h
#define AlgDs_dictionary_h

template <typename K, typename V>
class Dictionary {
public:
    virtual int size() const = 0;
    virtual bool put(K key, V val) = 0;
    virtual V get(K key) = 0;
    virtual bool remove(K key) = 0;
};

#endif
