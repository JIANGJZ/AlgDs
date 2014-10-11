#ifndef AlgDs_element_map_h
#define AlgDs_element_map_h

class ElementMap{
private:
    int* m_from;
    int* m_to;
    int N;
    int m_top;
    inline bool valid(int r) {
        return (0 <= r) && (r < m_top);
    }
    
public:
    ElementMap(int n = 8) {
        N = n;
        m_top = 0;
        m_from = new int[N];
        m_to = new int[N];
    }
    
    ~ElementMap() {
        delete []m_from;
        delete []m_to;
    }
    
    inline void set(int k) {
        if (test(k)) {
            return;
        }
        m_from[k] = m_top++;
        m_to[m_from[k]] = k;
    }
    
    inline bool test(int k) {
        return valid(m_from[k]) && (k == m_to[m_from[k]]);
    }
};

#endif
