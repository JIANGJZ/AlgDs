#ifndef AlgDs_graph_h
#define AlgDs_graph_h

#include "../queue/v_queue.h"
#include "../stack/v_stack.h"

#include <climits>
#include <iostream>

typedef enum {
    UNDISCOVERED,
    DISCOVERED,
    VISITED
}VStatus;

typedef enum {
    UNDETERMINED,
    TREE,
    CROSS,
    FORWORD,
    BACKWARD
}EStatus;


template <typename Tv, typename Te>
class Graph {
private:
    void reset() {
        for (int i = 0; i < m_vertex_num; i++) {
            getDtime(i) = -1;
            getFtime(i) = -1;
            getParent(i) = -1;
            getPriority(i) = INT_MAX;
            getVertexStatus(i) = UNDISCOVERED;
            for (int j = 0; j < m_vertex_num; j++) {
                if (exist(i, j)) {
                    getEdgeStatus(i, j) = UNDETERMINED;
                }
            }
        }
    }
    
    void _bfs(int start_v, int& clock);
    
    void _dfs(int start_v, int& clock);
    
    bool _tSort(int start_v, int& clock, VStack<Tv>* S);
    
    template <typename P>
    void _pfs(int clock, P priority);
    
public:
    int m_vertex_num;
    
    virtual Tv& getVertexData(int index) = 0;
    
    virtual int inDegree(int index) = 0;
    
    virtual int outDegree(int index) = 0;
    
    virtual VStatus& getVertexStatus(int index) = 0;
    
    virtual int& getDtime(int index) = 0;
    
    virtual int& getFtime(int index) = 0;
    
    virtual int& getParent(int index) = 0;
    
    virtual int& getPriority(int index) = 0;
    
    virtual int getFirstNbr(int index) = 0;
    
    virtual int getNextNbr(int index_i, int index_j) = 0;
    
    virtual int insertVertex(Tv const& data) = 0;
    
    virtual Tv removeVertex(int index) = 0;
    
    
    
    int m_edge_num;
    
    virtual bool exist(int index_v, int index_u) = 0;
    
    virtual EStatus getEdgeStatus(int index_v, int index_u) = 0;
    
    virtual int& getEdgeWeight(int index_v, int index_u) = 0;
    
    virtual Te& getEdgeData(int index_v, int index_u) = 0;
    
    virtual Te removeEdge(int index_v, int index_u) = 0;
    
    virtual void insertEdge(Te const &data, int weight, int index_v, int index_u) = 0;
    
    int bfs(int start_v);
    
    int dfs(int start_v);
    
    VStack<Tv>* tSort(int start_v);
    
    template <typename P>
    void pfs(int clock, P priority);
    
    void prim(int start_v);
    
    void dijkstra(int start_v);
};

template <typename Tv, typename Te>
void Graph<Tv, Te>::_bfs(int start_v, int& clock) {
    VQueue<int> Q;
    getVertexStatus(start_v) = DISCOVERED;
    Q.enqueue(start_v);
    while (!Q.empty()) {
        int v = Q.dequeue();
        getDtime(v) = ++clock;
        for (int u = getFirstNbr(v); -1 < u; u = getNextNbr(v, u)) {
            if (UNDISCOVERED == getVertexStatus(u)) {
                getVertexStatus(u) = DISCOVERED;
                Q.enqueue(u);
                getEdgeStatus(v, u) = TREE;
                getParent(u) = v;
            } else {
                getEdgeStatus(v, u) = CROSS;
            }
        }
        
        getVertexStatus(v) = VISITED;
    }
    
}


template <typename Tv, typename Te>
int Graph<Tv, Te>::bfs(int start_v) {
    reset();
    int clock = 0;
    int v = start_v;
    do {
        if (UNDISCOVERED == getVertexStatus(v)) {
            _bfs(v, clock);
        }
        v = (++v % m_vertex_num);
    } while (start_v != v);
    
}


template <typename Tv, typename Te>
void Graph<Tv, Te>::_dfs(int start_v, int &clock) {
    getDtime(start_v) = ++clock;
    getVertexStatus(start_v) = DISCOVERED;
    for (int u = getFirstNbr(start_v); -1 < u; u = getNextNbr(start_v, u)) {
        switch (getVertexStatus(u)) {
            case UNDISCOVERED:
                getEdgeStatus(start_v, u) = TREE;
                getParent(u) = start_v;
                _dfs(u, clock);
                break;
            case DISCOVERED:
                getEdgeStatus(start_v, u);
                break;
            default:
                getEdgeStatus(start_v, u) = getDtime(start_v)  < getDtime(u) ? FORWORD : CROSS;
                break;
        }
    }
    getVertexStatus(start_v) = VISITED;
    getFtime(start_v) = ++clock;
}

