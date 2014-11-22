#include <iostream>
#include <list>

using namespace std;

int lastRemaining(list<int>& l, int m) {
    if (l.empty() || m < 0) {
        return -1;
    }
    
    list<int>::iterator current = l.begin();
    while (l.size() > 1) {
        for (int i = 0; i < m - 1; i++) {
            current++;
            if (current == l.end()) {
                current = l.begin();
            }
        }
        
        list<int>::iterator old = current;
        if (next(current) == l.end()) {
            current = l.begin();
        }
        else {
            current = next(current);
        }
        l.erase(old);
        
    }
    
    return *(l.begin());
}

/*
int main() {
    list<int> l = {1, 2, 3, 4, 6};
    
    
    lastRemaining(l, 2);
    
    cout << lastRemaining(l, 3);
}
*/