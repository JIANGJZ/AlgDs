#ifndef AlgDs_bitmap_h
#define AlgDs_bitmap_h

#include <memory>
#include <cstdio>
#include <iostream>


class Bitmap {
private:
    char *m_map;
    int m_byte_len;
    
    void init(int n) {
        m_byte_len = (n + 7)/8;
        m_map = new char[m_byte_len];
        memset(m_map, 0, m_byte_len);
    }
    
    void expand(int k);

public:
    Bitmap(int n = 8) {
        init(n);
    }
    
    Bitmap(char* file, int n = 8) {
        init(n);
        FILE* fp = fopen(file, "r");
        fread(m_map, sizeof(char), m_byte_len, fp);
        fclose(fp);
    }
    
    ~Bitmap() {
        delete []m_map;
        m_map = nullptr;
    }
    
    void set(int k);
    
    void clear(int k);
    
    bool test(int k);
    
    void dump(char* file) {
        FILE* fp = fopen(file, "w");
        fwrite(m_map, sizeof(char), m_byte_len, fp);
        fclose(fp);
    }
    
    char* bits2string(int n) {
        expand(n-1);
        char* s = new char[n+1];
        s[n] = '\0';
        for (int i = 0; i < n; i++) {
            s[i] = test(i) ? '1' : '0';
        }
        return s;
    }
    
    void print(int n) {
        expand(n);
        for (int i = 0; i < n; i++) {
            std::cout << (test(i) ? '1' : '0');
        }
    }
};

void Bitmap::expand(int k) {
    if (k < m_byte_len * 8) {
        return;
    }
    
    char* old_map = m_map;
    int old_len = m_byte_len;
    
    m_byte_len = (2 * k + 7) / 8;
    
    m_map = new char[m_byte_len];
    memset(m_map, 0, m_byte_len);
    memcpy(m_map, old_map, old_len);
    
    delete []old_map;
    old_map = nullptr;
}

void Bitmap::set(int k) {
    expand(k);
    m_map[k >> 3] |= ((0x80) >> (k & 0x07));
}

void Bitmap::clear(int k) {
    expand(k);
    m_map[k >> 3] &= ~((0x80) >> (k & 0x07));
}

bool Bitmap::test(int k) {
    expand(k);
    return m_map[k >> 3] & ((0x80) >> (k & 0x70));
}



#endif
