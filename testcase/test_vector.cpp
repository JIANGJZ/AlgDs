/*
#include "vector.h"

#include <iostream>

template <typename T>
class Visit {
public:
    void operator()(T &e) {
        std::cout << e << std::endl;
    };
};


int main() {
    Vector<int> V;
    Visit<int> visit;
    V.insert(V.size(), 12);
    V.traverse(visit);
}
*/