template <typename Tv, typename Te>
int Graph<Tv, Te>::dfs(int start_v) {
    reset();
    int clock = 0;
    int v = start_v;
    do {
        if (UNDISCOVERED == getVertexStatus(v)) {
            _dfs(v, clock);
        }
        v = (++v % m_vertex_num);
    }while (start_v != v);
}

template <typename Tv, typename Te>
bool Graph<Tv, Te>::_tSort(int start_v, int &clock, VStack<Tv> *S) {
    getDtime(start_v) = ++clock;
    getVertexStatus(start_v) = DISCOVERED;
    for (int u = getFirstNbr(start_v); -1 < u; u = getNextNbr(start_v, u)) {
        switch (getVertexStatus(u)) {
            case UNDISCOVERED:
                getParent(u) = start_v;
                getEdgeStatus(start_v, u) = TREE;
                if (!_tSort(u, clock, S)) {
                    return false;
                }
                break;
            case DISCOVERED:
                getEdgeStatus(start_v, u) = BACKWARD;
                return false;
            default:
                getEdgeStatus(start_v, u) = getDtime(start_v)  < getDtime(u) ? FORWORD : CROSS;
                break;
        }
    }
    getVertexStatus(start_v) = VISITED;
    S->push(getVertexData(start_v));
    return true;
}

template <typename Tv, typename Te>
VStack<Tv>* Graph<Tv, Te>::tSort(int start_v) {
    reset();
    int clock = 0;
    int v = start_v;
    VStack<Tv>* S = new VStack<Tv>();
    do {
        if (UNDISCOVERED == getVertexStatus(v)) {
            if (!_tSort(v, clock, S)) {
                while (!S->empty()) {
                    std::cout << S->top();
                    S->pop();
                }
            }
        }
        v = (++v % m_vertex_num);
    }while (start_v != v);
    return S;
}


template <typename Tv, typename Te>
struct DijkstraP {
    void operator() (Graph<Tv, Te>* g, int start_v, int u) {
        if(UNDISCOVERED == g->getVertexStatus(u)) {
            if(g->getPriority(u) > g->getPriority(start_v) + g->getWeight(start_v, u)) {
                g->getPriority(u) = g->getPriority(start_v) + g->getWeight(start_v, u);
                g->getParent(u) = start_v;
            }
        }
    }
};

template <typename Tv, typename Te>
struct PrimP {
    void operator() (Graph<Tv, Te>* g, int start_v, int u) {
        if(UNDISCOVERED == g->getVertexStatus(u)) {
            if(g->getPriority(u) > g->getWeight(start_v, u)) {
                g->getPriority(u) = g->getWeight(start_v, u);
                g->getParent(u) = start_v;
            }
        }
    }
};

template <typename Tv, typename Te>
template <typename P>
void Graph<Tv, Te>::_pfs(int start_v, P priority) {
    getPriority(start_v) = 0;
    getVertexStatus(start_v) = VISITED;
    getParent(start_v) = -1;
    
    while (1) {
        for (int u = getFirstNbr(start_v); -1 < u; u = getNextNbr(start_v, u)) {
            priority(this, start_v, u);
        }
        
        for (int shortest = INT_MAX, v = 0; v < m_vertex_num; v++) {
            if (UNDISCOVERED == getVertexStatus(v)) {
                if (shortest > getPriority(v)) {
                    shortest = getPriority(v);
                    start_v = v;
                }
            }
        }
        
        if (VISITED == getVertexStatus(start_v)) {
            break;
        }
        
        getVertexStatus(start_v) = VISITED;
        getEdgeStatus(getParent(start_v), start_v) = TREE;
    }
    
}

template <typename Tv, typename Te>
template <typename P>
void Graph<Tv, Te>::pfs(int start_v, P priority) {
    reset();
    int v = start_v;
    do {
        if (UNDISCOVERED == getVertexStatus(v)) {
            _pfs(v, priority);
        }
        v = (++v % m_vertex_num);
    }while (start_v != v);
}

#endif
