#ifndef AlgDs_graph_h
#define AlgDs_graph_h

#include <climits>

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
    
};


#endif
