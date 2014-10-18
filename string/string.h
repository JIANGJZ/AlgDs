#ifndef AlgDs_my_string_h
#define AlgDs_my_string_h

#include <algorithm>
#include <cassert>

const int g_string_capacity_default = 3;

class String {
public:
    String(int c = g_string_capacity_default, int s = 0, char v = '\0') : m_capacity(c), m_size(s) {
        m_element = new char[m_capacity];
        for (m_size = 0; m_size < s; m_size++) {
            m_element[m_size] = '\0';
        }
    }
    
    String(char const* S, int lo, int hi) {
        _copy_from(S, lo, hi);
    }
    
    String(String const& S, int lo, int hi) {
        _copy_from(S.m_element, lo, hi);
    }
    
    String(String const& S) {
        _copy_from(S.m_element, 0, S.m_size);
    }
    
    ~String() {
        delete []m_element;
    }
    
    int length() const;
    
    char charAt(const int i) const;
    
    int comp(String& s) const;
    
    int comp(char* s) const;
    
    int indexOf(String& pattern)const;
    
    int indexOf(char* s) const;
    
    String prefix(int k) const;
    
    String suffix(int k) const;
    
    String& concat(char* s);
    
    String& concat(String& s);
    
    char* getData();
    
    void expand();
    
    void shrink();
private:
    int m_size;
    int m_capacity;
    char* m_element;
    
    void _copy_from(char const * s, int lo, int hi);
    
};

int String::length() const {
    return m_size;
}

char String::charAt(const int i) const {
    return m_element[i];
}

int String::comp(char *s) const {
    int i = 0;
    while (i < strlen(s) && i < m_size) {
        if (m_element[i] < s[i]) {
            return -1;
        }
        if (m_element[i] > s[i]) {
            return 1;
        }
        i++;
    }
    if (i < strlen(s)) {
        return -1;
    } else if (i < m_size){
        return 1;
    }
    return 0;
}

int String::comp(String &s) const {
    return this->comp(s.m_element);
}

int String::indexOf(String &pattern) const {
    return this->indexOf(pattern.m_element);
}

int String::indexOf(char *s) const {
    char *p = s;
    int i = 0;
    p = strstr(m_element, s);
    if (p == NULL) {
        return -1;
    } else {
        while (s != p) {
            s++;
            i++;
        }
    }
    return i;
}

String String::prefix(int k) const {
    return String(*this, 0, k);
}

String String::suffix(int k) const {
    return String(*this, k, m_size);
}

String& String::concat(char *s) {
    char* old_elem = m_element;
    m_element = new char[strlen(s) + m_size];
    int old_size = m_size;
    m_size = 0;
    for (int i = 0; i < old_size; i++) {
        m_element[m_size++] = old_elem[i];
    }
    
    for (int i = 0; i < strlen(s); i++) {
        m_element[m_size++] = s[i];
    }
    
    delete []old_elem;
    return *this;
}

String& String::concat(String &s) {
    concat(s.m_element);
    return *this;
}

void String::_copy_from(char const * s, int lo, int hi) {
    m_capacity = (hi - lo) * 2;
    m_size = 0;
    m_element = new char[m_capacity];
    while (lo < hi) {
        m_element[m_size++] = s[lo++];
    }
}

void String::expand() {
    if (m_size < m_capacity) {
        return;
    }
    m_capacity = std::max(m_capacity, g_string_capacity_default);
    
    char* old_elem = m_element;
    m_element = new char[m_capacity << 1];
    for (int i = 0; i < m_size; i++) {
        m_element[i] = old_elem[i];
    }
    delete []old_elem;
}

void String::shrink() {
    if (m_size < g_string_capacity_default) {
        return;
    }
    if (m_size << 2 > m_capacity) {
        return;
    }
    char* old_elem = m_element;
    m_element = new char[m_capacity >> 1];
    for (int i = 0; i < m_size; i++) {
        m_element[i] = old_elem[i];
    }
    
    delete [] old_elem;
}

char* String::getData() {
    return this->m_element;
}
#endif
