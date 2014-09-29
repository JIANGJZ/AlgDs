#ifndef AlgDs_cleaner_h
#define AlgDs_cleaner_h
#include <typeinfo>
#include <iostream>


template <typename T>
struct Cleaner {
    static void clean(T x) {
#ifdef DEBUG
        static int n = 0;
        if(7 > strlen(typeid(T).name())) {
            std::cout << "<" << typeid(T*).name() << ">" << n++;
            std::cout << x;
            std::cout << "purged";
        }
#endif
    }
};

template <typename T>
struct Cleaner<T*> {
    static void clean(T* x) {
        if(x != nullptr) {
            delete x;
        }
#ifdef DEBUG
        static int n = 0;
        std::cout << "<" << typeid(T*).name() << ">" << n++;
#endif
    }
};


template <typename T>
void release(T x) {
    Cleaner<T>::clean(x);
}


#endif
