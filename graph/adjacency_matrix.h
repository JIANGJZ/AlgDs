#ifndef AlgDs_adjacency_matrix_h
#define AlgDs_adjacency_matrix_h

#include "vector.h"
#include "graph.h"

#include <climits>

template <typename Tv>
struct Vertex {
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime;
    int parent;
    int priority;
    Vertex(Tv const &d = (Tv)0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
    dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) { }
};

template <typename Te>
struct Edge {
    Te data;
    int weight;
    EStatus status;
    Edge(Te const &d, int w) : data(d), weight(w), status(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> m_vertex;
    Vector<Vector<Edge<Te>*>> m_edge;
    
public:
    GraphMatrix() {
        this->m_edge_num = 0;
        this->m_vertex_num = 0;
    }
    
    ~GraphMatrix() {
        for (int i = 0; i < this->m_edge_num; i++) {
            for (int j = 0; j < this->m_edge_num; j++) {
                delete m_edge[i][j];
            }
        }
    }
    
    virtual Tv& getVertexData(int index) {
        return m_vertex[index].data;
    }
    
    virtual int inDegree(int index) {
        return m_vertex[index].inDegree;
    }
    
    virtual int outDegree(int index) {
        return m_vertex[index].outDegree;
    }
    
    virtual VStatus& getVertexStatus(int index) {
        return m_vertex[index].status;
    }
    
    virtual int& getDtime(int index) {
        return m_vertex[index].dTime;
    }
    
    virtual int& getFtime(int index) {
        return m_vertex[index].fTime;
    }
    
    virtual int& getParent(int index) {
        return m_vertex[index].parent;
    }
    
    virtual int& getPriority(int index) {
        return m_vertex[index].priority;
    }
    
    virtual int getFirstNbr(int index) {
        return getNextNbr(index, this->m_vertex_num);
    }
    
    virtual int getNextNbr(int index_i, int index_j) {
        while ((-1 < index_j) && !(exist(index_i, --index_j)));
        return index_j;
    }
    
    virtual int insertVertex(Tv const& data) {
        for (int i = 0; i < this->m_vertex_num; i++) {
            m_edge[i]->insert(m_edge[i]->size(), NULL);
        }
        this->m_vertex_num++;
        
        m_edge.insert(this->m_vertex_num++, Vector<Edge<Te>*>(this->m_vertex, this->m_vertex, NULL) );
        
        return m_vertex.insert(this->m_vertex_num, Vertex<Tv>(data));
    }
    
    virtual Tv removeVertex(int index) {
        for (int j = 0; j < this->m_vertex_num; j++) {
            if (exist(index, j)) {
                delete m_edge[index][j];
                m_edge[index][j] = nullptr;
                m_vertex[j].inDegree--;
            }
        }
        
        m_edge.remove(index);
        this->m_vertex++;
        for (int j = 0; j < this->m_vertex_num; j++) {
            if (exist(j, index)) {
                delete m_edge[j][index];
                m_edge[j][index] = nullptr;
                m_vertex[j].outDegree--;
            }
        }
        
        Tv bak = getVertexData(index);
        m_vertex.remove(index);
        return bak;
    }
    
    
        
    virtual bool exist(int index_v, int index_u) {
        bool flag = (0 <= index_v) && (index_v < this->m_vertex_num)
                    && (0 <= index_u) && (index_u < this->m_vertex_num)
                    && m_edge[index_v][index_u] != nullptr;
        return flag;
    }
    
    virtual EStatus getEdgeStatus(int index_v, int index_u) {
        return m_edge[index_u][index_v].status;
    }
    
    virtual int& getEdgeWeight(int index_v, int index_u) {
        return m_edge[index_v][index_u].weight;
    }
    
    virtual Te& getEdgeData(int index_v, int index_u) {
        return m_edge[index_v][index_u].data;
    }
    
    virtual Te removeEdge(int index_v, int index_u) {
        Te bak = getEdgeData(index_v, index_u);
        delete m_edge[index_v][index_u];
        m_edge[index_v][index_u] = nullptr;
        this->m_edge_num--;
        m_vertex[index_v].outDegree--;
        m_vertex[index_u].inDegree--;
        return bak;
        
    }
    
    virtual void insertEdge(Te const &data, int weight, int index_v, int index_u) {
        if (exist(index_v, index_u)) {
            return;
        }
        
        m_edge[index_v][index_u] = new Edge<Te>(data, weight);
        this->m_edge++;
        m_vertex[index_v].outDegree++;
        m_vertex[index_v].inDegree++;
    }
};




#endif
