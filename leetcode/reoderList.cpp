#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

class SolutionSTL
{
public:
    void reoderList(list<int>& l){
        list<int>::iterator it_slow = l.begin();
        list<int>::iterator it_fast = next(l.begin());
        
        while (next(it_fast) != l.end()) {
            it_slow++;
            it_fast++;
            it_fast++;
        }
        
        reverseList(it_slow, l);
        
        list<int>::iterator head = l.begin();
        list<int>::iterator mid = it_slow;
        while (next(head) != mid) {
            list<int>::iterator old = head;
            head = next(head);
            l.splice(it_slow, l, old);
            it_slow = next(it_slow);
        }
    
    }
    
private:
    void reverseList(list<int>::iterator& mid, list<int>& l) {
        list<int>::iterator cur = next(mid);
        
        while (cur != l.end()) {
            list<int>::iterator old = cur;
            cur++;
            l.splice(mid, l, old);
            mid = prev(mid);
        }
        
    }
};

/*
int main()
{
    SolutionSTL s;
    
    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8};
    
    s.reoderList(l);
    
    ostream_iterator<int> out(cout, " ");
    copy(l.begin(), l.end(), out);
}
*/