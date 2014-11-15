#include <list>
#include <iostream>

using namespace std;

class SolutionSTL
{
public:
    void reverseK(list<int>& l, int k) {
        list<int>::iterator it = l.begin();
        list<int>::iterator cur_p;
        list<int>::iterator pre_p;
        for (; it != l.end();) {
            cur_p = next(it);
            pre_p = it;
            for (int i = 0; i < k && it != l.end(); i++) {
                if (it == l.end()) {
                    break;
                }
                it = next(it);
            }
            if ((it != l.end()) || (l.size() % k == 0)) {
                reverse(pre_p, cur_p, it, l);
            }
        }
    }

private:
    void reverse(list<int>::iterator pre, list<int>::iterator cur, list<int>::iterator end, list<int>& l) {
        while (cur != end) {
            list<int>::iterator old = cur;
            cur = next(cur);
            l.splice(pre, l, old);
            pre = old;
        }
        
        
        copy(l.begin(), l.end(), ostream_iterator<int>(cerr, " "));
        cerr << endl;
        
    }
};

/*
int main()
{
    SolutionSTL s;
    
    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8};
    
    s.reverseK(l, 7);
    
    copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
}
*/